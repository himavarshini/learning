
![alt text][C_C++_Manual]

[C_C++_Manual]: C_C++.jpg "Logo Title Text 2"





# C and CPP Manual


## Table of contents
**1. Intro**

**2. C Programming**

**3. C++ Programming**

**4. CMAKE**

**5. Cybersecurity Best practices and Secure coding**


-----------

## Abbreviations

| Name | Description |
|------|-------------|
| gcc  | GNU C Compiler |
| g++  | GNU C++ Compiler |
| STL  | Standard Template Library |


------------


## Intro

This is a work-in-progress reference manual that detail on the C, C++ and some of the parts of secure coding in C. This is basically what i learnt over the time. This is written in short and simple English and not to confuse the end reader. I am not a native english speaker. So, if you come across any silly blunders and spell mistakes, please do not hesistate to correct and provide me patch at `devendra.aaru@gmail.com`. Appericate it !

**How to read this manual:**

**The readers intended are basic (and the ones that are starting in C and C++ programming), intermediate and may be serve as a reference or dictionary or a goto guide for the advanced programmers.**

1. many topics are started from basic and goes down the line and deep on particular topics more.
2. sometimes the topics that are worth describing will be explained there itself than going to the next section like in a conventional way.
3. the book is not very organised but in a random selection of topic that are sprinkled everywhere. Please bear with this in mind while reading.
4. sometimes new concepts are being used in the initial parts of the book as well (describing macros at the start of the C example..), this lets the flow in this book going while the new reader might find it hard to understand and keepup. Please bear that many of such concepts are covered and are going to be covered in depth.

There are lots of coding examples and fully written code than any other C or C++ book anyone have ever read.

Instructions to start the manual:

1. use Ubuntu OS.. i used Ubuntu to compile and run programs .. any Ubuntu >= 18.04 is ok. If you want to use the other OS, you are free to do so.. MacOS does `g++` and `gcc` as well similar to the Ubuntu. Windows, usually it is hard to setup but MinGW is one option. MinGW is here: http://www.mingw.org/
2. install gcc and g++ on Ubuntu.

```shell
apt install build-essential gcc g++ cmake
```

`cmake` is required for building multiple cpp files into one unit. This is similar to `Makefile` but more advanced and wraps around makefile as well. We describe and learn about this in coming sections.

All the code examples are at [here](https://github.com/DevNaga/gists/tree/master/cpp)

**Author**: *Dev Naga* `<devendra.aaru@gmail.com>`

**CopyRight**: **DevNaga**. All rights reserved. The work is purely based on what i have learnt over the time of writing this document about C, C++, Secure coding and other topics described in this manual.

**LICENSE**: [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0)

For any bugs in the manual / in the code contact me at the above mentioned email address.

---------

# Source code conventions

1. I use VSCode..which i prefer.. you choose any editor you like (Atom, Sublime, Vim, Emacs, Notepad++ are some of good ones!)
2. I follow tab width of 4 (VScode defaults)
3. I give spaces instead of tabs in the entire source code that's in the book
4. The code following the `public` keyword or the `private` keyword will have 4 spaces
5. `if` and `else` will have the braces beside them just like `for`, `while`, `class`, `struct`, `union` .. like `if (condition) {`
6. functions will have the braces below them and not beside.. functions are more privileged that way

---------


## 1. Introduction to Compilers

At this point, i am guessing you already have a version of compiler and most preferrably `gcc` or `g++` on a linux / windows machine. Check `gcc -v` to see the version of your gcc compiler installed on your ubuntu.

1. Usually `gcc` is the preferred compiler for C programs and `g++` is for the C++ programs.
2. The compilers implement the programming language and works as a translational unit that converts the program written in C and C++ into the binaries that are used to run on the hardware.
3. there are many stages in the compiler.
    1. preprocessor
    2. compilation
    3. assembly
    4. linking

4. The pre-processor (usually is `cc1`) converts the program to high level language that the compiler understands. it finds out the header files and appends them to your program. if there are multiple header files, then it appends them all, and if there are repeated header files, it then as well appends only one of them.
5. if there are any macro definitions, it translates them and expands them into code and pastes them into the portions where they are called. We will  / going to discuss about macros in the coming parts of this.

**Example:**
```c
#include <stdio.h>

#define PREP_TEST(x) (x+4)

int main()
{
    printf("message is %d\n", PREP_TEST(4));
}
```

pre-processing stage:

```shell
gcc -E prog.c
```

Would produce the result as:

```shell
.. stdio.h header output ..
extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 942 "/usr/include/stdio.h" 3 4

# 2 "prep_test.c" 2




# 5 "prep_test.c"
int main()
{
    printf("message is %d\n", (4 +4));
}
```
observe the `#define PREP_TEST` in the C code is replaced with its code after preprocessor. This is called macro expansion.

6. compilation stage involve converting the pre-processor code into the assembly code for a corresponding target architecture. Here's the trick is the compilation target that analyse and replaces instructions to that target architecture.

```shell
gcc -S prog.c
```

7. Assembler converts the input code into object code. Object code is then contains the instructions for the target architecture.

```shell
gcc -c prog.c
```

8. Linking process involve finding the function call dependencies and library dependencies and adds the corresponding linker referencecs in the object code, something such as a pointer address when called the function. the outcome of this is the final binary that can be run on the target platform. Usuaally, the target binary names would be `a.out` in unix (if the compiler -o option has not been given).

Once the program that you have compiled, is loaded into memory for execution, the loader then is responsible for loading the function into the memory and execute it.

-----------------------

## 2. C Programming

### intro

The C programming language is created by a legendry programmer **Dennis Ritchie**. He himself put around 4 or 5 out of 10 when someone asked him the expertise in C. This is because of the vast programmability and its minimal footprint on the final binary makes it a programming language to code a program in infinite variations.

1. Use any text editor to code in C, Like i use `vi` editor or `vscode` from microsoft is also good.
2. every program in C, starts with header file definition something like `#include <stdio.h>` . This section is called the header file declaration section. Header files contain most important information about various definitions and declarations of the variables and types. We will discuss these in coming chapters.
3. every C program starts with `main()` function. Function is a body that contains a group of statements and be executed when the function is called, if not called they wont be executed. So, if `main()` is a function , then who calls `main()` ?
4. C program follows many syntax rules, they are described in below sections. The source files in C follow the extension `.c` and header files follow the extension `.h`, many editors will colorise and customise the source code as soon as they see this extensions. The compiler would require the extensions to be present as well. If you are new to write programs in C and C++ then it is best to use the editor which colorise the keywords and variables for you.

For example a C program looks like the following:

```c
#include <stdio.h>   // header file

int main() // main function
{
    printf("Hello C\n");     // printf call

    return 0;   // return statement
}
```

1. In the above program the header file that we discussed `<stdio.h>` is being declared. Each header file follows a `#` and `include` statements defining that to include this file into the program.
2. The function `main()` is called but before that `int` is kept, the `int` type is basically returned by the `main()` function. Every function in C program may or many not return a value. so in our `main()` above there, returns an int, like the last statement `return 0` returning integer 0. A function can return anything and nothing.
3. The function `printf()` is called with argument `"Hello C\n"`. argument is basically what the type of variable a function accept. There can be variable arguments to the function and are covered in coming sections of this manual. The `"` is the usage to define a string. string is basically a group of characters followed by a null terminator. a null terminator defines where the string end. the null terminator is basically `\0`. it is not `o` but is `0`.
4. the `\n` is basically a new line. when `printf()` prints the message on to screen, the new line is printed after the last character is being printed.
5. the `//` is comment. comments are basically used to describe what the line of code means. One can meaningfully define what the particular part of the source code really means. Anything in english language can be written in the comment section

### streams (`stdin`, `stdout` and `stderr`)

There are 3 file streams in the C program called

1. `stdin` - input stream (takes input from screen console)
2. `stdout` - output stream (outputs to screen console)
3. `stderr` - error stream  (outputs to screen console)

the function `printf` points to output stream called `stdout`. The `stdout` stream is a buffered stream and the `stderr` is an unbuffered stream.

functions such as `fprintf` are on error stream `stderr`.

functions such as `scanf` are on input stream `stdin`.

when printing too many messages on the screen the `fprintf` is prefered because it is unbuffered than using `printf`.

One such an example is when printing the messages over the serial console..

### variables and types

C has many types to represent the data. The following are the types. Type represent the data its holding and its size.


| type | size | range |
|------|------|-------|
| `char` | character of one byte in size | -127 to 127 |
| `unsigned char` | unsigned char | 0 to 255 |
| `short int` | signed short integer of two bytes | -32768 to 32767 |
| `unsigned short int` | unsigned short int of two bytes | 0 to 65535 |
| `int` | signed integer of 4 bytes | -2147483648 to 2147483647 |
| `unsigned int` | unsigned integer of 4 bytes | 0 to 4294967295 |
| `void` | type of void | - |

There are more formats as `long`, `unsigned long`, `long long` types, however they are not very practical.

The ranges are defined in the header file `<limits.h>`.

The header file `<stdint.h>` contain somemore tyes such as below.

| type | size | range|
|------|------|------|
| `int8_t` | 1 | -127 to 127 |
| `uint8_t` | 1 | 0 to 255 |
| `int16_t` | 2 | -32768 to 32767 |
| `uint16_t` | 2 | 0 to 65535 |
| `int32_t` | 4 | -2147483648 to 2147483647 |
| `uint32_t` | 4 | 0 to 4294967295 |
| `int64_t` | 8 | - |
| `uint64_t` | 8 | - |

A variable can be declared as the following

```c
char c; // character variable
unsigned int i; // unsigned integer variable
uint8_t a[4]; // unsigned array of 4 one byte integers
uint32_t i; // same as the unsigned int i
uint64_t big_i; // unsigned 64 bit integer
char str[40]; // string of length 40
```

let's define a program this way:

```c
#include <stdio.h>

int main()
{
    short int i;
}
```

There is another concept called the **scope and lifetime of the variable**. Here's one example,

```c
root@linux# cat 1.c:

int a;

int func()
{
    a = 4;

    return 0;
}

int main()
{
    func();
    printf("value of a %d\n", a);
}
```

Here the variable `a` is with global scope and it will be accessible by any function in the file `1.c`. The variable `a` is said to be a **Global variable**. The lifetime of the varilable `a`, meaning how long the variable can live, is the program lifetime or till the `main()` function ends.

consider another example below,

```c
root@linux# cat 1.c:

int func()
{
    int a = 4;

    return a;
}

int main()
{
    int a;

    a = func();
    printf("value of a %d\n", a);
}
```

The variable `a` is here said to have a **local/ function scope** and is then called a **Local variable**. The variable `a` in functions `func()` and `main()` does not cause a double declaration compilation warning/error. It is said to have the scope local and thus is valid with in that function only. The lifetime of the variable `a` in function `func()` is said to have its lifetime only the lifetime of the function `func()` (lifetime of `func()` is the execution time of the `func()`) and the same apply to variable `a` in `main()`.

The below example will provide some reference on what is called **typecasting**. The **typecasting** is most important along with the function prototyping when writing software for automotive and aeronautics systems.

```c
#include <stdio.h>

int main()
{
    double val;
    
    val = 1 / 10;
    
    printf("%f\n", val);
}
```

The above program must print `0` because the compiler treats the right hand side of the expression contain both the `int` values and thus the result. So care must be taken when the other end (left hand side) expression is of different type. So the fixes are many such as below..

```c
val = 1 / (double)10;
```

typecast 10 to double. or,

```c
val = 1 / 10.0;
```
make 10 as 10.0 or,

```c
val = 1.0 / 10;
```
make the top 1 as 1.0.

This way the compiler can treat the variables now one of them as double and generates the assembler code to evaulate to double.




Below are some of the most useful API need to be understood before we go in subsequent sections...

1. `printf`:

The `printf` function prints the message on the screen. Below are some of the ways to print the data on the screen.

**Printing integers**

```c
int a = 4;

printf("%d\n", a);
```

The `%d` is a format specifier to print an integer.

**Printing unsigned integers**

```c
uint32_t a = 4;

printf("%u\n", a);
```

The `%u` is a format specifier to print an unsigned integer.


**Printing a string**

```c
char *str = "Hello C";

printf("%s\n", str);
```

The `%s` is a format specifier to print a string.


**Printing a character**

```c
char c = 'C';

printf("%c\n", c);
```

The `%c` is a format specifier to print a character.

**Printing hex values**

```c
uint32_t val = 0x04;

printf("0x%x\n", val);
```

The `%x` is a format specifier to print a hexadecimal value.. the `0x` before it is a string

**Priting a double**

```c
double val = 4.4;

printf("%f\n", val);
```

The `%f` is a format specifier to print a double value



2. `scanf`:

There's not much about `scanf` and is rarely is used in any newer version of the software .. so we are not gonna much concentrate on this one here.


baseline format specifiers are listed below.. 

| format specifier | type |
|------------------|------|
| %d | `int` |
| %u | `unsigned int` |
| %ld | `long int` |
| %lu | `long unsigned int` |
| %ju | `unsigned long long int` |
| %f | `float / double` |
| %s | `string` |

### Loops and conditional statements

Loops are sections of the code that the program wants the computer to be executed repeatedly or till a condition. Loops in C are coded with `while`, `for` and `do while`. conditions can be written with `if`, `if..else`, `if..elseif`. One can write loops by using `if` and `goto` statement as well. Some programmers may find `goto` as most dangerous way to write software, it depends on the way and path it is being used at in a program.

#### `if` statement

`if` statement holds in a condition and if the condition is set to be true, then the statements with in the if block are executed and if not the statements in the block are not executed.

usually the `if` is followed with atleast one or more of statements such as following..

```c
if (apples != oranges) {
    printf("these are apples\n");
}
```

The same example above can be written in the following way as well..

```c
if (apples != oranges)
    printf("these are apples\n");
```

now, since the `if` has only one statement to execute within it, thus braces are not required. Let's say there are more than one statement, then one must use the braces to enclose the statements to be executed with in `if`. This may go in as a conding style in organisations (or in opensource projects such as Linux) but following first one is always desirable. The reason being that its less ambiguous and provide more clarity while reading the source code back again.

Consider the below example:

```c
int apples = 6;
int mangoes = 7;

if (apples > mangeos) {
    printf("apples are more in number than mangoes\n");
} else {
    printf("mangoes are more in number than apples\n");
}
```

The statement above is `if` and `else` followed with it. The statement `if` is used to check for truth in the condition and if that truth is passed, then the statements with in the if's opening and closing brace `{` and `}` respectively, will get executed. If the condition is false within the `if` statement then the `else` will be executed.

Consider another example below:

**Example:**
```c
int main()
{
    else {
        printf("Hello\n");
    }
}
```

will give you a compilation error because **the `else` shall always be followed with an `if` statement.**

Consider another example:

```c
typedef enum {
    MANGOES,
    APPLES,
    BANANA,
    AVOCADO,
} fruits;

fruits f;

if (f == MANGOES) {
    printf("chosen Mangoes\n");
} else if (f == APPLES) {
    printf("chosen Apples\n");
} else if (f == BANANA) {
    printf("chosen Banana\n");
} else if (f == AVOCADO) {
    printf("chosen Avocado\n");
} else {
    printf("none choosen\n");
}
```

The above statement has one more new definition called `enum`. `enum`eration often is useful to represent constants or group them together into one to serve one kind of purpose. In above example we grouped MANGOES, APPLES, BANANA, AVOCADO into fruits. (see that we have used new feature **typedef** and this is explained in below sections)

Alternatively we could simply use pre-processor statements to define them as well such as ..

```c
#define MANGOES 0
#define APPLES 1
#define BANANA 2
#define AVOCADO 3
```

but when looking at it, we merely cannot identify what they really represent in first glance till we look at their use in the code.

The first constant in the `enum` is always set to 0 by default by the compiler. The next elements are an increment of their previous element. such as the following

```c
typedef enum {
    REG_REQ = 1,
    REG_RESP,
    UNREG_REQ,
    UNREG_RESP,
} request_type_t;
```

the `REG_REQ` is explicitly set to 1 and thus the `REG_RESP` will be set to 2 and so on..

Let's say the following, setting the `UNREG_REQ` makes `UNREG_RESP` go +1 higher than this..

```c
typedef enum {
    REG_REQ = 1,
    REG_RESP,
    UNREG_REQ = 10,
    UNREG_RESP,
} request_type_t;
```

printing the above contants will tell us the compiler behavior on `enum` constants. Lets' get back to original program about mangoes..


The statement above has a new conditional statement called `else if` that is always followed by the `if` statement just like the `else` follows an `if`. In `else if` you must add a conditional statement just like you add in the `if` statement. This above example is one of the forms of `if - elseif` ladder. An `else` in an `if` .. `else if` ladder can be placed at the end of the last `else if` statement.

enums are basically int types so that means they are 4 bytes in length and that means we can use like below..

```c
typedef enum {
    PROTOCOL_VERSION_SET = 0x01,
    ADDR_TYPE_SET = 0x02,
    STATION_TYPE_SET = 0x04,
    STATION_COUNTRY_CODE_SET = 0x08,
} geonetwork_bitsets_t;
```

the above one is a legit enum definition and can be used anywhere else.. the idea is that now all the values are grouped in one place in a enum type not like the `#define` way of macro'ing everything and confuse what represents what. This way it is more meaningful.

### switch statement

#### `for` statement

`for` statement contains 3 steps. first is to assign, second is condition check and third is increment / decrement. one can avoid all 3 statements (that is an infinite loop).

```c
for (initialise; control ; increment / decrement);
```

an example of printing numbers from 1 to 100 is below.

```c
int no;

for (no = 1; no <= 100; no ++) {
    printf("%d\n", no);
}
```

the same example eliminating initialisation can be written as below..

```c
no = 1;

for (; no <= 100; no ++) {
    printf("%d\n", no);
}
```

#### `while` statement

### typedef

`typedef` is generally used to name a variable or a type. something like in a project if a variable or the type is to be named for the purpose of the project. Something like the below..

```c
struct __looper_list {
    int timeout;
    void (*callback)(void *data);
};
```

we declare the variable of type `struct __looper_list` as

```c
struct __looper_list item;
```

into something meaningful as 

```c
typedef struct __looper_list looperSet;
```

and then use the new type to define variables of the type as

```c
looperSet item;
```

more important usecase is the enums. i do really use typedefs when required and only with enums, like i did in the first example where you have seen typedef'ed enums.. 

```c
typedef enum {
    DIRECTION_NONE = 0x01,
    DIRECTION_FWD = 0x02,
    DIRECTION_REV = 0x04,
} direction_t;
```

`typedef` is encountered in almost all C projects that are in Github.. it makes reading the code easier and more understandable..

### pre-processor statement

1. preprocessor macros are used for various purposes such as from defining or giving names to values to a function look alikes for performance reasons. Calling functions too often may lead to a function call-and-return overhead. Thus, in most of the time the few lines of that source code could go in as a preprocessor macro.

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

above is a multi-line macro.. observe the `\` line after the each line till the end. To group all the statements with in the macro function usually `{` and `{` are used. usually the better example is below..


```c
#define _factorial(_val, _fact) { \
    if (_val <= 0) { \
        _fact = 1; \
    } else { \
        int _i; \
        _fact = 1; \
        for (_i = 1; _i <= _val; _i ++) {\
            _fact *= _i; \
        } \
    } \
}
```

sometimes, even more function like macros are useful where using them is more efficient than doing a function call. (i have no idea to be honest why..)


few notes to consider:

1. most of the times, the function like macros cannot be used within `if` condition and such cases shall be prohibited from the code.
2. macro expansion may lead to the compiler errors / runtime behavior change because of the variables being used are same as well in macro, (shadowed) and to avoid the cases, some preced each variable a `_` and defines variables without it.
3. do not use function like macros unless otherwise it is really really constrained hardware that the program is executing on. They cause more trouble than gaining those small speeds in execution


3. The **#ifdef** ..

4. the **#error**

5. gcc specific macros

### arrays

Arrays are group of variables of same type. Examples are an array of integers, an array of characters (in this case is string) or array of floats.

defining an array is simple in C.

```c
int a[5];
```

defines an array a with 5 integers.

Accessing the elements of the array is simple as well.. the array index starts from 0 and goes till 4 (because size 5 and in C the indexing starts from 0).

| a[0] | a[1] | a[2] | .. | a[n] |
|------|------|------|----|------|

```c
#include <stdio.h>

int main()
{
    int a[44];
    int i;

    for (i = 0; i < sizeof(a) / sizeof(a[0]); i ++) {
        printf("a[%d] = %p\n", i, a + i);
    }
}
```


#### 2D arrays

two-d arrays are defined as follows..

```c
int a[5][4];
```

defines a 2-d array of dimemnsions 5x4. The array can fit 4 columns and 5 rows. that means it can fit integers of total 20.

**accessing two-d arrays**

writing:

```c
int i;
int j;

for (i = 0; i < 5; i ++) {
    for (j = 0; j < 4; j ++) {
        a[i][j] = j;
    }
}
```

reading:

```c
int i;
int j;

for (i = 0; i < 5; i ++) {
    printf("row [%d]\n", i);
    for (j = 0; j < 4; j ++) {
        printf("\t %d\n", a[i][j]);
    }
}
```

various other types can have the same array type

two-d array of strings (or called as array of strings)

```c
char string[100][40];
```

100 rows of strings of length 40 each.


uses of the two-d arrays (or especially arrays of multi dimensions) are wide in the current world. They are used to represent the rows and columsn of a csv file, or a black-and-white photograph (intensitiy of the black and white lights respectively..) or anything that deals with matrix multiplications and additions in more than one dimension.


#### 3D arrays

### structures

1. order and assignment

2. bit fields

3. the `__attribute__((__packed__))`

### unions

unions are similar to structures but are very different from them in terms of memory allocation by the compiler.

union is declared as the below..

```c
union u {
    int a;
};
```

the above snippet defines a union of type u. the variable `a` in the `union` is accessed by the reference operator `.` or `->` depending on how the union varialble is declared..

referencing with `.`:

```c
union u {
    int a;
};

union u u_;

u_.a = 4;

printf("value of a %d\n", u_.a);
```

referencing with `->`:

```c
union u {
    int a;
};

union u *u_;

u_ = calloc(1, sizeof(union u));
if (!u_) {
    return -1;
}

u_->a = 4;

printf("value of a %d\n", u_->a);
```

let's do `sizeof` on the union

```c
printf("union size %d\n", sizeof(union u));
```

gives us 4.

let's take an example of the following union

```c
union u {
    int a;
    int a1;
};
```

`sizeof` on this gives us 4 as well. 

The reason being that any number of variables that are defined in the union, the largest variable size will become the size of union.

let's take another exmaple

```c
union u {
    int a;
    double a1;
};
```

`sizeof` on this gives us 8. its because double is larger.

so let's print the values with in the union..

```c
#include <stdio.h>

int main()
{
    union u {
        int a;
        int a1;
    };

    union u *u_;

    u_ = calloc(1, sizeof(union u));
    if (!u_) {
        return -1;
    };

    u_->a1 = 4;

    printf("size of union %d\n", sizeof(union u));
    printf("a %d a1 %d\n", u_->a, u_->a1);
}

```


the variable a1 is set to 4. the a as well set to the same value. the reason being that the union allocates the 4 bytes because the largest element is of size 4 bytes and the variable a1 can fit the 4 bytes with value 4 and thus a is sharing the same memory and accesses same value.

lets' say the below program

```c
#include <stdio.h>

int main()
{
    union u {
        int a;
        char a1;
    };

    union u *u_;

    u_ = calloc(1, sizeof(union u));
    if (!u_) {
        return -1;
    };

    u_->a = 0x00404040;

    printf("size of union %d\n", sizeof(union u));
    printf("a 0x%x a1 %x\n", u_->a, u_->a1);
}

```

would print `a` as `0x00404040` and `a1` as `0x40` because the a1 is a char variable and when accessed by the `printf` only 1byte of the memory will be accessed and that is the last byte of a.


unions are usually discouraged to be used in programs that involve transaction between more than one system, and when memory is enough available, usually structures are prefered over unions.



### pointers


### sizeof operator

Any size of a variable, structure, data type can be obtained using `sizeof` operator. See some of the few nice examples below.

```c
int i;

sizeof(int); or sizeof(i)  //mean the same

struct var {
    int i;
};

struct var v;

sizeof(struct var); or sizeof(v); // mean the same

struct var v[2];

// to find the number of elements in this above v[2], we do.

num_elem = sizeof(v) / sizeof(v[0]);

int *i;

sizeof(*i); and sizeof(i) mean the same but ..

struct var_struct *v;

sizeof(v) and sizeof(*v) does not mean the same.

the sizeof(v) would give you the sizeof a pointer but the sizeof(*v) gives you the sizeof the structure struct var_struct.
```

### The `?:` operator

The `?:` is an operator that has `?` check for truth statement and the rest of the statements between `?` and `:` and after `:` work based on the evaluation before `?`.

See an example below.

**Example:**

```c
#include <stdio.h>

int main()
{
    int i = 1;

    printf("%s\n", (i == 1) ? "i is 1": "i is not 1");
}
```

Here's the explanation about the above example:

1. The statement `(i == 1)` before the `?` is a condition that gets evaulated first.
2. The statement `"i is 1"` is executed if the `(i == 1)` holds truth.
3. The staetement `"i is not 1"` is executed if the `(i == 1)` holds failure.

The following statement,

```c
    int i = 1;

    (i == 1) ? return 1: return 0;
```

does not compile and is not valid. However the modified statement,

```c
    int i = 1;

    return (i == 1) ? 1: 0;
```

is valid statement and retturns 1.

The `?:` is useful when you do not want to write an `if` and `else` statement and to represent the code portion in a conscice manner.


### Functions

Functions in `C` are the efficient way to organise and group the source code. A function will have a declaration and a definition. Definition holds the body of the function and declaration declares the function with its prototype.

Every function may contain the arguments and returns a value. A function may not even have an argument and may not haev even the return type. Such function are not very useful in the real world however.

Here's one example:

```c
void function(void); // function takes no arguments and returns nothing.
void function(int a, double f); // function takes integer argument and a double and returns void
void function(struct struct_var s); // function takes a structure as an argument and returns void
int function (int a, struct var s); // function takes an int and a struct as argument and returns an int
```

it is always advised to declare functions before calling them. The reason being that in C the return (atleast with `gcc`) type is always `int` and the function accepts no arguments. So, it looks something like this.

```c
int function(void);
```

Take a look at the example below..

**Example:**

```c
#include <stdio.h>

int main()
{
    double f1 = f();
    printf("val %f\n", f1);
}

f()
{
    return 44.1;
}
```

compiling the above program gives us the following warnings:

```shell
c/default.c: In function ‘main’:
c/default.c:5:21: warning: implicit declaration of function ‘f’ [-Wimplicit-function-declaration]
         double f1 = f();
                     ^
c/default.c: At top level:
c/default.c:9:1: warning: return type defaults to ‘int’ [-Wimplicit-int]
 f()
 ^
```

see the line 9, the compiler defaulting the return of `f()` to int, however it meant to return the type to double. The new compilers now smart enough to make the following program fail compilation giving out the following errors.

Take a look at the modified example below, the function `f()` returns `double` now.

```c
#include <stdio.h>

int main()
{
        double f1 = f();
    printf("val %f\n", f1);
}

double f()
{
    return 44.1;
}
```

See the  below line 9.

```shell
c/default.c: In function ‘main’:
c/default.c:5:21: warning: implicit declaration of function ‘f’ [-Wimplicit-function-declaration]
         double f1 = f();
                     ^
c/default.c: At top level:
c/default.c:9:8: error: conflicting types for ‘f’
 double f()
        ^
c/default.c:5:21: note: previous implicit declaration of ‘f’ was here
         double f1 = f();
                     ^
```

The correct fix to the program is to have a prototype in the C code. Please see the modified example below..

```c
#include <stdio.h>

double f();

int main()
{
        double f1 = f();
    printf("val %f\n", f1);
}

double f()
{
    return 44.1;
}
```

#### Static functions

A function can be called anywhere with in the same program. This statement does not hold true at all the times. usually a function can be scoped as well just like a variable. (local or global) 

in this case a function can be scoped to be with in a file and never be called from other files. Let's take below code.

file1.c

```c
int get_market_rate()
{
    return 10;
}
```

file2.c

```c
int main()
{
    int market_price = get_market_rate();

    printf("marketprice %d\n", market_price);
}
```

when the above two files are compiled together as in `gcc file1.c file2.c` would let the main print the market price. Let's say we add static to the `get_market_rate`.

file1.c

```c
static int get_market_rate()
{
    return 10;
}
```

now when we compile `gcc file1.c file2.c` then we get a linkage error saying `undefined reference to get_market_rate()`. That is because the function scope is now limited to file1.c itself.

Why anyone wants to limit function scope. Many reasons to it.. such as 


1. name collision with other functions with in different files and thus limit their scope
2. reduce the exposure of functions to just within the file and otherwise not required - like the way in c++

Eitherway, usage of static functions reduce the ambiguity and clutter.

### string manipulation API

### Allocation API (`malloc` / `calloc` and `free`)

### static and global variables

If a variable is declared global in the c code above all the functions that are written, then it has the full scope of the binary program. All or any function with in the binary can access this variable (referencing via `extern`).

If a variable is declared global and static then the scope is limited to the file. All functions with in the same file can access this but not the functions outside.

If a varialbe is declared static and with in the function, then it has only file scope and only the function can access it.

### FILE I/O

FILE I/O in C is done using the C lib. Alternatively one can use directly the lower layer calls provided by the OS such as linux does provide syscalls to do file operations. Both are described in this section.

Below program describe a basic file reading in C.

```c
#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *fp;
    
    if (argc != 2) {
        fprintf(stderr, "<%s filename>\n", argv[0]);
        return -1;
    }
 
    // open the file given from command line
    fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "failed to open %s \n", argv[1]);
        return -1;
    }
    
    char buf[1024];
    
    while (fgets(buf, sizeof(buf), fp)) {
        printf("input <%s>\n", buf);
    }
    
    fclose(fp);
    
    return 0;
}
```

**Example: basic file i/o**

FILE I/O functions

| function | description |
|----------|-------------|
| `fopen` | open the file given name and mode |
| `fgets` | read a line of text from the input into the buffer pointed |
| `fprintf` | write formatted contents into the file pointer pointed |
| `fscanf` | read formatted contents from the file pointer pointed |
| `fseek` | seek to a specific position in the file |
| `fclose` | close file pointer |


The `FILE` is a type that holds information about the opened file. When `fopen` is called, it returns the pointer of type `FILE`, on success and on  failure `NULL` is returned.

`fopen` prototype is as follows.

```c
FILE* fopen(char *filename, char *mode);
```

where `filename` is the file to be opened, and `mode` represents the following.

|mode | description |
|-----|-------------|
| "r" | read only |
| "w" | write only | 
| "a" | append mode  (write at the end of the file) |
| "rb" | read binary mode only |
| "wb" | write binary mode only |
| "ab" | append binary mode only |

A simple use of the `fopen` is below..

any opened file must be closed with `fclose` function. the `fclose` prototype is as follows.

```c
void fclose(FILE *fp);
```


```c
int main(int argc, char **argv)
{
    FILE *fp;
    char input[1024];
    
    fp = fopen(argv[1], "w");
    if (!fp) {
        fprintf(stderr, "failed to open file in write mode %s\n", argv[1]);
        return -1;
    }
    
    fprintf(stderr, "write anything to dump in %s..\n", argv[1]);
    fgets(input, sizeof(input), stdin);
    fputs(input, fp);

    printf("successfully written to the file..\n");
    fflush(fp);
    fclose(fp);
}
```

Operating system does not guarantee the writes to be done at the instant when written. If that is the requirement (writes happening immediately) then `fflush` function is to be used to accomplish the job.

`fflush` flushes the given stream immediately causing the system to write contents directly on the stream. Its prototype is as follows.

`int fflush(FILE *fp);`

doing `fflush(fp)` on an `fp` that is opened in write mode causes it to immediately write the contents.

**Linux File i/o**:

Linux file i/o is described here is very simple and not part of the C, but the syscall interface allows to code in C/ C++.

| syscall | description |
|---------|-------------|
| `open` | open the file |
| `read` | read from the file |
| `write` | write to the file |
| `close` | close the file |


### Data structures

#### Linked Lists

#### Doubly linked lists

#### Queues

#### Stacks

#### Hash tables

#### Trees

#### Graphs

### FAQ

1. to use C code inside the cpp use `extern "C" {"` and the `}` when the `C` portion of the program end.
2. The constant PI is defined as `M_PI` in `<math.h>`.
3. The types such as `uint32_t` are part of `<stdint.h>`.


----------------

# CPP programming

C++ is invented by **Bjarne Stroustrup**, while he was trying to extend C for object oriented approach. C++ is an improvement over C, however, a lot of changes being done in recent years that makes it more and more advanced and faster to program than in C. This makes up a large amount of base being dedicated in C++ to the standard libraries and libraries using STL (Standard Template Library) mechanism (such as **boost library**.). The C++ is the starting point of the modern object oriented programming approach.

## Intro

1. Many C++ standards came in. Most prominent are the C++11 and C++14. Between each standard there are so many improvements and major new features (such as lambda functions in C++14)
2. C++ gets much more hands-on if `python` learnt first and then C++.


```cpp
#include <iostream>

int main()
{
    std::cout << "Hello C++\n";
}
```

One thing that is easily noticeable is the header file missing `.h` extension. C++ does not require the `.h` presence and is optional. The extension for a C++ file are `.cpp` and `.hpp`.

some books / manuals / sites may show the hello example this way as well..

```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello C++\n";
}
```

this example uses the `using namespace` directive. This means that the namespace std is being used and the keyword `cout` can be found in the `std::` namespace. so one does not need to explicitly write `std::` before `cout` to do scope resolution.

In this manual / book we are not going to use `using namespace` mainly because we would wanna learn and understand various APIs that are exposed by STL and other libraries in C++ as well some classes.

There are 3 API just like the `printf`, `fprintf` and `scanf` we have `cout`, `cerr` and `cin` in C++.


| function in C | equivalent in c++ |
|---------------|-------------------|
| `printf` | `cout` |
| `scanf` | `cin` |
| `fprintf` | `cerr` | 

**NOTE**: usually `fprintf` with stderr is treated as `cerr`.

Here are below examples of the 3 API:

**Example:  cout**

```cpp
#include <iostream>

int main()
{
    char hello_msg[] = "Hello";

    std::cout << hello_msg;
}
```

**Example: cerr**

```cpp
#include <iostream>

int main()
{
    char hello_msg[] = "Hello";

    std::cerr << hello_msg;
}
```

**Example: cin**

```cpp
#include <iostream>

int main()
{
    int n;

    std::cout << "Enter number: ";
    std::cin >> n;
    std::cout << "Number is "<< n << std::endl;
}
```

### FILE I/O


**Example: Writing into file**

```cpp
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    std::string input;
    std::ofstream fp;

    fp.open(argv[1]);
    if (!fp) {
        return -1;
    }

    fp << "Hello there" << std::endl;

    fp.close();
}
```

**Example: Reading from file**

```cpp
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    std::ifstream fp;
    std::string line;

    fp.open(argv[1]);

    if (!fp) {
        return -1;
    }

    std::getline(fp, line);

    std::cout << "line: " << line << std::endl;

    fp.close();
}
```

There are 3 types of io operations

| operation | meaning |
|-----------|---------|
| `std::ios::in` | input .. reading mode like the "r" |
| `std::ios::out` | output .. writing mode like the "w" |
| `std::ios::app` | append mode like the "a" |
| `std::ios::binary` | open file in binary mode |


**Example: Open in read and write mode**

```cpp
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    std::ifstream fp;
    std::string line;

    fp.open(argv[1], std::ios::in | std::ios::out);

    if (!fp) {
        return -1;
    }

    std::getline(fp, line);

    std::cout << "line: " << line << std::endl;

    fp.close();
}
```

**Example: Appending to a file**

```cpp
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    std::string input;
    std::ofstream fp;

    fp.open(argv[1], std::ios::out | std::ios::app);
    if (!fp) {
        return -1;
    }

    for (auto i = 2; i <= argc - 1; i ++) {
        fp << argv[i] << " ";
    }
    fp << std::endl;

    fp.close();
}
```

In the binary mode of operation the file writes must be done using `write` method.

|  member function | description |
|------------------|-------------|
| `.write(<reinterpret_cast<char *>msg, sizeof(msg))` | write the output buffer to file |
| `.flush()` | flush the `ofstream` .. not valid for `ifstream` |

**Example: Binary file operation**

```cpp
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    std::ofstream fp;

    int array[44];

    for (auto i = 0; i < sizeof(array) / sizeof(array[0]); i ++) {
        array[i] = i + 1;
    }

    // write file binary mode
    fp.open(argv[1], std::ios::out | std::ios::binary);
    if (!fp) {
        return -1;
    }

    // write file in binary mode
    fp.write(reinterpret_cast<char *>(array), sizeof(array));

    fp.close();


    std::ifstream fp_i;
    int array_i[44] = { 0 };

    fp_i.open(argv[1], std::ios::in | std::ios::binary);
    if (!fp_i) {
        return -1;
    }

    fp_i.read(reinterpret_cast<char *>(array_i), sizeof(array_i));

    for (auto i = 0; i < sizeof(array_i) / sizeof(array_i[0]); i ++) {
        std::cout << "array [" << i << "]: " << array_i[i] << std::endl;
    }

    fp_i.close();
}
```

**Example: reading a file and printing contents**

```cpp
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    std::ifstream fp;
    std::string str;

    fp.open(argv[1], std::ios::in);
    if (!fp) {
        return -1;
    }

    while (fp) {
        getline(fp, str);

        std::cout << str << std::endl;
    }

    fp.close();
}
```

**Example: file copy program written in C++**

```cpp
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    std::ifstream fp1;
    std::ofstream fp2;

    fp1.open(argv[1], std::ios::in | std::ios::binary);
    if (!fp1) {
        std::cerr <<"failed to open " << argv[1] << std::endl;
        return -1;
    }

    fp2.open(argv[2], std::ios::out | std::ios::binary);
    if (!fp2) {
        std::cerr <<"failed to open " << argv[2] << std::endl;
        return -1;
    }

    while (fp1) {
        std::string line;

        std::getline(fp1, line);

        fp2 << line << std::endl;
    }

    fp1.close();
    fp2.flush();
    fp2.close();
}
```

## overloading functions (polymorphysm)

1. same function name but different jobs depending on the type of input passed
2. useful when the job performed by the API is same irrespective of what the input is.. usually templates are the prefered approach for such kind of operation.

**Example:**

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

In the above example, the function `add()` does the same job irresepctive if the input is `int` or `double`.

see the error after compiling this example: that the last line when passed a double and an int. This is because the compiler
does not find a match with this type.

But when typecasting the value `2` to `(double)2` the code works again see the below:

```cpp
std::cout << "add result for a double and int <1.1 and 2>:" << add(1.1, (double)2) << std::endl;
```

2. if the function has same args the overloading is not possible
3. if the caller passes the variables of types that are not available in the target overloaded functions, then it is not possible to overload (care must be taken to 
pass the right options or use the typecasting - but typecasting is strictly not good in c++)


## 'new' and 'delete' operators (Allocation and Free)

1. `new` and `delete` operators are used to allocate and free memory respectively.
2. they are similar to `malloc` and `free` in C. However 

Below example describe some of the vary many ways to do allocation of dynamic memory.

```cpp
new int_ptr = new int; // allocate only pointer to int
new int_ptr_array = new int[4]; // allocate pointer to array of integers
new char_ptr = new char[44]; // allocate string
new int_ptr_2 = new int(2); // allocate and assign value at int_ptr_2 to 2
new s = new struct mystr; // allocate a structure
```

**Basic example:**

```cpp
#include <iostream>
int main()
{
    auto array = new int[5]; // allocate an array to hold 5 integer variable
    int i;

    // assigning the array elements
    for (i = 0; i < 5; i ++) {
        array[i] = i;
    }

    // print the elements of the array
    for (i = 0; i < 5; i ++) {
        std::cout <<"i:" << array[i] << std::endl;
    }
}
```

3. `delete` operator is similar to the `new`.

To free one pointer use `delete pointer`.
To free an array of pointers use `delete [] pointer`.

4. calling `delete` on a NULL pointer has no effect.

Full example using all sort of the calls with `new` and `delete` is below.

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

A traditional C functions can also be used to perform the similar job. See example below. include `<cstdlib>`.

**Example:**

```cpp
#include <iostream>
#include <cstdlib>

int main()
{
    int *ptr = (int *)malloc(4);

    *ptr = 4;

    std::cout << "ptr is:" << *ptr << std::endl;
}
```

in the above example, we see that the `malloc()` return is typecasted. The CPP does not allow types being return `void *`.

## class

1. class is a very good form of object oriented representation of the software program.
2. class contain both data and functions (they call in cpp as member functions / methods)
3. class also has protection mechanisms such as : `private`, `protected` and `public`.
    1. `private` members of the class are accessible only with in the class by their member functions of the same class or from their friends. Friends are discussed further down the manual.
    2. `protected` members are accessible from the same members of the class and friends, but also members of the derived classes. derived classes are described further down the manual again.
    3. `public` members are accessible by anyone once the class is declared in any functions and by referring them from the object.

A basic class looks like this:

```cpp

class class_name {
    access_type:
        data..
        data..
    access_type:
        member_func();
        member_func();
}
```

**Example:**

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

**Example:**

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

if you see in the above example, unlike the structure declaration as `struct cls p`, we only did `cls p` and is fine by the compiler (the class name `class` before cls is optional when declaring).

Alteratively, the variable `p` with in the class can be assigned a value this way as well. But you need to compile with `-std=c++11`.

**Example:**

```cpp
#include <iostream>

class library {
    private:
        int bookCount = 4;
    public:
        int getBookCount()
        {
            return bookCount;
        }
        int getAccess()
        {
            return true;
        }
};

int main()
{
    class library l;

    std::cout << "library book count: " << l.getBookCount() << std::endl;
}
```

The above example will give compilation error because the method `getP()` is `private` automatically.

4. pointers can be pointing to the class as well.

```cpp
class cpp_ptr {
    int ptr;
};

class cpp_ptr *cptr; // pointer to a class
```

## constructors

1. constructors are like init routines of a c lib.
2. constructors never return anything .. not even `void` type
3. two types of constructors : `default constructor` and `parameterised constructor`.

**Example:**

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

**Example:**

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
    cons_class p1 (4); // constructor is called here
    cons_class p2 = p1; // copy constructor called here
}
```

Constructor is called only when you declare the class in the caller.

if the constructor is not created, then the compiler creates one by default.

Take a look at the below example. This has the nice way of assigning the values to the private members of the class via constructor.. much like a parameterised constructor in a new way. Download [here](https://github.com/DevNaga/gists/blob/master/cpp/args_setup.cpp).

**Example:**

```cpp
#include <iostream>

class test_class {
    public:
        test_class(int f): a1 (f) // assign f to a1
        {
        }

        int geta1()
        {
            return a1;
        }

    private:
        int a1;
};

int main()
{
    // parameterised constructor call
    test_class test(5);

    std::cout << "a1: " << test.geta1() << std::endl;
}
```

## destructor

1. destructors are like deinit routines of a c lib. 
2. destructors are called when the class object goes out of scope or when the program ends.
3. use `~` symbol before the constructor name, then it becomes destructor. 

**Example:**

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
#include <iostream>

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

int main()
{
    overloadedC o;
    overloadedC o1(4);
}
```

## 'this' pointer

1. used to reference the object itself with in the object only. referencing outside the object is not allowed and produce compiler error.

**Example:**

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

## Inheritance

As you might already know now that the C++ defines a very nice mechanism called `class` to define object and data very well in sturctured format. One very well known features of the C++ are inheritance.

Inheritance is a derivation or like a child inheriting the genes of her mom.

There are many types of inheritance.

1. single inheritance
2. multiple inheritance
3. multilevel inheritance
4. heirarchial inheritance
5. hybrid inheritance


### single inheritance

A class inherits the properties of another class. This is done by using the `:` operator, followed by the access method. Access method could be like `private`, `public` or `protected`.

Consider the below example:

**Example:**

```cpp
#include <iostream>

class library {
    private:
        int bookCount = 4;
    public:
        int getBookCount()
        {
            return bookCount;
        }
        int getAccess()
        {
            return true;
        }
};


class engineering : public library {
};

int main()
{
    class engineering e;
    class library l;

    std::cout << "book count: " << e.getBookCount() << std::endl;

    std::cout << "library book count: " << l.getBookCount() << std::endl;
}
```

in this example, the `class` `engineering` is a section of `class library`. Library contains so many books and sections and Engineering is part of it. So the methods such as getting access to the library and the number of total books in the library are usually common to both the classes. So the `library` becomes the base class and the `engineernig` becomes a derived class that inherits the `library` base class.

A class can be inherited only one time. doing it multiple times, would cause compilation error. Consider the below example:

**Example:**

```cpp
#include <iostream>

class library {
    private:
        int bookCount = 4;
    public:
        int getBookCount()
        {
            return bookCount;
        }
        int getAccess()
        {
            return true;
        }
};


class engineering : public library {
};

class compsci: public engineering, public library {
};

int main()
{
    engineering e;
    library l;
    computersci cs;

    std::cout << "book count: " << e.getBookCount() << std::endl;

    std::cout << "library book count: " << l.getBookCount() << std::endl;
}
```

### multiple inheritance

A class when inherited with multiple super classes (the base classes that are supersets, in our case the `class library` is one of the super class), it is said to be doing multiple inheritance.

### multilevel inheritance

### hierarchial inheritance

### hybrid inheritance


## STD API

### std::chrono (from c++ - 14) use -std=c++14

use `<chrono>` as the header file.

```cpp
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

int main()
{
    auto day = 24h;
    auto secs = 60s;
    auto millisec = 100ms;

    std::cout << "seconds: " << secs.count() << "\n"
              << "hours in day: " << day.count() << "\n"
              << "miiseconds: " << millisec.count() << std::endl;
}
```

### std::to_string

converts any value type into strings, so be it an `int`, `unsigned int`, `double`, or `long` types. The `to_string` method is an overloaded type.

**Example:**

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

**Example:**

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
## std::signal

`std::signal()` is an API to register a signal handler for the Linux signals. Such as the `SIGINT`, `SIGQUIT` etc.. The C++ standard library has a wrapper around this API.

**Example:**

```cpp
#include <csignal>
#include <iostream>

static std::sig_atomic_t signal_status;

void signal_handler(int signal)
{
    signal_status = signal;
}

int main()
{
    std::signal(SIGINT, signal_handler);

    while (1) {
        if (signal_status == SIGINT) {
            std::cout << "caught ctrl + c .. exit\n" << std::endl;
            break;
        }
    }
}
```

use `<csignal>` to use the `std::signal()` API.

## std::map

`std::map` provides a key value store in C++ so that one does not have to create something on their own. Think of map as a two-d vector but the values referenced by the keys.

The map can be declared very basically as follows.

use `<map>` header.

```cpp
std::map <type1, type2> var;
```

The example below shows the usage of `std::map`.

**Example:**

```cpp
#include <iostream>
#include <map>

int main()
{
    std::map<char,int> m;
    std::map<char,int> :: iterator t;

    m['a'] = 1;
    m['b'] = 2;
    m['c'] = 3;
    m['d'] = 4;

    std::cout << "map size:" << m.size() << std::endl;

    for (t = m.begin(); t != m.end(); t ++) {
        std::cout << "keyid:" << t->first
                  << "value:" << t->second << std::endl;
    }

    // search for d
    std::map<char, int> :: iterator t_1;

    t_1 = m.find('d');

    std::cout << "value at 'd':"<< t_1->second << std::endl;
}
```

just like the `std::list` or `std::vector`, the `std::map` can also be iterated using the `std::map <type1, type2> :: iterator`.

in the above example we see that the map element `m` is being iterated with the `.begin` and `.end` types. The `->first` and the `->second` are the `key` and `value` pairs respectively.

A value can be found by using a key element using the `.find()` method. If a key is available or not is found by checking the return of `.find()` method with `.end()`.

### writing loops with iterators

1. using `::iterator`

with `auto` keyword, its nothing

```cpp
for (auto it = m.begin(); it != m.end(); it ++) {
    std::cout << it->first << it->second << std::endl;
}
```

```cpp
for (std::map<char, int>::iteartor it = map.begin(); it != map.end(); it ++) {
    std::cout << it->first << it->second << std::endl;
}
```

2. using `const_iterator`

```cpp
for (auto cit = m.cbegin(); cit != m.cend(); cit ++) {
    std::cout << cit->first << cit->second << std::endl;
}
```

```cpp
for (std::map<char, int>::reverse_iterator rit = map.begin(); rit != map.end(); rit ++) {
    std::cout << rit->first << rit->second << std::endl;
}
```

3. using map with structures

```cpp

struct structures {
    int a;
    int b;
};

std::map<std::string, struct structures> data;

struct structures s = {1,2};

// using insert
data.insert(std::pair<std::string, struct structures>("Hello", s);

// direct set

data["Hello"] = {1, 2};
```

4. iterating the std::map with a struct

```cpp
for (std::map<std::string, struct structure>::iterator it = data.begin(); it != data.end(); it ++) {
    struct structures *s = &(it->second);

    std::cout << " structures: s->a : " << s->a << " s->b : " << s->b << std::endl;
}
```

| feature | value |
|---------|-------|
| `map.size()` | get the element count in map |
| `map.erase(iterator)` | erase a particular element |
| `map.erase(begin, end)` | erase if given begin and end points of iterator |
| `map.empty()` | check if map is empty |

**Example:**

```cpp
std::map <char, int> :: iterator key;

key = m.find('e');
if (key == m.end()) {
    std::cout << "key did not found\n";
}
```


## namespaces

1. namespaces are used to organise the very large amount of source code to avoid name collisions (mainly).
2. a namespace can be nested within another namespace
3. namespaces can span into multiple source files / header files and the compiler combines them or extends them
4. once defined the namespace is accessed using the `using namespace` or the explicit access as `ns::var..`. the word `using` is a directive. without using the `using` directive, one should write the namespace before accessing any member of the namespace.

Below example provide an overview of the namespace usage:

**Example:**

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


Sometimes it gets hard to understand or access variables inside a namespace.. such as for ex defined Enums. See example below.

**Example:**

```cpp
#include <iostream>

namespace ns {
    typedef enum {
        ENUM_1,
        ENUM_2,
    } TestEnum_t;

    TestEnum_t te;
};

int main()
{
    ns::TestEnum_t te1 = ns::ENUM_2;
    ns::te = ns::ENUM_1;
    std::cout << "Enum1: " << ns::te << std::endl;
}
```

in the above example the namespace `ns` defines a enum called `TestEnum_t` inside it..

1. To declare 

### STL

#### std::string Standard library std (String library)

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
2. iterator definitions:

```cpp
std::string s("12345");

std::string::iterator it;
std::string::const_iterator it; // iterate char by char from 0 index to the length

... use .begin() and .end() API to iterate char by char wise from 0.

std::string::reverse_iterator it; // iterate char by char from last index to 0

... use .rbegin() and .rend() API to iterate char by char wise from length
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

The c type string `char *` can be accessed with the `.c_str` member function.

```cpp
std::string str = "Hello";

char *c_string = str.c_str();
```

The C type strings are accessed as well... see below basic example.

**Example:**

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string cstr = "Hello";

    std::cout << "C string form: " << cstr.c_str() << std::endl;
}
```

getting a particular character at a particular location is by using the `at` member function.

**Example:**

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string str1 = "Programming";

    std::cout << "first char : " << str1.at(0) << std::endl;
}
```

iterating character wise in ascending and descending order is shown below.

**Example:**

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string str = "string";

    std::cout << "In Ascending order: \n";

    std::string::const_iterator it;

    for (it = str.begin(); it != str.end(); it ++) {
        std::cout << *it << std::endl;
    }

    std::cout << "In descending order: \n";

    std::string::reverse_iterator rit;

    for (rit = str.rbegin(); rit != str.rend(); rit ++) {
        std::cout << *rit << std::endl;
    }
}
```

The front and last characters of a string are found by using `.front()` and `.back()` member functions. The equivalent of calling this is `.at(0)` and `.at(std::str::length() - 1)`.

**Example:**

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string str = "string";

    std::cout << "Front: " << str.front() << "Back: " << str.back() << std::endl;
}
```

use `-std=c++11` option when compiling with `g++`.

To clear the content of the string, use `.clear()` member function.

**Example:**

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string str = "string";

    std::cout << "string length: " << str.length() << std::endl;

    str.clear();

    std::cout << "string length: " << str.length() << std::endl;
}
```

The string to integer conversion is done by using `stoi` and double is done using `stod`. The `stoi` is overloaded in the case that you can pass to convert to a decimal or hex.

**Example:**

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string s1 = "50";
    std::string s2 = "44.44";

    int s1_int;
    double s2_double;

    s1_int = std::stoi(s1);
    s2_double = std::stod(s2);

    std::cout << "integer value: " << s1_int << std::endl;
    std::cout << "integer hex : 0x" << std::stoi(s1, 0, 16) << std::endl;
    std::cout << "double value: " << s2_double << std::endl;
}
```

## USECASE
As we now know much details in the coding of C++ such as `class`, `constructor / destructor` and `std::str` we would go ahead and write on file system io operation class as a usecase.

**Example:**

```cpp
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

class fsAPI {
    private:
        int fd;
    public:
        fsAPI(std::string filename, std::string mode)
        {
            int o_type = 0;
            int perms = 0;

            if (mode == "r") {
                o_type = O_RDONLY;
            }
            if (mode == "w") {
                o_type = O_CREAT | O_WRONLY;
                perms = S_IRWXU;
            }
            if (mode == "a") {
                o_type = O_APPEND;
            }

            if (perms != 0) {
                fd = open(filename.c_str(), o_type, perms);
            } else {
                fd = open(filename.c_str(), o_type);
            }
            if (fd < 0) {
                std::cout << "failed to open:" << filename << std::endl;
            }
        }
        ~fsAPI()
        {
            if (fd > 0)
               close(fd);
        }
        int writeAPI(std::string buf, int buf_len);
        int readAPI(std::string *buf, int buf_len);
};

int fsAPI::writeAPI(std::string buf, int buf_len)
{
    return write(fd, buf.c_str(), buf_len);
}

int fsAPI::readAPI(std::string *buf, int buf_len)
{
    char c_buf[1400];
    int ret;

    ret = read(fd, (void *)c_buf, buf_len);

    c_buf[ret] = '\0';

    buf->append(c_buf);
    return 0;
}

int main(int argc, char **argv)
{
    if (!strcmp(argv[1], "write")) {
        class fsAPI fsHandle("devnaga.txt", "w");
        std::string msg("Hello C++.. fs API");

        fsHandle.writeAPI("Hello C++.. fs API", msg.size());
    } else if (!strcmp(argv[1], "read")) {
        class fsAPI fsHandle("devnaga.txt", "r");
        std::string msg;

        fsHandle.readAPI(&msg, 1400);

        std::cout << "msg length: " << msg.size() << std::endl;
        std::cout << "str: " << msg << std::endl;
    }
}
```

### Lists (std::list)
1. lists are another part of STL. they are like the linked lists.
2. the `std::list` is used to perform the various operations

|type / way to use | description|
|------------------|------------|
|`std::list<int>`| declares a set of integer lists|
|`std::list<int>::const_iterator`| declares a constant iterator to iterate thru list|
|`std::list::push_front(elem)`| push an element in the front |
|`std::list::push_back(elem)`| push at the end of the list |
|`std::list::front(elem)`| access the element at the beginning |
|`std::list::back(elem)`| access the element at the end |
|`std::list::empty()`| check if list is empty |
|`std::list::size()`| size of the list |
|`std::list::max_size()`| find max size of the list |
|`std::list::clear()`| clear the list contents |
|`std::list::assign(std::list<>::const_iterator, std::list<>::const_iterator)` | assign the new list at the end of the old list from begin to end |
|`std::list::sort(comparison function)` | sorts the elements in the ascending order |

**Declaring the integer list:**

```cpp
std::list<int> i;
```

**Adding an element at the end in the list:**

```cpp
std::list<int> i;

i.push_back(4);
```

**Adding an element at the front in the list:**

```cpp
std::list<int> i;

i.push_front(4);
```


Below is a big example, provides an overview of lists:

**Example:**

```cpp
#include <iostream>
#include <list>

// writes our class to print list elements
class list_class {
    public:
        void list_print(std::list<int> i)
        {
            std::list<int>::const_iterator t;

            for (t = i.begin(); t != i.end(); t ++) {
                std::cout << *t << "->";
            }
            std::cout << std::endl;
        }

        void list_cprint(std::list<int> i)
        {
            std::list<int>::const_iterator t;

            for (t = i.cbegin(); t != i.cend(); t ++) {
                std::cout << *t << "->";
            }
            std::cout << std::endl;
        }

        void list_rprint(std::list<int> i)
        {
            std::list<int>::const_reverse_iterator t;

            for (t = i.rbegin(); t != i.rend(); t ++) {
                std::cout << *t << "->";
            }
            std::cout << std::endl;
        }
};

int main()
{
    std::list<int> i {1, 2, 3, 4, 5}; // setting up the list initialisation
    std::list<int>::const_iterator t;
    std::list<int>::const_reverse_iterator rt;

    std::list<int> new_list {4, 1, 2, 4};

    // value and ptr for testing of the contents after i being modified
    std::list<int> i_copy = i; // copy constructor ?
    std::list<int> *i_ptr = &i; // assign the address of the old list

    list_class l;

    //add at front
    i.push_front(4);
    //add at end
    i.push_back(8);

    std::cout << "begin" << std::endl;
    l.list_print(i);

    std::cout << "cbegin" << std::endl;
    l.list_cprint(i);

    std::cout << "rbegin" << std::endl;
    l.list_rprint(i);

    std::cout <<"front element:" << i.front() << std::endl;
    std::cout <<"last element:" << i.back() << std::endl;

    std::cout << "list empty:" << (i.empty() ? "Yes" : "No") << std::endl;

    std::cout << "list element number:" << i.size() << std::endl;

    std::cout << "list max_size:" << i.max_size() << std::endl;

    std::cout << "clearing list" << std::endl;

    i.clear();

    std::cout << "list count:" << i.size() << std::endl
              << "list empty:" << (i.empty() ? "Yes" : "No") << std::endl;

    i.assign(new_list.begin(), new_list.end());

    l.list_print(i);
    l.list_print(i_copy);
    l.list_print(*i_ptr);

    // sorts them in ascending order
    i.sort(std::greater<int>());
    l.list_print(i);
}
```

**USECASE:**

```cpp
/**
 * Written by DevNaga <devendra.aaru@gmail.com>
 *
 * Copyright All rights reserved DevNaga. Apached 2.0 License
 */
#include <iostream>
#include <list>
#include <string>

// linked list class..
//
// wrapper around the std::list<int>
class linked_list_class {
    private:
        std::list<int> i; // 
    public:
        void add_element(int i);
        void remove_element(int i);
        void print_elements();
        bool search_element(int i);
        void delete_all();
        int element_count();
};

// add an element in the linked list
void linked_list_class::add_element(int elem)
{
    i.push_back(elem);
}

// remove an element in the linked list
void linked_list_class::remove_element(int elem)
{
    i.remove(elem);
}

// print all the elements of linked list
void linked_list_class::print_elements()
{
    std::list<int>::iterator it;

    for (it = i.begin(); it != i.end(); it ++) {
        std::cout << "elem: " << *it << std::endl;
    }
}

// find and check if the element exist in linked list
bool linked_list_class::search_element(int elem)
{
    std::list<int>::iterator it;

    for (it = i.begin(); it != i.end(); it ++) {
        if (elem == *it) {
            return true;
        }
    }

    return false;
}

// delete all the elements in the linked list
void linked_list_class::delete_all()
{
    i.erase(i.begin(), i.end());
}

// count the number of elements in the linked list
int linked_list_class::element_count()
{
    return i.size();
}

int main(int argc, char **argv)
{
    linked_list_class lc;
    int i;

    std::cout << "add elements in the list " << std::endl;
    for (i = 1; i <= argc - 1; i ++) {
        lc.add_element(std::stoi(argv[i]));
    }

    std::cout << "printing elements >>>>>>>>>>>>>>>> : Element count is " << lc.element_count() << std::endl;

    lc.print_elements();

    std::cout << "search and remove an element " << std::endl;
    if (lc.search_element(3)) {
        lc.remove_element(3);
    }

    std::cout << "printing elements >>>>>>>>>>>>>>>>> : Element count is " << lc.element_count() << std::endl;

    lc.print_elements();

    lc.delete_all();

    std::cout << "clear off linked list" << std::endl;
    std::cout << "printing elements >>>>>>>>>>>>>>>>> : Element count is " << lc.element_count() << std::endl;
    lc.print_elements();
}
```

lets discuss here itself some of the comparison operators:

|type / way to use | description|
|------------------|------------|
|`std::greater<type>()` | greater than operation |
|`std::less<type>()` | less than operation |

#### std::stack

#### std::queue

#### Double ended queues (std::deque)

`std::deque` is a double ended queue that allow fast insertion and removal on both ends of the queue. This has the similar APIs that of any other STL API.

| API | description |
|-----|-------------|
|`.push_front()` | insert element at the beginning of deque |
|`.push_back()` | insert element at the end of deque |
|`.pop_front()` | remove element at the front of deque |
|`.pop_back()` | remove element at the end of deque |
|`.size()` | get the size of the deque |
|`std::deque<type>::const_iterator` | constant iterator from `.begin()` to `.end()` |
|`std::deque<type>::reverse_iterator` | constant iterator from `.rbegin()` to `.rend()` |
|`.begin()` | start of the deque |
|`.end()` | end of the deque |
|`.rbegin()` | reverse iterator at beginning |
|`.rend()` | reserve iteartor at the end |
|`.empty()` | check if the deque is empty |



```cpp
#include <iostream>
#include <deque>

int print_list(std::deque<int> d)
{
    std::deque<int>::const_iterator it;

    for (it = d.begin(); it != d.end(); it ++) {
        std::cout << *it << "-> ";
    }

    std::cout << std::endl;
}

int main()
{
    std::deque<int> d = {1, 2, 3, 4};
    std::deque<int>::const_iterator it;

    // normal iterate
    print_list(d);

    std::deque<int>::reverse_iterator ri;
    for (ri = d.rbegin(); ri != d.rend(); ri ++) {
        std::cout << "rd : " << *ri << std::endl;
    }

    auto empty = d.empty();
    if (empty == true) {
        std::cout << "list is empty " << std::endl;
    } else {
        std::cout << "list is filled : element count : " << d.size() << std::endl;
    }

    d.push_front(5);
    d.push_front(6);
    d.push_back(7);
    d.push_back(8);

    print_list(d);

    std::cout << std::endl;

    std::cout << "removing front element : size " << d.size() << std::endl;
    d.pop_front();

    std::cout << "final size : " << d.size() << std::endl;

    print_list(d);

    std::cout << "removing rear element : size " << d.size() << std::endl;
    d.pop_back();

    std::cout << "final size : " << d.size() << std::endl;

    print_list(d);
}
```

### vectors (std::vector)

1. vectors are dynamic arrays unlike the C's static arrays (it can be of array of integers, strings ..).
2. vectors is a class of std library
3. so we need to use `using namespace std` or use the full form representation (peferred approach if you are starting with CPP)

include `<vector>` header before using `std::vector`

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
9. access the front element using `.front()`.
10. access the back element using `.back()`.

**Example:**

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

**Example:**

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

    std::cout << "front:" << a.front()
              << "end:" << a.back() << std::endl;

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

**Example:**

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

merging the two vectors is a different thing. Here's one example:

**Example:**

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v(20), v1, v2;
    int i;

    for (i = 0; i < 10; i ++) {
        v1.push_back(i);
        v2.push_back(10 - i);
    }

    std::cout << "v1 size:" << v1.size() <<std::endl
              << "v2.size:" << v2.size() << std::endl;

    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());

    std::cout << "front:" << v1.front()
              << "back: " << v1.back() << std::endl;

    v.push_back(21);

    std::vector<int>::const_iterator iv;

    std::cout << "size:" << v.size() << std::endl;
    for (iv = v.begin(); iv != v.end(); iv ++) {
        std::cout << "iv:" << *iv << std::endl;
    }
}
```

Merging the two vectors is first followed with initialisation of the final vector with the memory sufficient to hold both vectors.

then calling the `std::merge` API to get the merge going.

So, when i test if the vector is still expandable by pushing new element at the rear, it still is.

defining a vector of vectors:

```cpp
std::vector< std::vector < int > > i;
```

iterating the vector of vectors:

```cpp
std::vector< std::vector < int > > i;

for (auto it = i.begin(); i != i.end(); i ++) {
    std::vector i1 = *it;

    for (auto it1 = i1.begin(); it1 != i1.end(); it1 ++) {
        ;
    }
}
```

adding elements to the vector of vectors:

```cpp

int id1 = 0;
int id2 = 0;

std::vector< std::vector < int > > i;

for (id1 = 0; id1 < 100; id1 ++) {
    std::vector v;

    for (id2 = 0; id2 < 100; id2 ++) {
        v.push_back(id2);
    }
    i.push_back(v);
}
```

### topics to cover yet:

2. std::numeric_limits
3. static_assert
4. explicit constructor
5. std::chrono
    1. steady clock
6. std::transform
7. std::bind
8. typename
9. std::thread
10. pointers vs references
11. std::for_each
12. override
13. decltype
14. mutable
15. singleton class
    
### C++ exception handling

C++ provides the exception handling via some routines such as the following.

**1. `std::runtime_error`**

The class `runtime_error` provide an exception handling API when used with `throw` statement it produces an exception on the screen and aborts the program by calling `abort`.

A sample of this program is illustrated here. You can download it [here](https://github.com/DevNaga/gists/blob/master/cpp/std_runtime.cpp) as well

**Example**

```cpp
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    if (argc != 2) {
        throw std::runtime_error("argc is not 2");
    }
    std::cout << "number of args : " << argc << std::endl;
}
```

As we know the `argc` is count of arguments when entered via command line and `argv` is the list of arguments that are being entered.

In the above program, checks for the `argc` not being equal to 2 and throws the exception on the screen if it isn't. If it is, then it shows number of args is 2.


   
## Boost libraries

### topics to cover:

1. `boost::program_options`
2. `boost::mpl`
------------------------


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

3. setting `cmake` C++ standard

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

---------------------------


# Cyber security - Secure coding practises

## security farmework principles

1. disable features that are not being used by default
2. run programs in lesser privilege execution mode
3. write a lot of test cases (use tools such as `gtest`, `flawfinder`)
4. do analysis with external code review tools (such as `coverity` for example or any opensource review tools)
5. run the reviews against a common known vulnerabilities

## coding practices in C and C++

1. reduce the usage of too many or even one global variables as well as static variables unless otherwise it is really really important do not use them.

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


**3. using `rand()` and `srand()` the random number is not very pseudorandom**

Using `rand()` and `srand()` for seeding the random number generator does not really produce a psuedo random number and is not really usable by applications requiring the pseudorandom number. Insetad  in Linux usually provides `/dev/urandom` as the random number generator.

Here's one way to do a pseudorandom generator in C++.

```cpp
/**
 * Written by Dev Naga <devendra.aaru@gmail.com>
 *
 * All rights reserved Dev Naga, Apache 2.0 license
 */
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

// random generator class
class rand_num_gen {
    private:
        int fd;
    public:
        rand_num_gen();
        ~rand_num_gen();
        int gen_rand(uint8_t *rand_num);
        int gen_rand(uint16_t *rand_num);
        int gen_rand(uint32_t *rand_num);
        int gen_rand(uint64_t *rand_num);
        int gen_rand(uint64_t *rand_num, uint64_t min, uint64_t max);
};

// open fd to /dev/urandom
rand_num_gen::rand_num_gen()
{
    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        return;
    }
}

rand_num_gen::~rand_num_gen()
{
    close(fd);
}

int rand_num_gen::gen_rand(uint8_t *rand_num)
{
    int ret;

    ret = read(fd, rand_num, sizeof(*rand_num));
    if (ret > 0)
        return 0;

    return -1;
}

int rand_num_gen::gen_rand(uint16_t *rand_num)
{
    int ret;

    ret = read(fd, rand_num, sizeof(*rand_num));
    if (ret > 0)
        return 0;

    return -1;
}

int rand_num_gen::gen_rand(uint32_t *rand_num)
{
    int ret;

    ret = read(fd, rand_num, sizeof(*rand_num));
    if (ret > 0)
        return 0;

    return -1;
}

int rand_num_gen::gen_rand(uint64_t *rand_num)
{
    int ret;

    ret = read(fd, rand_num, sizeof(*rand_num));
    if (ret > 0)
        return 0;

    return -1;
}

int rand_num_gen::gen_rand(uint64_t *rand_num, uint64_t min, uint64_t max)
{
    int ret;

    if (min == max) {
        return -1;
    }

    ret = read(fd, rand_num, sizeof(*rand_num));
    if (ret > 0) {
        *rand_num = *rand_num % (max - min);
    }

    return -1;
}


int main(int argc, char **argv)
{
    rand_num_gen r;
    int i;

    if (argc != 2) {
        std::cout << argv[0] << " random number of times " << std::endl;
        return -1;
    }

    for (i = 0; i < std::stoi(argv[1]); i ++) {
        uint32_t rand_num32;
        uint64_t rand_num64;

        r.gen_rand(&rand_num32);
        r.gen_rand(&rand_num64);

        std::cout << "Rand number: " << rand_num32 << std::endl;
        std::cout << "Rand number: " << rand_num64 << std::endl;
    }
}
```

# FAQ

1. C header files

| header file | description |
|-------------|-------------|
| `<stdio.h>` | standard header file i/o |
| `<stdint>` | stdint headers with `uint32_t` and `uint8_t` etc |
| `<limits.h>` | limits such as `UINT_MAX` |
| `<getopt>` | opt arguments parsing |

2. C++ header files

| header file | description |
|-------------|-------------|
| `<array>` | fixed size array |
| `<bitset>` | a bit array |
| `<deque>` | double ended que |
| `<forward_list>` | a singly linked list |
| `<list>` | doubly linked list |
| `<map>` | sorted associative array |
| `<queue>` | single ended que |
| `<set>` | set class |
| `<stack> ` | stack |
| `<unordered_map>` | class for unordered map |
| `<unordered_set>` | class for unordered set | 
| `<vector>` | dynamic array |
| `<algorithm>` | algorithms |
| `<chrono>` | chrono time events |
| `<functional>` | standard functions for algorithms |
| `<iterator>` | classes for templates |
| `<memory>` | memory management templates |
| `<stdexcept>` | std exception classes |
| `<tuple>` | class tuple |
| `<utility>` | working for object pairs |
| `<string>` | string manip |
| `<regex>` | patterns for regex |
| `<fstream>` | file i/o | 
| `<iomanip>` | output format manip |
| `<ios> ` | i/o stream operation |
| `<iosfwd>` | forward declarations of several templates |
| `<iostream>` | c++ io fundamentals |
| `<istream>` | input stream classes |
| `<ostream>` | output stream classes |
| `<sstream>` | string stream classes |
| `<exception>` | exception handling |
| `<limits>` | std limits |
| `<thread>` | threads |
| `<mutex>` | mutual exclusion |
| `<condition_variable>` | condition variable |
| `<random>` | faclitiy for generating random numbers |

3. creating a static library in linux

```bash
ar rcv lib.a *.o
```

# Useful Links

1. https://www.cs.uaf.edu/2010/spring/cs202/lecture/03_02_exceptions.html
2. https://en.cppreference.com/w/cpp/error/runtime_error
