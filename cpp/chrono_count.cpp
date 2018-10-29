#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

int main()
{
    std::chrono::milliseconds ms = 1s;

    std::cout << "number of milliseconds " << ms.count() << std::endl;
}
