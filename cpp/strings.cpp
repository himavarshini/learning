#include <iostream>
#include <string>
#include <cstdio>

int main(int argc, char **argv)
{
    std::string str;

    if (argc != 2) {
        fprintf(stderr, "<%s> string\n", argv[0]);
        return -1;
    }

    str = std::string{argv[1]};

    std::cout << "string " << str << std::endl;
    return 0;
}

