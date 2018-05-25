#include <iostream>
#include <string>

int main()
{
    std::string str("Hello");
    std::string::iterator it;

    for (it = str.begin(); it < str.end(); it ++) {
        std::cout << str << std::endl;
    }

    // get length of the string
    std::cout << str.length() << std::endl;

    return 0;
}

