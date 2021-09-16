#include "view.h"
#include <iostream>

void foo(emb::view<int> xs)
{
    for (auto const& x : xs) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}

int main(void)
{
    int arr[5] = {0, 1, 2, 3, 4};
    emb::view<int> xs(arr);
    foo(xs);

    return 0;
}
