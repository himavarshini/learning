## useful operations

`printf()`: displays data on the screen

`str()`: converts any type into string type

`type()`: find the type of a variable


Many types are in the `python`:

| type| value|
|-----|------|
|int | for integer variables|
|float | floating point variables|

## Lists

1. Lists are like links of structures that are grouped together with various data types.
2. there can be list with in list

```python
list = [1, 2, 3, 4, 5];

print list
print type(list)
```
getting element in a list:

```python
print list[2] # gets element at index 2 i.e 3
```

### slicing

```python
first_two = list[:2];
remaining=  list[2:];

print(first_two, remaining)   # yes more than one statement or variable can be put into the print statement for printing
```

gets the first two elements of the list into `first_two` and the remaining elements into `remaining`.

### implicit copy of list

```python
list = [1, 2, 3, 4, 5];
list_copy = list
```

### explicit copy of list

```python
list = [1, 2, 3, 4, 5]
list_copy = list[:]
```

## functions

Functions are created with `def` type before any function call.

```python
def display_hello():
    print("Hello")

display_hello()
```

#### function - factorial
```python
def factorial(no):
    if no == 0 or no == 1:
        return 1

    val = 1;
    for i in range(1, no + 1):
        val *= i

    return val

fact = factorial(5)
print(fact)
```

## Tuples

1. returning multiple values from a function

```python
def return_multi(val1, val2):
    tuple_data = (val1, val2)
    return tuple_data

final_val = return_multi(4, 3)
print(final_val)
print("final val is of type " + str(type(final_val)))
```
2. assign tuple data to elements

```python
final_val = (val1, val2)
a = final_val[0]; # indexed
b = final_val[1]; # same .. indexe
```


## Great tools

1. pandas: https://www.dataquest.io/blog/pandas-python-tutorial/
