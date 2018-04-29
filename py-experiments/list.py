#!/usr/bin/python

def function(item):
    print item

class Lists:
    def __init__(self):
        self.list = []

    def list_head(self):
        return self.list[0]

    def list_tail(self):
        return self.list[len(self.list) - 1]

    def list_add_tail(self, elem):
        self.list.append(elem)

    def list_add_head(self, elem):
        self.list.insert(0, elem)

    def list_remove(self, elem):
        self.list.remove(elem)

    def list_foreach(self, func):
        for item in self.list:
            func(item)

    def list_empty(self):
        if len(self.list) == 0:
            return True
        return False

    def list_find_elem(self, elem):
        for item in self.list:
            if item == elem:
                return True
        return False

list = Lists()
list.list_add_tail(20)
list.list_add_tail(10)
list.list_add_head(1)
list.list_foreach(function)
print list.list_empty()
list.list_foreach(function)
print list.list_find_elem(44)
print list.list_find_elem(1)
print list.list_head()
print list.list_tail()
