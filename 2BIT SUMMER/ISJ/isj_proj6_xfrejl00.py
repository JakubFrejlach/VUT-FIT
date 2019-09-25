#!/usr/bin/env python3

import re
import sys

class Polynomial:
    """Holds polynomial as list of indexes of polynomial starting from
    lowest one.

    3x^2 + 2 is hold as [2, 0, 3]

    This polynomials can be added, compared, powered, derivated and calculated
    with assigned value.
    """

    def __init__(self, *args, **kwargs):
        """Creates Polynomial class from given arguments

        Arguments can be given via:
        1) list                -> pol1 = Polynomial([1,-3,0,2])
        2) separate int values -> pol2 = Polynomial(1,-3,0,2)
        3) key arguments       -> pol3 = Polynomial(x0=1,x3=2,x1=-3)

        If any value is different type and int, error occurs.
        """

        self.indexes = []
        # Checks if positional and key arguments didn't occur at same time
        if args and not kwargs:
            # Separated int values
            if isinstance(args[0], list) and len(args) == 1:
                self.indexes = args[0]
            # List of indexes
            elif all(isinstance(x, int) for x in args):
                self.indexes = list(args)
            else:
                sys.stderr.write("Wrong input.\n")
                exit(1)

        # Checks if positional and key arguments didn't occur at same time
        elif kwargs and not args:
            # Checks if all values are ints and if there are only correct key arguments
            for x in sorted(kwargs):
                if not re.search(r'^x[1-9][0-9]*$', x) and x != 'x0':
                    sys.stderr.write("Wrong input.\n")
                    exit(1)
                if not isinstance(kwargs[x], int):
                    sys.stderr.write("Wrong input.\n")
                    exit(1)

            # Storing highest index of polynomial
            max = 0
            for x in sorted(kwargs):
                tmp_max = int(x.lstrip('x'))
                max = tmp_max if tmp_max > max else max
            i = 0
            # Storing whole polynomial in list and filling the gaps with zeros
            while i <= max:
                if 'x'+str(i) in kwargs:
                    self.indexes.append(kwargs['x'+str(i)])
                else:
                    self.indexes.append(0)
                i += 1
        else:
            sys.stderr.write("Wrong input.\n")
            exit(1)

    def __str__(self):
        """Changes polynomial list representation to classic representation
        in str operations such as print(),etc.
        """

        values = []
        last_index = len(self.indexes) - 1

        for idx, x in enumerate(self.indexes):
            # Ommits all indexes with 0 value
            if x == 0:
                pass
            # lowest index, without power and x (variable)
            elif idx == 0:
                if x < 0:
                    values.append('- ' + str(-x))
                elif x > 0 and idx != last_index:
                    values.append('+ ' + str(x))
                elif x > 0 and idx != last_index:
                    values.append(str(x))
            # second lowest index, without power
            elif idx == 1:
                if x < 0:
                    values.append('- ' + str(-x) + 'x')
                elif x == 1:
                    values.append('+ x')
                else:
                    values.append('+ ' + str(x) + 'x')
            # other indexes, with x (variable) and with power
            else:
                if x == 1 and idx != last_index:
                    values.append('+ x^' + str(idx))
                elif x == 1 and idx == last_index:
                    values.append('x^' + str(idx))
                elif x == -1 and idx != last_index:
                    values.append('- x^' + str(idx))
                elif x == -1 and idx == last_index:
                    values.append('-x^' + str(idx))
                elif x < 0 and idx != last_index:
                    values.append('- ' + str(-x) + 'x^' + str(idx))
                elif x < 0 and idx == last_index:
                    values.append(str(x) + 'x^' + str(idx))
                elif x > 0 and idx == last_index:
                    values.append(str(x) + 'x^' + str(idx))
                elif x > 0 and idx != last_index:
                    values.append('+ ' + str(x) + 'x^' + str(idx))
        values = ' '.join(values[::-1])
        # return whole polynomial without redundant '+' in the begging
        return values.lstrip('+ ') if values else '0'

    def __eq__(self, other):
        """Compares two polynomials using two list comparing.
        Returns true or false whether polynomials equals or not.
        """

        list1 = self.indexes
        list2 = other.indexes

        # Filling shorter list with redundant zeros
        # [2, 0, 3] and [2, 0, 3, 0] are the same
        if len(list1) > len(list2):
            list2.extend([0] * (len(list1) - len(list2)))
        if len(list1) < len(list2):
            list1.extend([0] * (len(list2) - len(list1)))

        return list1 == list2

    def __add__(self, other):
        """Adds same indexes togehter from 2 lists.
        Returns new Polynomial class instance with result of adding.
        """

        list1 = self.indexes
        list2 = other.indexes

        # Filling shorter list with redundant zeros
        # [2, 0, 3] and [2, 0, 3, 0] are the same
        if len(list1) > len(list2):
            list2.extend([0] * (len(list1) - len(list2)))
        if len(list1) < len(list2):
            list1.extend([0] * (len(list2) - len(list1)))

        # Creating new list from two given
        list3 = [a + b for a, b in zip(list1, list2)]

        return Polynomial(list3)

    def __pow__(self, power):
        """Powers polynomial to given power using polynomial multiplying.
        Returns new Polynomial class instance with result of power.
        """
        # Check if power is positive int
        if not isinstance(power, int) or power < 0:
            sys.stderr.write("Wrong input.\n")
            exit(1)

        # x^0 -> 1
        if power == 0:
            return Polynomial([1])
        # No change
        elif power == 1:
            return Polynomial(self.indexes)
        # For each power stage, executes new polynomial multiplying
        else:
            index = 2
            s1 = self.indexes.copy()
            s2 = self.indexes.copy()
            while index <= power:

                # List filled with number zeros -> final index count
                result = [0]*(len(s1)+len(s2)-1)
                for o1,i1 in enumerate(s1):
                    for o2,i2 in enumerate(s2):
                        result[o1+o2] += i1*i2
                s2 = result.copy()
                index += 1

        return Polynomial(s2)

    def derivative(self):
        """Derivates polynomial.
        Returns new Polynomial class instance with result of derivative.
        """

        return Polynomial([self.indexes[i] * i for i in range(1, len(self.indexes))])

    def at_value(self, value1, value2 = None):
        """Calculates the value of polynomial with variable assigned from value1.
        If value2 is assigned too, returns their difference.
        """

        # Check for float or int
        if not isinstance(value1, int) and not isinstance(value1, float):
            sys.stderr.write("Wrong input.\n")
            exit(1)

        # Result from value1
        result1 =  [self.indexes[i] * (value1 ** i) for i in range(0, len(self.indexes))]

        # value2 isn't given
        if value2 is None:
            return sum(result1)
        else:
            # Check for float or int
            if not isinstance(value2, int) and not isinstance(value2, float):
                sys.stderr.write("Wrong input.\n")
                exit(1)

            # Result from value2
            result2 = [self.indexes[i] * (value2 ** i) for i in range(0, len(self.indexes))]
            return sum(result2) - sum(result1)

def test():
    """Tests given in project description.
    """
    assert str(Polynomial(0,1,0,-1,4,-2,0,1,3,0)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(Polynomial([-5,1,0,-1,4,-2,0,1,3,0])) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x - 5"
    assert str(Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3= -1, x1=1)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(Polynomial(x2=0)) == "0"
    assert str(Polynomial(x0=0)) == "0"
    assert Polynomial(x0=2, x1=0, x3=0, x2=3) == Polynomial(2,0,3)
    assert Polynomial(x2=0) == Polynomial(x0=0)
    assert str(Polynomial(x0=1)+Polynomial(x1=1)) == "x + 1"
    assert str(Polynomial([-1,1,1,0])+Polynomial(1,-1,1)) == "2x^2"
    pol1 = Polynomial(x2=3, x0=1)
    pol2 = Polynomial(x1=1, x3=0)
    assert str(pol1+pol2) == "3x^2 + x + 1"
    assert str(pol1+pol2) == "3x^2 + x + 1"
    assert str(Polynomial(x0=-1,x1=1)**1) == "x - 1"
    assert str(Polynomial(x0=-1,x1=1)**2) == "x^2 - 2x + 1"
    pol3 = Polynomial(x0=-1,x1=1)
    assert str(pol3**4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
    assert str(pol3**4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
    assert str(Polynomial(x0=2).derivative()) == "0"
    assert str(Polynomial(x3=2,x1=3,x0=2).derivative()) == "6x^2 + 3"
    assert str(Polynomial(x3=2,x1=3,x0=2).derivative().derivative()) == "12x"
    pol4 = Polynomial(x3=2,x1=3,x0=2)
    assert str(pol4.derivative()) == "6x^2 + 3"
    assert str(pol4.derivative()) == "6x^2 + 3"
    assert Polynomial(-2,3,4,-5).at_value(0) == -2
    assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3) == 20
    assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3,5) == 44
    pol5 = Polynomial([1,0,-2])
    assert pol5.at_value(-2.4) == -10.52
    assert pol5.at_value(-2.4) == -10.52
    assert pol5.at_value(-1,3.6) == -23.92
    assert pol5.at_value(-1,3.6) == -23.92

if __name__ == '__main__':
    test()
