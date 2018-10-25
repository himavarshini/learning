#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    std::string str;

    if (argc != 2) {
        std::cerr << argv[1] << " string\n";
        return -1;
    }

    str = std::string{argv[1]};

    std::string::const_iterator it;

    for (it = str.begin(); it != str.end(); it ++) {
        std::cout << *it << std::endl;
    }

    return 0;
}

