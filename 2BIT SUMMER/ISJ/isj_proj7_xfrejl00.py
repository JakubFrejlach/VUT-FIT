#!/usr/bin/env python3

import collections

class log_and_count(object):
    '''Decorator class, that counts function calls and prints
    info about function params.
    '''
    def __init__(self, key = None, counts = None):
        '''Initialize decorator, counter must be given. Function
        name may be given, or it will take default name of function.
        '''
        self.counts = counts
        self.key = key

    def __call__(self, function):
        '''Calls default function with intel about params.
        '''
        if self.key is None:
            self.key = function.__name__

        def inner(*args, **kwargs):
            self.counts[self.key] += 1
            print("called " + function.__name__ + " with ", end='')
            print(args, end='')
            print(" and ", end='')
            print(kwargs)
            return function(*args, **kwargs)

        return inner

my_counter = collections.Counter()

@log_and_count(key = 'basic functions', counts = my_counter)
def f1(a, b=2):
    return a ** b
@log_and_count(key = 'basic functions', counts = my_counter)
def f2(a, b=3):
    return a ** 2 + b
@log_and_count(counts = my_counter)
def f3(a, b=5):
    return a ** 3 - b

f1(2)
f2(2, b=4)
f1(a=2, b=4)
f2(4)
f2(5)
f3(5)
f3(5,4)

print(my_counter)
