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
    std::cout << "Lenght of string: " << str.length() << std::endl;

    // lenght of the string
    std::cout << "size: " << str.size() << std::endl;

    // capacity of the string
    std::cout << "Capacity: " << str.capacity() << std::endl;

    // insert at the end
    str.append(" This is Dev");

    std::cout << str << std::endl;

    // insert at the beginning
    str.insert(0, "Hello ");

    std::cout << str << std::endl;

    std::string s1;

    std::cout << "capacity of unallocated string: " << s1.capacity() << std::endl;
    std::cout << "size of unallocated string: " << s1.size() << std::endl;

    // reserve some storage for the string
    s1.reserve(400);

    std::cout << "capcity of s1 " << s1.capacity() << " size of s1 " << s1.size() << std::endl;

    return 0;
}

