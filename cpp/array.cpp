#include <iostream>
#include <array>

int main()
{
    std::array<int, 10> a;
    int i;

    for (i = 0; i < 10; i ++) {
        a.at(i) = i;
    }

    std::array<int, 10>::const_iterator it;

    for (it = a.begin(); it != a.end(); it ++) {
        std::cout << *it << std::endl;
    }

    std::cout << "size of array: " << a.size() << std::endl;
    std::cout << "front " << a.front() << " back " << a.back() << std::endl;

    std::cout << "accessing with operator[]" << std::endl;
    for (i = 0; i < a.size(); i ++) {
        std::cout << a[i] << std::endl;
    }
}

