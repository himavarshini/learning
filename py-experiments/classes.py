#!/usr/bin/python

class Shape:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    description = "this shape has not been described yet"
    author = "nobody has claimed to make this shape yet"
    def area(self):
        return self.x * self.y
    def perimeter(self):
        return 2 * self.x + 2 * self.y
    def describe(self, text):
        self.description = text
    def authorName(self, name):
        self.author = name
    def scaleSize(self, scale):
        self.x = self.x * scale
        self.y = self.y * scale

class Square(Shape):
    def __init__(self, x):
        self.x = x
        self.y = x

rectangle = Shape(10, 20)
print rectangle.area()

square = Square(10)
print square.area()
