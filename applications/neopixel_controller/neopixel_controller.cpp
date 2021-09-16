#include "neopixel_controller.h"

#include "em_device.h"

#include "em_ldma.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"

/*-----------------------------------------------------------------------------
 * Constants
 *---------------------------------------------------------------------------*/

static constexpr GPIO_Port_TypeDef pixelTxPort = gpioPortC;

static constexpr uint32_t pixelTxPin = 0;

static USART_TypeDef* usartInstance = USART0;

static constexpr CMU_Clock_TypeDef usartClockInstance = cmuClock_USART0;

static constexpr uint32_t usartBaudRate = 3'333'333u;

static constexpr unsigned int LDMA_CH = 0;

static constexpr unsigned int LDMA_CH_MASK = 1 << LDMA_CH;

/**
 * To transfer a single pixel worth of data, the USART needs to transmit 3
 * colors, with 4 bytes per color.
 */
static constexpr size_t XFERCNT = 3 * 4;

/*-----------------------------------------------------------------------------
 * Variables
 *---------------------------------------------------------------------------*/

namespace {

/**
 * Buffer holding raw pixel data to drive SK6812 "neopixels".
 *
 * Logical `uint8_t` RGB values can be converted to `uint32_t` values suitable
 * for transmission with the `neopixel_lookup_table`.
 */
std::array<volatile uint32_t, 3> pixelTxBuffer;

/**
 * LDMA channel configuration.
 *
 * Configures the LDMA channel to trigger transfers on USART0 TXBL signal. The
 * transfer loops for each descriptor.
 */
const LDMA_TransferCfg_t transfer = {
  .ldmaReqSel =
    LDMAXBAR_CH_REQSEL_SOURCESEL_USART0 | LDMAXBAR_CH_REQSEL_SIGSEL_USART0TXBL,
  .ldmaCtrlSyncPrsClrOff = 0,
  .ldmaCtrlSyncPrsClrOn = 0,
  .ldmaCtrlSyncPrsSetOff = 0,
  .ldmaCtrlSyncPrsSetOn = 0,
  .ldmaReqDis = false,
  .ldmaDbgHalt = false,
  .ldmaCfgArbSlots = ldmaCfgArbSlotsAs1,
  .ldmaCfgSrcIncSign = ldmaCfgSrcIncSignPos,
  .ldmaCfgDstIncSign = ldmaCfgDstIncSignPos,
  .ldmaLoopCnt = NUM_LEDS,
};

/**
 * LDMA Transfer Descriptor.
 *
 * @warning Don't change the values! The LDMA <-> USART transfer is quite picky.
 */
const LDMA_Descriptor_t descriptor = {
  .xfer =
    {
      .structType = ldmaCtrlStructTypeXfer,
      .reserved0 = 0,
      .structReq = 1,
      .xferCnt = XFERCNT - 1,
      .byteSwap = 0,
      .blockSize = ldmaCtrlBlockSizeUnit1,
      .doneIfs = 0,
      .reqMode = 0,
      .decLoopCnt = 1,
      .ignoreSrec = 1,
      .srcInc = ldmaCtrlSrcIncOne,
      .size = ldmaCtrlSizeByte,
      .dstInc = ldmaCtrlDstIncNone,
      .srcAddrMode = 0,
      .dstAddrMode = 0,
      .srcAddr = reinterpret_cast<uintptr_t>(pixelTxBuffer.data()),
      .dstAddr = reinterpret_cast<uintptr_t>(&usartInstance->TXDATA),
      .linkMode = ldmaLinkModeRel,
      .link = 0,
      .linkAddr = 0,
    },
};

}  // namespace

/*-----------------------------------------------------------------------------
 * Private Function Declarations
 *---------------------------------------------------------------------------*/

void initGpio();

void initLdma();

void initUsart();

/*-----------------------------------------------------------------------------
 * Interrupts
 *---------------------------------------------------------------------------*/

extern "C" void LDMA_IRQHandler()
{
    uint32_t flags = LDMA->IF;

    LDMA->IF_CLR = flags;

    if (flags & LDMA_IF_DONE0) {
        LDMA->IF_CLR = LDMA_IF_DONE0;
    }

    if (flags & LDMA_IF_ERROR) {
        __BKPT(0);
    }
}

/*-----------------------------------------------------------------------------
 * Public Function Definitions
 *---------------------------------------------------------------------------*/

void neopixel_controller_init()
{
    initGpio();
    initUsart();
    initLdma();
}

void neopixel_controller_send(uint8_t red, uint8_t green, uint8_t blue)
{
    pixelTxBuffer[0] = neopixel_lookup_table[green];
    pixelTxBuffer[1] = neopixel_lookup_table[red];
    pixelTxBuffer[2] = neopixel_lookup_table[blue];

    LDMA_StartTransfer(0, &transfer, &descriptor);
}

/*-----------------------------------------------------------------------------
 * Private Function Definitions
 *---------------------------------------------------------------------------*/

void initGpio()
{
    // Enable peripheral clock

    CMU_ClockEnable(cmuClock_GPIO, true);

    // Configure external pin for digital output

    GPIO_PinModeSet(pixelTxPort, pixelTxPin, gpioModePushPull, 0);
}

void initLdma()
{
    // Initialize LDMA peripheral
    LDMA_Init_t init = LDMA_INIT_DEFAULT;
    LDMA_Init(&init);
}

void initUsart()
{
    // Enable peripheral clock

    CMU_ClockEnable(usartClockInstance, true);

    // Initialize USART peripheral

    USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;
    init.enable = usartEnableTx;
    init.baudrate = usartBaudRate;
    init.msbf = true;
    USART_InitSync(usartInstance, &init);

    // Route USARTn Tx signal to external GPIO

    GPIO->USARTROUTE_SET[USART_NUM(usartInstance)].ROUTEEN =
      GPIO_USART_ROUTEEN_TXPEN;
    GPIO->USARTROUTE_SET[USART_NUM(usartInstance)].TXROUTE =
      ((pixelTxPort << _GPIO_USART_TXROUTE_PORT_SHIFT)
        & _GPIO_USART_TXROUTE_PORT_MASK)
      | ((pixelTxPin << _GPIO_USART_TXROUTE_PIN_SHIFT)
         & _GPIO_USART_TXROUTE_PIN_MASK);
}
