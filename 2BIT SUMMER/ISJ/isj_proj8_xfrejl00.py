#!/usr/bin/env python3

def first_with_given_key(iterable, key = lambda x: x):
    '''Function takes iterable and function. Function is called for each item
    if key is new, item with this key is generated and key is stored in keys
    list. If key is already in keys list. item is not generated.
    '''
    keys = []
    for item in iterable:
        if key(item) not in keys:
            keys.append(key(item))
            yield item



print(tuple(first_with_given_key([[1],[2,3],[4],[5,6,7],[8,9]])))
