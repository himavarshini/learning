
# C and CPP Manual

## pre-processor statement

1. preprocessor macros are used for various purposes such as from defining or giving names to values to a function look alikes for perofmrnace reasons

2. value type example

```c
#define IPHONE_VERSION "6s"
```

3. function type example

```c
#define get_iphone_version(_version) { \
    _version = "6s"; \
}
```

above is a multi-line macro.. observe the `\` line after the each line till the end. To group all the statements with in the macro function usually `{` and `{`} are used.

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

### Some of the string manipulation API

1. length of string : `str.length()`.
2. iterator definitions

```cpp
string s("12345");
string::iterator it;
```

3. finding the size : `str.size()`
4. finding the capacity: `str.capacity()`
5. inserting at a particular pos: `str.insert(pos, string_val)`
6. appending at the end of the string: `str.append(string_val)`
7. size of the following string is 0.

```cpp
string str;

cout << "size : " << str.size() << endl;

str.reserve(10);

cout << "size : " << str.size() << endl;
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

## Secure coding practises

1. do not use `gets()`.

The `gets()` function usage is as follows.

```cpp
char input[30];

cout << "Enter your input" << endl;
// user may enter input more than 30 lines ..
gets(input);
```

Above example describe one example of the unsafe use of `gets()`. The user input buffer is of size 30 byte and the gets takes the input from
a command line. If the input grows more than 30 bytes, the out of bounds error will occur causing the program to crash.

The safest way to program this is to use `fgets()`.

```cpp
char input[30];

cout << "Enter your input" << endl;

// stdin is input .. the fgets reads till size of input bytes
fgets(input, sizeof(input) - 1, stdin);
```

Above example describe that the `fgets()` reads till one less than the size of the `input`.

