add_library(stdlib OBJECT)

target_sources(stdlib PRIVATE exit.cpp assert.cpp)

target_link_libraries(stdlib PRIVATE gecko-sdk)
