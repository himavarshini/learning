# CPP Manual

## FAQ

1. to use C code inside the cpp use `extern "C" {"` and the `}` when the `C` portion of the program end.


## namespaces

1. namespaces are used to organise the very large amount of source code to avoid name collisions (mainly).

## STL

## Standard library std (String library)

1. string library is part of std namespace. so, `std::string`. or `using namespace std` and directly reference string
2. c++ strings does not include null terminator because the c++ string class contain the housekeeping information such as the length of the string and the left length so that to expand the internal buffer storage
3. header file `<string>`.
4. initialising strings:

```cpp
using namespace std;

string s1; // s1 is filled with zeros or length 0
string s2("Hello"); //s2 basically initialised by the constructor
string s3 = "Hello" ; // '=' overloading ?
string s4(s3); // initilsing by another string using constructor again
string s5(s2, 0, 2); // first two characters of string s2
string s6(s2, 2, 4); // middle two of the string s2
```

The below example describe something in c++ one of the features:

##### Example taken from the Thinking in C++ book Vol.2
```cpp
#include <string>
#include <iostream>

using namespace std;

int main()
{
    string s1("12345");
    
    // beginning of the string s1.
    string::iterator it = s1.begin();
    
    // make s2 point to s1
    string s2 = s1;
    
    // changes s1 but not s2.. at this point the s2 is become a copy of original string s1.
    *it = '0';
    
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    
    return 0;
}
```
