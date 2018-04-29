#include <iostream>
#include <vector>

// vector declaration
//
// std::vector<int> array;
//
// reserve 3 elements
// array.reserve(3);
//
// append an element into the array
//
// array.push_back(100);
//
// resize the vector
// array.resize(5);
//
using namespace std;

int main(int argc, char **argv)
{
    vector<int> array1;
    vector<int> array(10);

    for (int i = 0; i < 10; i ++) {
        array[i] = i;
    }

    for (int i = 0; i < 10; i ++)
        cout << "i : " << array[i] <<endl;

    try {
        array.at(1000) = 0;
    }

    catch (out_of_range o) {
        cout <<o.what() <<endl;
    }
    
    return 0;
}
