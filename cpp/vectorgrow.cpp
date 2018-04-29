#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> array;
    vector<int> array1;
    int i;

    array.push_back(10);

    for (i = 0 ; i < array.size(); i ++)
        cout << "array: " <<array[i] <<endl;

    array1.reserve(10);
    cout << "array size " << array.capacity() << endl;
    cout << "array1 size " << array1.capacity() << endl;
    
    return 0;
}
