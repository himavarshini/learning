
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

## std::to_string

converts any value type into strings, so be it an `int`, `unsigned int`, `double`, or `long` types. The `to_string` method is an overloaded type.

Example:

```cpp
#include <iostream>
#include <cstdint>
#include <climits>
#include <string>

int main()
{
    std::string int_str = std::to_string(4);
    std::string long_str = std::to_string(INT_MAX);
    std::string long_long_str = std::to_string(UINT_MAX);
    std::string unsigned_str = std::to_string(65535);
    std::string double_str = std::to_string(14.414);

    std::cout << "int:" << int_str << std::endl;
    std::cout << "long:" << long_str << std::endl;
    std::cout << "long long:" << long_long_str << std::endl;
    std::cout << "unsigned int:" << unsigned_str << std::endl;
    std::cout << "double str:" << double_str << std::endl;
}
```

## std::sort

`std::sort` sorts out the content and orders them in ascending order. Below example reads random input from `/dev/urandom` and apply `std::sort` on it.

use `algorithm` header for `std::sort`. always include `<unistd.h>` while using any Linux OS internal lib.

```cpp
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>

extern "C" {
#include <unistd.h>
int getInt(int fd)
{
    int var;

    read(fd, &var, sizeof(var));

    return var;
}
}

int main()
{
    std::vector<unsigned int> a;
    struct timeval tv;
    int i;
    int fd;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        std::cout << "failed to open /dev/urandom" << std::endl;
        return -1;
    }

    for (i = 0; i < 100; i ++) {
        unsigned int var;

        var = getInt(fd);
        a.push_back(var);
    }

    std::sort(a.begin(), a.end());

    std::vector<unsigned int>::const_iterator t;

    for (t = a.begin(); t != a.end(); t ++) {
        std::cout << "a:" << *t << std::endl;
    }

    close(fd);
    return 0;
}
```

## overloading functions

1. same function name but different jobs depending on the type of input passed

Example:

```cpp
#include <iostream>

int add(int a, int b)
{
    return a + b;
}

double add(double a, double b)
{
    return a + b;
}

int main()
{
    std::cout << "add result for ints <1 and 2>:" << add(1, 2) << std::endl;
    std::cout << "add result for doubles <1.1 and 2.2>:" << add(1.1, 2.2) << std::endl;
    std::cout << "add result for a double and int <1.1 and 2>:" << add(1.1, 2) << std::endl;
}
```

see the error after compiling this example: that the last line when passed a double and an int. This is because the compiler
does not find a match with this type.

But when typecasting the value `2` to `(double)2` the code works again see the below:

```cpp
std::cout << "add result for a double and int <1.1 and 2>:" << add(1.1, (double)2) << std::endl;
```

2. if the function has same args the overloading is not possible
3. if the caller passes the variables of types that are not available in the target overloaded functions, then it is not possible to overload (care must be taken to 
pass the right options or use the typecasting - but typecasting is strictly not good in c++)


## constructors

1. constructors are like init routines of a c lib.
2. constructors never return anything .. not even `void` type
3. two types of constructors : `default constructor` and `parameterised constructor`.

```cpp
class constr {
    private:
        int a, b;
    public:
        constr() // default constructor
        {
            a = 4;
            b = 4;
        }

        constr(int arga, int argb) // parameterised constructor
        {
            a = arga;
            b = argb;
        }
}
```

## destructor

1. destructors are like deinit routines of a c lib. 
2. destructors are called when the class object goes out of scope or when the program ends.

Example:

```cpp
class destr {
    private:
        int v;
    public:
        destr()
        {
            std::cout << "Constructor called"<< std::endl;
            v = 4;
        }
        
        ~destr()
        {
            v = 0;
        }
        
        int getVal()
        {
            std::cout << "Destructor called"<< std::endl;
            return v;
        }
};

f1()
{
    destr d;
    
    std::cout << d.getVal() << std::endl;
}

f2()
{
    destr d;
    
    std::cout << d.getVal() << std::endl;
}

```

## constructor overloading

1. constructors can be overloaded but the both constructors must have different number of args passed to them so that the g++ can find the corresponding one to call.
2. some uses could be for creating layers or creating default sets

```cpp
class overloadedC {
    private:
        int a;
    public:
        overloadedC()
        {
            a = 4;
        }
        
        // overloaded constructor
        overloadedC(int x)
        {
            a = x;
        }
        
        int getC()
        {
            return a;
        }
};

.. caller such as main()..

overloadedC o;
overloadedC o1(4);
```

## 'this' pointer

1. used to reference the object itself with in the object only. referencing outside the object is not allowed and produce compiler error.

Example:

```cpp
#include <iostream>

class thisobj {
    private:
        int var;
    public:
        thisobj()
        {
            var = 4;
        }
        int getThis()
        {
            std::cout << "this val:" << this << std::endl;

            // causes recursive loop because this is class itself and calling the function itself via this indirectly
            this->getThis();
        }
};

int main()
{
    thisobj obj;

    obj.getThis();
}
```

### STD API

**1. make_shared and shared_ptr**

include `<memory>` compile with `-std=c++11` option. otherwise you get error regarding the type such as `var does not declare in this scope` or `var does not name a type`.

1. `make_shared` allocates once and `shared_ptr` allocates twice

Example:

```cpp
auto var = std::make_shared<int>(10);  // creates shared pointer var and assigns the value at address to 10

std::shared_ptr<int> var(new int);  // creates a shared pointer var

*var = 10; // assign the value at var to 10

std::shared_ptr<int> var(new int(10)); // creates a shared pointer var and assigns the value at the address to 10
```

Another example: using `make_shared` in class

```cpp
class makeSharedClass {
    private:
        int var;
    public:
        makeSharedClass()
        {
            var = 4;
        }
        // overloaded constructor
        makeSharedClass(int a)
        {
            var = a;
        }
        int getClass()
        {
            return var;
        }
};

.. in main()..

auto var = std::make_shared<makeSharedClass>(); // creates a var pointer of type pointing to makeSharedClass
auto var1 = std::make_shared<makeSharedClass>()->getClass(); // gets value returned from getClass() method.
auto var2 = std::make_shared<makeSharedClass>(4); // create a var but call the overloaded constructor for direct assignment

std::cout <<"var:" << var->getClass() << std::endl;
std::cout <<"var1:" << var1 << std::endl;
std::cout <<"var2:" << var2->getClass() << std::endl;
```

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

8. adding strings is easy: use `+` operator, its overloaded when using strings.

Example:

```cpp
#include <iostream>

int main()
{
    std::string str1 = "string1 ", str2 = "string2", str;

    str = str1 + str2;

    std::cout <<"string:" << str1 + str2 << std::endl;
}
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

# CMAKE

1. Cmake is a build system especially used for C++ programs.

Example for compiling a small c++ program.

```cmake
cmake_minimum_required(VERSION 2.4)

project(CPPLearning)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

add_executable(namespace namespace.cpp) # Assuming you have namespace.cpp file
```

2. setup the cmake build system using

```shell
cmake .
```

3. compile

```shell
cmake --build .
```

4. more options

a) add c++11 to the build system

```cpp
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()
```


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

