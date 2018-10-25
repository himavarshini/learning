#include <iostream>
#include <array>

int main()
{
    std::array<int, 10> a;
    int i;

    for (i = 0; i < 10; i ++) {
        a[i] = i;
    }

    for (i = 0; i < a.size(); i ++) {
        std::cout << a[i] << std::endl;
    }
}

