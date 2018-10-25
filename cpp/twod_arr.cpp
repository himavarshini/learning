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

    for (it = twod_array.begin(); it != twod_array.end(); it ++) {
        std::array<int, 10>::const_iterator _it;
        std::array<int, 10> t = *it;

        for (_it = t.begin(); _it != t.end(); _it ++) {
            std::cout << *_it << "\t";
        }
        std::cout << "\n";
    }
}

