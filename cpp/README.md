
# C and CPP Manual

## Intro

This is a work-in-progress reference manual that detail on the C, C++ and the parts of secure coding in C. This is basically what i learnt over the time. This is written in short and simple English and not to confuse the end reader.

Instructions to start the manual:

1. use Ubuntu OS.. i used Ubuntu to compile and run programs .. any Ubuntu >= 18.04 is ok. If you want to use the other OS, you are free to do so.. MacOS does `g++` and `gcc` as well similar to the Ubuntu. Windows, usually it is hard to setup but MinGW is one option. MinGW is here: http://www.mingw.org/
2. install gcc on Ubuntu.

```shell
apt install build-essential gcc g++ cmake
```

`cmake` is required for building multiple cpp files into one unit. This is similar to `Makefile` but more advanced and wraps around makefile as well. We describe and learn about this in coming sections.

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

#CPP programming

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

## 'new' and 'delete' operators

1. `new` and `delete` operators are used to allocate and free memory respectively.
2. they are similar to `malloc` and `free` in C.

Below example describe some of the vary many ways to do allocation of dynamic memory.

```cpp
new int_ptr = new int; // allocate only pointer to int
new int_ptr_array = new int[4]; // allocate pointer to array of integers
new char_ptr = new char[44]; // allocate string
new int_ptr_2 = new int(2); // allocate and assign value at int_ptr_2 to 2
new s = new struct mystr; // allocate a structure
```

3. `delete` operator is similar to the new.

To free one pointer use `delete pointer`.
To free an array of pointers use `delete [] pointer`.

4. calling `delete` on a NULL pointer has no effect.

**Example:**

```cpp
#include <iostream>
#include <cstring>

int main()
{
    auto int_ptr = new int;
        auto int_ptr_array = new int[5];
        auto str_ptr = new char[100];

        auto int_ptr_2 = new int(2);

        struct var {
        int i;
                char str[30];
        };

        int i;

        struct var v_a = {1, "Hello"};
        struct var *v1 = new struct var(v_a);

        *int_ptr = 5;

        for (i = 0; i < 5; i ++) {
            *(int_ptr_array + i) = i;
        }

        strcpy(str_ptr, "Hello");

        std::cout << "int:" << *int_ptr_2 << std::endl;

        std::cout << "intr_ptr:" << int_ptr << std::endl;
        std::cout << "int@ int_ptr:" << *int_ptr << std::endl;

        for (i = 0; i < 5; i ++) {
        std::cout << "* int_ptr[" << i << "]" << *(int_ptr_array + i) << std::endl;
        }

        std::cout << "string:" << str_ptr << std::endl;

        std::cout << "v_a: " << "i:" << v_a.i << "str:" << v_a.str << std::endl;
        std::cout << "v_b: " << "i:" << v1->i << "str:" << v1->str << std::endl;

        delete int_ptr;
        delete [] int_ptr_array;
        delete [] str_ptr;
}
```

5. if you think that there could be n number of values.. you could use the `vector` types than using the `new` followed with `delete` for managing and all. (like for example arrays or array of structures or any n types). For strings you can simply use `std::string` type.

## class

1. class is a very good form of object oriented representation of the software program.
2. class contain both data and functions (they call in cpp as member functions / methods)
3. class also has protection mechanisms such as : `private`, `protected` and `public`.
    1. `private` members of the class are accessible only with in the class by their member functions of the same class or from their friends. Friends are discussed further down the manual.
    2. `protected` members are accessible from the same members of the class and friends, but also members of the derived classes. derived classes are described further down the manual again.
    3. `public` members are accessible by anyone once the class is declared in any functions and by referring them from the object.

Example:

```cpp
class cls {
    private:
        int i;
    public:
        cls()
        {
            i = 4;
        }
        int getI()
        {
            return i;
        }
};
```

if any of the `private`, `public` or `protected` are not declared then the class become `private` automatically.

Example:

```cpp
#include <iostream>

class cls {
    int p;

    int getP()
    {
        return (p = 4);
    }
};

int main()
{
    cls p;

    std::cout << p.getP() << std::endl;
}
```

The above example will give compilation error because the method `getP()` is `private` automatically.


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

Another concept in this is copy constructor. Take an example below:

```cpp
class cons_class {
    public:
        int a;
        cons_class(int x)
        {
            a = x;
        }
        cons_class(cons_class &x)
        {
            a = x.a;
        }
};

int main()
{
    cons_class p1 (4);
    cons_class p2 = p1; // copy constructor called here
}
```

if the constructor is not created, then the compiler creates one by default.


## destructor

1. destructors are like deinit routines of a c lib. 
2. destructors are called when the class object goes out of scope or when the program ends.
3. use `~` symbol before the constructor name, then it becomes destructor. 

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

Alteratively a constructor/ destructor or a memeber function even could be written outside the class layout as well.. 

```cpp
class cpp_class {
    private:
        int i;
    public:
        cpp_class();
};

cpp_class::cpp_class()
{
    i = 4;
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

## namespaces

1. namespaces are used to organise the very large amount of source code to avoid name collisions (mainly).
2. a namespace can be nested within another namespace
3. namespaces can span into multiple source files / header files and the compiler combines them or extends them
4. once defined the namespace is accessed using the `using namespace` or the explicit access as `ns::var..`.

Below example provide an overview of the namespace usage:

```cpp
#include <iostream>

// namespace that's basic
namespace variable
{
    int val = 0;
}

// nested namespace
namespace dev
{
    namespace naga
    {
        int val = 1;
                //class with in namespace
        class devnaga {
            private:
                int a;
            public:
                devnaga()
                {
                    a = 2;
                }

                int getA()
                {
                    return a;
                }
        };
    }

        // declaring class object with in the namespace
        naga::devnaga p;
}

// extending namespace
namespace variable
{
    int var = 3;
}

namespace dev {
namespace naga
{
    int var = 4;
}
}

// alias of dev::naga namespace
namespace _newdev = dev::naga;

int main()
{

    // declare a class within the namespace
    dev::naga::devnaga p;

    std::cout << "val::variable:" << variable::val << "variable::var:" << variable::var << std::endl;
    std::cout << "dev::naga::val:" << dev::naga::val << "dev::naga::var:" << dev::naga::var << std::endl;
    std::cout << "getA():" << p.getA() << std::endl;
        std::cout << "getA_new():" << dev::p.getA() << std::endl;
        std::cout << "val_newdev:" << _newdev::val << std::endl;
}
```

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

3. setting `cmake` standard

```cmake
if(NOT CMAKE_CXX_STANDARD)
   set(CMAKE_CXX_STANDARD 14)
endif()
```

4. setting `cmake` compiler

```cmake
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra)
endif()
```

# Cyber security - Secure coding practises

#### Links:

1. https://wiki.sei.cmu.edu/confluence/display/c/PRE31-C.+Avoid+side+effects+in+arguments+to+unsafe+macros#space-menu-link-content
2. https://www.w0lfzhang.com/2018/01/17/ASUS-router-stack-overflow-in-http-server/

### Details and Analysis of common vulnerabilities / issues in the programming:

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

**2. Accessing variable that is going out of scope**

Consider the below example..

```c
static int *ptr;
void getPtr()
{
    int data = 10;

    ptr = &data;
}

.. in main ..

getPtr();
printf("ptr value is %d\n", *ptr);
```

The variable `data` is local to the function `getPtr()` and the `ptr` is assigned the address of variable `data`. The data scope is within the `getPtr()` function and outside the stack is cleaned up and so the variable `data` memory. Thus the pointer ptr points to an invalid memory after the call to getPtr() resulting in an undefined output.

