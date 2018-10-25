#include <iostream>
#include <array>

int main(int argc, char **argv)
{
    std::array<std::array<int, 10>, 10> twod_array;
    int i;
    int j;

    for (i = 0; i < 10; i ++) {
        for (j = 0; j < 10; j ++) {
            twod_array[i][j] = i + j;
        }
    }

    std::array<std::array<int, 10>, 10>::const_iterator it;

    std::cout << "print from front " << std::endl;
    for (it = twod_array.begin(); it != twod_array.end(); it ++) {
        std::array<int, 10>::const_iterator _it;
        std::array<int, 10> t = *it;

        for (_it = t.begin(); _it != t.end(); _it ++) {
            std::cout << *_it << "\t";
        }
        std::cout << "\n";
    }

    std::array<std::array<int, 10>, 10>::reverse_iterator rit;

    std::cout << "print from rear " << std::endl;
    for (rit = twod_array.rbegin(); rit != twod_array.rend(); rit ++) {
        std::array<int, 10>::reverse_iterator _rit;
        std::array<int, 10> t = *rit;

        for (_rit = t.rbegin(); _rit != t.rend(); _rit ++) {
            std::cout << *_rit << "\t";
        }
        std::cout << "\n";
    }
}

