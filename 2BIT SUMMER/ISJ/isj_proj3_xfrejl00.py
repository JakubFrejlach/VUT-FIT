#!/usr/bin/env python3

import re

# ukol za 2 body
def first_odd_or_even(numbers):
    """Returns 0 if there is the same number of even numbers and odd numbers
       in the input list of ints.
       Returns the first odd number in the input list if the list has more even
       numbers.
       Returns the first even number in the input list if the list has more odd
       numbers.

    >>> first_odd_or_even([2,4,2,3,6])
    3
    >>> first_odd_or_even([3,5,4])
    4
    >>> first_odd_or_even([2,4,3,5])
    0
    """
    balance = 0
    odd_value = None
    even_value = None
    for value in numbers:
        if(value % 2 == 0):
            if even_value is None:
                even_value = value
            balance += 1
        else:
            if odd_value is None:
                odd_value = value
            balance -= 1

    if balance == 0:
        return 0;
    elif balance > 0:
        return odd_value if odd_value is not None else 0
    else:
        return even_value if even_value is not None else 0


# ukol za 3 body
def to_pilot_alpha(word):
    """Returns a list of pilot alpha codes corresponding to the input word

    >>> to_pilot_alpha('Smrz')
    ['Sierra', 'Mike', 'Romeo', 'Zulu']
    """

    pilot_alpha = ['Alfa', 'Bravo', 'Charlie', 'Delta', 'Echo', 'Foxtrot',
        'Golf', 'Hotel', 'India', 'Juliett', 'Kilo', 'Lima', 'Mike',
        'November', 'Oscar', 'Papa', 'Quebec', 'Romeo', 'Sierra', 'Tango',
        'Uniform', 'Victor', 'Whiskey', 'Xray', 'Yankee', 'Zulu']


    pilot_alpha_list = []

    A_ASCII_index = 65
    for letter in word:
        pilot_alpha_list.append(pilot_alpha[ord(letter.upper()) - A_ASCII_index])
    return pilot_alpha_list


if __name__ == "__main__":
    import doctest
    doctest.testmod()
