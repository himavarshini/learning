#include <iostream>
#include <array>

int main()
{
    std::array<int, 10> a;
    int i;

    for (i = 0; i < 10; i ++) {
        a.at(i) = i;
    }

    std::array<int, 10>::reverse_iterator it;

    for (it = a.rbegin(); it != a.rend(); it ++) {
        std::cout << *it << std::endl;
    }
}

