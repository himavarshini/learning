## useful operations

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
