
# C and CPP Manual

## Intro

This is a work-in-progress reference manual that detail on the C, C++ and the parts of secure coding in C. This is basically what i learnt over the time.

Instructions to start the manual:

1. use Ubuntu OS.. i used Ubuntu to compile and run programs .. any Ubuntu >= 18.04 is ok. If you want to use the other OS, you are free to do so.. MacOS does `g++` and `gcc` as well similar to the Ubuntu. Windows, usually it is hard to setup but MinGW is one option. MinGW is here: http://www.mingw.org/
2. install gcc on Ubuntu.

```shell
apt install build-essential gcc g++
```

Author: Dev Naga `<devendra.aaru@gmail.com>`   All rights reserved


## 1. Introduction to Compilers

## 2. C Programming

### pre-processor statement

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

above is a multi-line macro.. observe the `\` line after the each line till the end. To group all the statements with in the macro function usually `{` and `{` are used.

### FAQ

1. to use C code inside the cpp use `extern "C" {"` and the `}` when the `C` portion of the program end.


### namespaces

1. namespaces are used to organise the very large amount of source code to avoid name collisions (mainly).

### STL

#### Standard library std (String library)

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

##### Some of the string manipulation API

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

#### vectors

1. vectors are dynamic arrays unlike the C's static arrays (it can be of array of integers, strings ..).
2. vectors is a class of std library
3. so we need to use `using namespace std` or use the full form representation (peferred approach if you are starting with CPP)

**some of the APIs**

1. iterating

    iterating from begin to end:

    ```cpp
    vector<string>::const_iterator const_i;
    ```
    
    and then one can use the variable (of type `vector<string>`) types `.begin()` and `.end()` to iterate through the array.

```cpp
    vector<string> str;
    vector<string>::const_iterator const_i;

    for (const_i = str.begin(); const_i != str.end(); const_i ++) {
        cout << "String is " << *const_i << endl;
    }
```

iterating from end to begin:


```cpp
    vector<string>::reverse_iterator rev_i;
```


    and then one can use `.rbegin()` and `.rend()` methods similar to the `.begin()` and `.end()` counterparts.


```cpp
    vector<string> str;
    vector<string>::reverse_iterator rev_i;

    for (rev_i = str.rbegin(); rev_i != str.rend(); rev_i ++) {
        cout << "String is " << *rev_i << endl;
    }
```


on the otherhand, the normal iteration works as well.


```cpp
    vector<string> str;
    int i;

    for (i = 0; i < str.size(); i ++) {
        cout << "String is " << str[i] << endl;
    }
```


note the usage of `str.size()` method to find the length of vector.

2. adding elements at the end.
    use `.push_back()` method to perform this operation.


```cpp
    vector<string> str;

    str.push_back("Hello");
```


3. count elements in vector:
        `.size()` method.

4. check if the vector is empty:
        `.empty()` method.

5. reserving the vector does not make big difference because the vector is dynamic array.

        `.reserve()` method.

6. erase the elements of the vector is two way.

        `erase()` call can take one element -> `erase(iterator it)`
        `erase()` call can take over begin and end -> `erase(begin_iterator, end_iterator)`.

        either erase one element or erase an entire set of elements.

7. inserting the elements at the beginning -> `insert(iterator, variable)`

```cpp
        vector<string> str;

        str.insert(str.begin(), "Hi");
```

Example with all the above API is below.. along with some of the different API tests:

```cpp
#include <iostream>
#include <vector>


int main()
{
    std::vector<int> a;

    if (a.empty()) {
        std::cout << "Vector a is empty" << std::endl;
    }

    std::cout << "elements in vector a:" << a.size() << std::endl;
    std::cout << "capacity:" << a.capacity() << std::endl;
    std::cout << "maxsize:" << a.max_size() << std::endl;

    a.reserve(4);

    std::cout << "new size:" << a.size() << std::endl;

    int i;
    for (i = 0; i < 44; i ++) {
        a.push_back(i);
    }

    std::cout << "new size:" << a.size() << std::endl;

    for (i = 0; i < a.size(); i ++) {
        std::cout << "a:" << a[i] << std::endl;
    }

    std::vector<int>::iterator r = a.begin();

    a.erase(r);

    std::cout << "size::->" << a.size() << std::endl;

    // version oerloaded erase
    a.erase(a.begin(), a.end());

    std::cout << "size::->" << a.size() << std::endl;

    return 0;
}
```

Iterting through the structures is bit different. Please look at the below program.

```cpp
#include <iostream>
#include <vector>

struct types {
    int a;
    double e;
};

int main()
{
    std::vector<struct types> s;

    s.push_back(types());

    s[0].a = 10;
    s[0].e = 10.4;

    s.push_back(types());

    s[1].a = 4;
    s[1].e = 4.4;

    std::vector<struct types>::const_iterator i;

    for (i = s.begin(); i != s.end(); i ++) {
        std::cout << "a:" << (*i).a << std::endl;
        std::cout << "e:" << (*i).e << std::endl;
    }

    return 0;
}
```

1. the `push_back()` method accepts the constructor of the type `struct type`, where the `type` is a structure name.
2. each time a new element to be added, a `.push_back()` is called and then elements are referenced and assignment is made.
3. the access to the elements is same as the vector of integer or strings.


## Cyber security - Secure coding practises

#### Links:

1. https://wiki.sei.cmu.edu/confluence/display/c/PRE31-C.+Avoid+side+effects+in+arguments+to+unsafe+macros#space-menu-link-content
2. https://www.w0lfzhang.com/2018/01/17/ASUS-router-stack-overflow-in-http-server/

#### Details:

**1. Bufferoverflow**:

**1.a.)** do not use `gets()` while programming

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

