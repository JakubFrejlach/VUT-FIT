import sys
import re
import os                          # file checking
import xml.etree.ElementTree as ET # XML parsing
from enum import Enum

#**************************** CLASSES ****************************

class exit(Enum):
    """Enumerate for exit codes
    """

    CORRECT = 0

    # command line error codes
    PARAM = 10
    INPUT = 11
    OUTPUT = 12

    # parser error codes
    XML = 31
    SYNTAX = 32

    # interpret error codes
    SEMANTIC = 52
    OPERANDS = 53
    VAR = 54
    FRAME = 55
    MISSING_VALUE = 56
    WRONG_VALUE = 57
    STRING = 58

class t_stats:
    """STATI extension handling.
    """

    def __init__(self):
        self.vars = 0
        self.insts = 0

    def handle_vars(self, frames, stack):
        """Counts defined variables in GF, TF and LF.
        """
        vars_tmp = 0
        for var in frames['GF']:
            if frames['GF'][var].data is not None:
                vars_tmp += 1
        for var in frames['TF']:
            if frames['TF'][var].data is not None:
                vars_tmp += 1
        if frames['LF'] is not None:
            for frame in stack:
                for var in frame:
                    if frame[var].data is not None:
                        vars_tmp += 1

        self.vars = max(self.vars, vars_tmp)

    def print_stats(self, params):
        """Prints stats into file with requested order.
        """
        if params.stats:
            try:
                with open(params.stats, 'w') as file:
                    for option in params.stats_params:
                        if option == '--vars':
                            file.write(str(self.vars) + '\n')
                        elif option == '--insts':
                            file.write(str(self.insts) + '\n')
            except Exception as e:
                print_error(e, exit.OUTPUT.value)


class t_token:
    """Represets arguments as tokens with type and data.
    """

    def __init__(self, data = None, type = None):
        self.data = data
        self.type = type

    def edit(self, data, type):
        """Edits token with new data and type
        """
        self.data = data
        self.type = type

    def copy_values(self, other):
        """Copy data and type from one token to another
        """
        self.data = other.data
        self.type = other.type

    def copy(self):
        """Creates copy of t_token class instance
        """
        return t_token(self.data, self.type)

    def __str__(self):
        return '(%s, %s)' % (self.type, self.data)

class instruction:
    """Represents whole instruction with all arguments.
    """
    def __init__(self):
        self.order = None
        self.opcode = None
        self.arg_count = 0
        self.arg1 = t_token()
        self.arg2 = t_token()
        self.arg3 = t_token()

class argument_parser:
    """Class for argument parsing.
    """

    def __init__(self):
        """FLAGS for program behavior.
        """
        self.source = False     # Source from file/stdin
        self.input = False      # Input from file/stdin
        self.stats = False      # Stats requested
        self.stats_params = []

    def print_help(self):
        """Prints help to interpret.py script
        """
        print("******************************************** HELP ********************************************")
        print("* Script interprets code in language IPPcode19. Script loads code from XML format.")
        print("* Script is executed:")
        print("* python3.6 interpret.py [arguments]\n*")
        print("* Script must be executed with at least one from following arguments (except --help option):")
        print("* --source=<file>\tIf given, XML source is loaded from <file> instead of STDIN.")
        print("* --input=<file>\tIf given, input is loaded from <file> instead of STDIN.\n*")
        print("* Script can be executed with optional arguments:")
        print("* --help\t\tPrints help (obviously). Cannot be combined with other arguments.")
        print("* --stats=<file>\tPrints additional stats into <file> when combined with arguments below.\n*")
        print("* Following arguments can all be combined and can be used multiple times:")
        print("* --vars\t\tPrints max number of initialized variables in all frames.")
        print("* --insts\t\tPrints number of interpreted instructions.")
        print("**********************************************************************************************")
        sys.exit(exit.CORRECT.value)

    def parse_args(self):
        """Loops through all script arguments and parses them.
        """
        # --help option
        if(len(sys.argv) == 2 and sys.argv[1] == '--help'):
            self.print_help()

        # other options
        for arg in sys.argv[1:]:
            # source file
            if(re.search('^--source=.+$', arg) and not self.source):
                self.source = re.search('^--source=(.+$)', arg).group(1)
                if(not os.path.isfile(self.source)):
                    print_error('File doesn\'t exists.', exit.INPUT.value)

            # input file
            elif(re.search('^--input=.+$', arg) and not self.input):
                self.input = re.search('^--input=(.+$)', arg).group(1)
                if(not os.path.isfile(self.input)):
                    print_error('File doesn\'t exists.', exit.INPUT.value)

            # stats file
            elif(re.search('^--stats=.+$', arg) and not self.stats):
                self.stats = re.search('^--stats=(.+$)', arg).group(1)

            # stats params
            elif(re.search('^--(vars|insts)$', arg)):
                self.stats_params.append(arg)

            # unknown param
            else:
                print_error('Wrong params combination.', exit.PARAM.value)

        # neither source or input given
        if(not self.source and not self.input):
            print_error('Wrong params combination.', exit.PARAM.value)

        # stats params given, but stats file not
        elif(not self.stats and self.stats_params):
            print_error('Wrong params combination.', exit.PARAM.value)

#**************************** FUNCTIONS ****************************

def print_error(error_msg, error_code):
    """Prints error_msg to STDERR end terminates script with error_code.
    """
    sys.stderr.write('ERROR: %s\n' % error_msg)
    sys.exit(error_code)

def check_arg_number(number, inst):
    """Checks if instruction argument count is same as requested.
    """
    if(number != inst.arg_count):
        print_error('Wrong syntax.', exit.SYNTAX.value)

def check_variable(type):
    """Check if token is var type.
    """
    if(type != 'var'):
        print_error('Wrong syntax.', exit.SYNTAX.value)

def check_symbol(type):
    """Check if token is var, nil, bool, float, string or int type.
    """
    if(not re.search('^(var|nil|bool|float|string|int)$', type)):
        print_error('Wrong syntax.', exit.SYNTAX.value)

def check_label(type):
    """Check if token is label type.
    """
    if(type != 'label'):
        print_error('Wrong syntax.', exit.SYNTAX.value)

def check_type(type):
    if(type != 'type'):
        print_error('Wrong syntax.', exit.SYNTAX.value)

def convert_escape(string):
    """Converts decimal escape sequences like \010 to chars.
    """
    matches = re.findall(r'\\([0-9][0-9][0-9])', string)
    for escape in matches:
        string = re.sub(r'\\' + escape, chr(int(escape)), string)
    return string

def define_labels(instructions):
    """Defines all LABELs in intepreted code.
    """
    labels = {}
    for idx, inst in enumerate(instructions):
        if(inst.opcode == 'LABEL'):
            if inst.arg1.data in labels:
                print_error('Label redefinition', exit.SEMANTIC.value)
            labels[inst.arg1.data] = idx
    return labels

def is_defined(var, frame):
    """Checks if variable is defined in frame.
    If variable is from TF or LF, checks also if frames are defined.
    """
    if(frame == 'TF'):
        if not tf_defined:
            print_error('Undefined frame.', exit.FRAME.value)
    elif(frame == 'LF'):
        if not lf_stack:
            print_error('Undefined frame.', exit.FRAME.value)
    if var not in scope[frame]:
        print_error('Undefined variable.', exit.VAR.value)

def is_initialized(var, frame):
    """Checks if variable is initialized in frame.
    If variable is from TF or LF, checks also if frames are defined.
    """
    is_defined(var, frame)
    if scope[frame][var].type is None or scope[frame][var].data is None:
        print_error('Missing value.', exit.MISSING_VALUE.value)

def is_label_defined(label):
    """Checks if label is already defined in labels dictionary.
    """
    if label not in labels:
        print_error('Undefined label.', exit.SEMANTIC.value)

def get_frame(var):
    """Splits var representation like "frame@var" into separate frame and var.
    """
    frame = var.data.split('@')[0]
    name = var.data.split('@')[1]
    return name, frame

def handle_symbol(arg):
    """Checks if symbol is initialized and returns reference to it.
    """
    # variable
    if(arg.type == 'var'):
        var, frame = get_frame(arg)

        # Symbols in TYPE instruction can be uninitialized
        if(code[index].opcode != 'TYPE'):
            is_initialized(var, frame)
        else:
            is_defined(var, frame)
        return scope[frame][var]

    # constant
    else:
        return arg

def handle_var(arg):
    """Checks if variable is defined and returns reference to it.
    """
    var, frame = get_frame(arg)
    is_defined(var, frame)
    return scope[frame][var]

#**************************** MAIN PROGRAM ****************************

# argument parsing
params = argument_parser()
params.parse_args()

# loads XML from stdin
if not params.source:
    try:
        xml_input = sys.stdin.buffer
    except Exception as e:
        print_error(e, exit.INPUT.value)
    try:
        xml = ET.parse(xml_input)
    except Exception as e:
        print_error(e, exit.XML.value)

# loads XML from file
else:
    try:
        xml = ET.parse(params.source)
    except Exception as e:
        print_error(e, exit.XML.value)

if params.input:
    try:
        fp = open(params.input, 'r')
    except Exception as e:
        print_error(e, 11)

# XML check
root = xml.getroot()

# main root must be "program" and must have attribute "language"
if(root.tag == 'program' and 'language' in root.attrib and
        root.attrib['language'] == 'IPPcode19'):

    # checks for some additional text between tags
    if(root.text is not None and root.text.strip()):
        print_error('Unxpected XML text.', exit.SYNTAX.value)

    # checks for unknown attributes in root
    for key in root.attrib:
        if(re.search('^(name|description|language)$', key)):
            continue
        else:
            print_error('Wrong XML attributes.', exit.SYNTAX.value)

    # checks all root childs
    for child in root:

        # instruction has max 3 arguments
        if(len(child) > 3):
            print_error('Too much instruction arguments.', exit.SYNTAX.value)

        # checks for some additional text between tags
        if(child.text is not None and child.text.strip()):
            print_error('Unxpected XML text.', exit.SYNTAX.value)
        if(child.tail is not None and child.tail.strip()):
            print_error('Unxpected XML text.', exit.SYNTAX.value)

        # checks for childs tag and attributes
        if(child.tag == 'instruction' and 'order' in child.attrib and
                'opcode' in child.attrib and len(child.attrib) == 2):

            # checks all instruction childs
            for arg_child in child:

                # checks for some additional text between tagss
                if(arg_child.tail is not None and arg_child.tail.strip()):
                    print_error('Unxpected XML text.', exit.SYNTAX.value)

                # arguments are not allowed to have XML childs
                if(len(arg_child) != 0):
                    print_error('Unxpected XML text.', exit.SYNTAX.value)

                # checks for arg_childs tag and attributes
                if(re.search('^arg[1-3]$', arg_child.tag) and
                        'type' in arg_child.attrib and
                         len(arg_child.attrib) == 1):
                    continue
                else:
                    print_error('Wrong XML attributes.', exit.SYNTAX.value)
        else:
            print_error('Wrong XML attributes.', exit.SYNTAX.value)
else:
    print_error('Wrong XML attributes.', exit.SYNTAX.value)

# list for instructions
code = []

# list for checking instruction order
inst_order_check = []

# loops through all instructions
for child in root:
    inst = instruction()
    inst.opcode = child.attrib['opcode'].upper()

    # instruction order must be convertable to int
    try:
        inst_order_check.append(int(child.attrib['order']))
        inst.order = int(child.attrib['order'])
    except Exception as e:
        print_error(e, 32);

    # list for checking argument order
    arg_order_check = []

    # loops through all instruction arguments
    for idx, arg in enumerate(child):

        # gets argument number
        arg_order_check.append(int(arg.tag[3]))
        token = t_token(arg.text, arg.attrib['type'])

        # empty token text is replaced with empty string
        if token.data is None:
            token.data = ''

        # lexical analysis
        if(token.type == 'var' and re.search(r'^(GF|LF|TF)@[a-zA-Z_\-$&%*!?][a-zA-Z0-9_\-$&%*!?]*$', token.data)):
            pass
        elif(token.type == 'nil' and token.data == 'nil'):
            pass
        elif(token.type == 'bool' and re.search(r'^(true|false)$', token.data)):
            token.data = token.data == 'true'
        elif(token.type == 'int' and re.search(r'^[-+]?[0-9]+$', token.data)):
            token.data = int(token.data)
        elif(token.type == 'float' and re.search(r'^[-+]?(0[xX])?[0-9a-fA-F]*(\.[0-9a-fA-F]*)?(p[-+]?[0-9]+)?$', token.data)):
            token.data = float.fromhex(token.data)
        elif(token.type == 'string' and
                re.search(r'^(([\u0021\u0022\u0024-\u005B\u005D-\uFFFF])|(\\[0-9][0-9][0-9]))*$', token.data)):
            token.data = convert_escape(token.data)
        elif(token.type == 'type' and re.search(r'^(int|string|bool|float)$', token.data)):
            pass
        elif(token.type == 'label' and re.search(r'^[a-zA-Z_\-$&%*!?][a-zA-Z0-9_\-$&%*!?]*$', token.data)):
            pass
        else:
            print_error('Lexically wrong XML attribute.', exit.SYNTAX.value)

        # copy token token value and type into instruction argument
        if arg.tag == 'arg1':
            inst.arg1.copy_values(token)
            inst.arg_count += 1
        elif arg.tag == 'arg2':
            inst.arg_count += 1
            inst.arg2.copy_values(token)
        elif arg.tag == 'arg3':
            inst.arg_count += 1
            inst.arg3.copy_values(token)

    # check argument order
    arg_order_check = sorted(arg_order_check)
    if arg_order_check:
        if(not all(i == j - 1 for i, j in zip(arg_order_check, arg_order_check[1:])) or
                1 not in arg_order_check):
            print_error('Wrong arguments order.', exit.SYNTAX.value)

    # check syntax
    if(re.search('^(MOVE|INT2CHAR|STRLEN|TYPE|NOT|INT2FLOAT|FLOAT2INT)$', inst.opcode)):
        check_arg_number(2, inst)
        check_variable(inst.arg1.type)
        check_symbol(inst.arg2.type)
    elif(re.search('^(CREATEFRAME|PUSHFRAME|POPFRAME|RETURN|BREAK|CLEARS|ADDS|SUBS|MULS|IDIVS|LTS|GTS|EQS|ANDS|ORS|NOTS|INT2CHARS|STRI2INTS)$', inst.opcode)):
        check_arg_number(0, inst)
    elif(re.search('^(DEFVAR|POPS)$', inst.opcode)):
        check_arg_number(1, inst)
        check_variable(inst.arg1.type)
    elif(re.search('^(CALL|LABEL|JUMP|JUMPIFEQS|JUMPIFNEQS)$', inst.opcode)):
        check_arg_number(1, inst)
        check_label(inst.arg1.type)
    elif(re.search('^(PUSHS|WRITE|EXIT|DPRINT)$', inst.opcode)):
        check_arg_number(1, inst)
        check_symbol(inst.arg1.type)
    elif(re.search('^(ADD|SUB|MUL|IDIV|DIV|LT|GT|EQ|AND|OR|STRI2INT|CONCAT|STRLEN|GETCHAR|SETCHAR)$', inst.opcode)):
        check_arg_number(3, inst)
        check_variable(inst.arg1.type)
        check_symbol(inst.arg2.type)
        check_symbol(inst.arg3.type)
    elif(inst.opcode == 'READ'):
        check_arg_number(2, inst)
        check_variable(inst.arg1.type)
        check_type(inst.arg2.type)
    elif(re.search('^(JUMPIFEQ|JUMPIFNEQ)$', inst.opcode)):
        check_arg_number(3, inst)
        check_label(inst.arg1.type)
        check_symbol(inst.arg2.type)
        check_symbol(inst.arg3.type)
    else:
        print_error('Unknown OPCODE.', exit.SYNTAX.value)

    code.append(inst)

# check instruction order
inst_order_check = sorted(inst_order_check)
if inst_order_check:
    if(not all(i < j for i, j in zip(inst_order_check, inst_order_check[1:]))):
        print_error('Wrong instructions order.', exit.SYNTAX.value)

# sort instructions by order
code.sort(key = lambda x: x.order)
stats = t_stats()

# directories for scopes
scope = {}
scope['GF'] = {}
scope['TF'] = {}
scope['LF'] = None
tf_defined = False

# stacks for values, local frame and CALL instructions
lf_stack = []
call_stack = []
stack = []

labels = define_labels(code)
index = 0
while index < len(code):
    stats.insts += 1
    # CREATEFRAME
    if(code[index].opcode == 'CREATEFRAME'):
        tf_defined = True
        scope['TF'].clear()

    # PUSHFRAME
    elif(code[index].opcode == 'PUSHFRAME'):
        if not tf_defined:
            print_error('Undefined frame.', exit.FRAME.value)

        # append to LF stack and clear TF
        lf_stack.append(scope['TF'].copy())
        scope['LF'] = lf_stack[-1]
        tf_defined = False
        scope['TF'].clear()

    # POPFRAME
    elif(code[index].opcode == 'POPFRAME'):
        if not lf_stack:
            print_error('No scope on frame stack.', exit.FRAME.value)
        scope['TF'] = lf_stack.pop()
        scope['LF'] = lf_stack[-1] if lf_stack else None
        tf_defined = True

    # DEFVAR
    elif(code[index].opcode == 'DEFVAR'):
        var, frame = get_frame(code[index].arg1)

        # check for defined frames and variable redefinition
        if(frame == 'GF'):
            if var in scope['GF']:
                print_error('Variable redefinition.', exit.SEMANTIC.value)
        elif(frame == 'TF'):
            if not tf_defined:
                print_error('Undefined frame.', 55)
            if var in scope['TF']:
                print_error('Variable redefinition.', exit.SEMANTIC.value)
        elif(frame == 'LF'):
            if not lf_stack:
                print_error('Undefined frame.', 55)
            if var in scope['LF']:
                print_error('Variable redefinition.', exit.SEMANTIC.value)
        scope[frame][var] = t_token(None, None)

    # LABEL
    elif(code[index].opcode == 'LABEL'):
        pass

    # MOVE
    elif(code[index].opcode == 'MOVE'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)
        var.copy_values(symb1)

    # CALL
    elif(code[index].opcode == 'CALL'):
        call_stack.append(index + 1)
        is_label_defined(code[index].arg1.data)
        index = labels[code[index].arg1.data]
        continue

    # RETURN
    elif(code[index].opcode == 'RETURN'):
        if not call_stack:
            print_error('Empty call stack.', exit.MISSING_VALUE.value)
        index = call_stack.pop()
        continue

    # JUMP
    elif(code[index].opcode == 'JUMP'):
        is_label_defined(code[index].arg1.data)
        index = labels[code[index].arg1.data]
        continue

    # PUSHS
    elif(code[index].opcode == 'PUSHS'):
        symb1 = handle_symbol(code[index].arg1)
        stack.append(symb1.copy())

    # POPS
    elif(code[index].opcode == 'POPS'):
        if not stack:
            print_error('Missing value.', exit.MISSING_VALUE.value)
        var = handle_var(code[index].arg1)
        var.copy_values(stack.pop())

    # arithmetic instructions
    elif(code[index].opcode in ('ADD', 'SUB', 'MUL', 'IDIV', 'DIV')):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)
        symb2 = handle_symbol(code[index].arg3)

        # check for types
        if(symb1.type not in ('int', 'float') or symb2.type not in('int', 'float') or
                symb1.type != symb2.type):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # ADD
        if(code[index].opcode == 'ADD'):
            var.edit(symb1.data + symb2.data, symb1.type)

        # SUB
        elif(code[index].opcode == 'SUB'):
            var.edit(symb1.data - symb2.data, symb1.type)

        # MUL
        elif(code[index].opcode == 'MUL'):
            var.edit(symb1.data * symb2.data, symb1.type)

        # IDIV
        elif(code[index].opcode == 'IDIV' and symb1.type == 'int'):
            if symb2.data == 0:
                print_error('Division by zero.', exit.WRONG_VALUE.value)
            var.edit(symb1.data // symb2.data, 'int')

        # DIV
        elif(code[index].opcode == 'DIV' and symb1.type == 'float'):
            if symb2.data == 0:
                print_error('Division by zero.', exit.WRONG_VALUE.value)
            var.edit(symb1.data / symb2.data, 'float')

    # relation instructions
    elif(code[index].opcode in ('LT', 'GT', 'EQ')):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)
        symb2 = handle_symbol(code[index].arg3)

        # EQ
        if(code[index].opcode == 'EQ'):
            if(symb1.type == 'nil' or symb2.type == 'nil'):
                var.edit(symb1.type == symb2.type, 'bool')
            elif(symb1.type == symb2.type):
                var.edit(symb1.data == symb2.data, 'bool')
            else:
                print_error('Wrong operand types.', exit.OPERANDS.value)

        # check for supported type
        elif not (symb1.type in ('int', 'float', 'string', 'bool') and
                symb1.type in ('int', 'float', 'string', 'bool') and
                symb1.type == symb2.type):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # LT
        elif(code[index].opcode == 'LT'):
            var.edit(symb1.data < symb2.data, 'bool')

        # GT
        elif(code[index].opcode == 'GT'):
            var.edit(symb1.data > symb2.data, 'bool')

    # bool instructions
    elif(code[index].opcode in ('AND', 'OR')):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)
        symb2 = handle_symbol(code[index].arg3)

        # check for supported type
        if(symb1.type != 'bool' or symb2.type != 'bool'):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # AND
        if(code[index].opcode == 'AND'):
            var.edit(symb1.data and symb2.data, 'bool')

        # OR
        elif(code[index].opcode == 'OR'):
            var.edit(symb1.data or symb2.data, 'bool')

    # NOT
    elif(code[index].opcode == 'NOT'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)

        # check for supported type
        if(symb1.type != 'bool'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        var.edit(not symb1.data, 'bool')

    # INT2CHAR
    elif(code[index].opcode == 'INT2CHAR'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)

        # check for supported type
        if(symb1.type != 'int'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        try:
            var.edit(chr(symb1.data), 'string')
        except:
            print_error('Wrong operation with string.', exit.STRING.value)

    # STRI2INT
    elif(code[index].opcode == 'STRI2INT'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)
        symb2 = handle_symbol(code[index].arg3)

        # check for supported type
        if(symb1.type != 'string' or symb2.type != 'int'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        try:
            var.edit(ord(symb1.data[symb2.data]), 'string')
        except:
            print_error('Wrong operation with string.', exit.STRING.value)

    # READ
    elif(code[index].opcode == 'READ'):
        var = handle_var(code[index].arg1)
        try:
            # reading from file
            if params.input:
                value = fp.readline().strip("\n")
            # reading from STDIN
            else:
                value = input()

        # empty file -> empty string returned instead of '\n'
        except EOFError:
            value = ''

        # conversion to type or initializing with default value
        if(code[index].arg2.data == 'int'):
            try:
                var.edit(int(value), 'int')
            except:
                var.edit(0, 'int')
        elif(code[index].arg2.data == 'float'):
            try:
                var.edit(float.fromhex(value), 'float')
            except:
                var.edit(0.0, 'float')
        elif(code[index].arg2.data == 'string'):
            try:
                var.edit(str(value), 'string')
            except:
                var.edit('', 'string')
        elif(code[index].arg2.data == 'bool'):
                var.edit(value.lower() == 'true', 'bool')

    # WRITE
    elif(code[index].opcode == 'WRITE'):
        symb1 = handle_symbol(code[index].arg1)

        # bool and float must be converted before writing
        if(symb1.type == 'bool'):
            if symb1.data:
                print('true', end = '')
            else:
                print('false', end = '')
        elif(symb1.type == 'float'):
            print(float.hex(symb1.data), end = '')
        elif(symb1.type == 'nil'):
            pass
        else:
            print(symb1.data, end = '')

    # CONCAT
    elif(code[index].opcode == 'CONCAT'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)
        symb2 = handle_symbol(code[index].arg3)

        # check for supported type
        if(symb1.type != 'string' or symb2.type != 'string'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        var.edit(symb1.data + symb2.data, 'string')

    # STRLEN
    elif(code[index].opcode == 'STRLEN'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)

        # check for supported type
        if(symb1.type != 'string'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        var.edit(len(symb1.data), 'int')

    # GETCHAR
    elif(code[index].opcode == 'GETCHAR'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)
        symb2 = handle_symbol(code[index].arg3)

        # check for supported type
        if(symb1.type != 'string' or symb2.type != 'int'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        try:
            var.edit(symb1.data[symb2.data], 'string')
        except:
            print_error('Index out of range.', exit.STRING.value)

    # SETCHAR
    elif(code[index].opcode == 'SETCHAR'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)
        symb2 = handle_symbol(code[index].arg3)

        # check for supported type
        if(var.type != 'string' or symb1.type != 'int' or symb2.type != 'string'):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # check for range
        if(len(var.data) <= symb1.data or not symb2.data):
            print_error('Index out of range.', exit.STRING.value)
        var.edit(var.data[:symb1.data] + symb2.data[0] + var.data[symb1.data + 1:], 'string')

    # TYPE
    elif(code[index].opcode == 'TYPE'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)

        # uninitialized
        if(symb1.type is None):
            var.edit('', 'string')
        else:
            var.edit(symb1.type, 'string')

    # jump instructions
    elif(code[index].opcode in ('JUMPIFEQ', 'JUMPIFNEQ')):
        is_label_defined(code[index].arg1.data)
        symb1 = handle_symbol(code[index].arg2)
        symb2 = handle_symbol(code[index].arg3)

        # check for supported type
        if(symb1.type != symb2.type):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # JUMPIFEQ
        if(code[index].opcode == 'JUMPIFEQ' and symb1.data == symb2.data):
            index = labels[code[index].arg1.data]
            continue

        # JUMPIFNEQ
        elif(code[index].opcode == 'JUMPIFNEQ' and symb1.data != symb2.data):
            index = labels[code[index].arg1.data]
            continue

    # EXIT
    elif(code[index].opcode == 'EXIT'):
        symb1 = handle_symbol(code[index].arg1)

        # check for supported type
        if(symb1.type != 'int'):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # check for value range
        if(symb1.data not in range(0, 50)):
            print_error('Invalid value.', exit.WRONG_VALUE.value)

        stats.print_stats(params)
        # close input
        if params.input:
            fp.close()

        sys.exit(symb1.data)

    # DPRINT
    elif(code[index].opcode == 'DPRINT'):
        symb1 = handle_symbol(code[index].arg1)
        sys.stderr.write(str(symb1.data) + '\n')

    # BREAK
    elif(code[index].opcode == 'BREAK'):
        sys.stderr.write("*********** BREAK ***********\n")
        sys.stderr.write("Code position: %i\n" % index)
        sys.stderr.write("Instructions executed: %i\n" % (stats.insts - 1))
        sys.stderr.write('GF: ')

        # GF status
        for var in scope['GF']:
            sys.stderr.write('(%s, %s, %s); ' % (var, scope['GF'][var].type, scope['GF'][var].data))

        # TF status
        sys.stderr.write('\nTF:')
        if not tf_defined:
            sys.stderr.write("Undefined")
        else:
            for var in scope['TF']:
                sys.stderr.write('(%s, %s, %s), ' % (var, scope['TF'][var].type, scope['TF'][var].data))

        # LF status
        sys.stderr.write('\nLF:')
        if not lf_stack:
            sys.stderr.write("Undefined")
        else:
            for var in scope['LF']:
                sys.stderr.write('(%s, %s, %s), ' % (var, scope['LF'][var].type, scope['LF'][var].data))
        sys.stderr.write("\n*********** BREAK ***********\n")

    # INT2FLOAT
    elif(code[index].opcode == 'INT2FLOAT'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)

        # check for supported type
        if(symb1.type != 'int'):
            print_error("Wrong operand types.", exit.OPERANDS.value)
        var.edit(float(symb1.data), 'float')

    # FLOAT2INT
    elif(code[index].opcode == 'FLOAT2INT'):
        var = handle_var(code[index].arg1)
        symb1 = handle_symbol(code[index].arg2)

        # check for supported type
        if(symb1.type != 'float'):
            print_error("Wrong operand types.", exit.OPERANDS.value)
        var.edit(int(symb1.data), 'int')

    # CLEARS
    elif(code[index].opcode == 'CLEARS'):
        stack.clear()

    # stack arithmetic instructions
    elif(code[index].opcode in ('ADDS', 'SUBS', 'MULS', 'IDIVS')):
        try:
            symb2 = stack.pop()
            symb1 = stack.pop()
        except:
            print_error("Missing value on stack.", exit.MISSING_VALUE.value)

        # check for supported type
        if(symb1.type not in ('int', 'float') or symb2.type not in('int', 'float') or
                symb1.type != symb2.type):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # ADDS
        if(code[index].opcode == 'ADDS'):
            stack.append(t_token(symb1.data + symb2.data, symb1.type))

        # SUBS
        elif(code[index].opcode == 'SUBS'):
            stack.append(t_token(symb1.data - symb2.data, symb1.type))

        # MULS
        elif(code[index].opcode == 'MULS'):
            stack.append(t_token(symb1.data * symb2.data, symb1.type))

        # IDIVS
        elif(code[index].opcode == 'IDIVS'):
            if symb2.data == 0:
                print_error('Division by zero.', exit.WRONG_VALUE.value)
            stack.append(t_token(symb1.data // symb2.data, symb1.type))

    # stack relation instructions
    elif(code[index].opcode in ('LTS', 'GTS', 'EQS')):
        try:
            symb2 = stack.pop()
            symb1 = stack.pop()
        except:
            print_error("Missing value on stack.", exit.MISSING_VALUE.value)

        # EQS
        if(code[index].opcode == 'EQS'):

            # check for supported type
            if(symb1.type == 'nil' or symb2.type == 'nil'):
                stack.append(t_token(symb1.type == symb2.type, 'bool'))
            elif(symb1.type == symb2.type):
                stack.append(t_token(symb1.data == symb2.data, 'bool'))
            else:
                print_error('Wrong operand types.', exit.OPERANDS.value)

        # check for supported type
        elif not (symb1.type in ('int', 'float', 'string', 'bool') and
                symb1.type in ('int', 'float', 'string', 'bool') and
                symb1.type == symb2.type):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # LTS
        elif(code[index].opcode == 'LTS'):
            stack.append(t_token(symb1.data < symb2.data, 'bool'))

        # GTS
        elif(code[index].opcode == 'GTS'):
            stack.append(t_token(symb1.data > symb2.data, 'bool'))

    # stack bool instructions
    elif(code[index].opcode in ('ANDS', 'ORS')):
        try:
            symb2 = stack.pop()
            symb1 = stack.pop()
        except:
            print_error("Missing value on stack.", exit.MISSING_VALUE.value)

        # check for supported type
        if(symb1.type != 'bool' or symb2.type != 'bool'):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # ANDS
        if(code[index].opcode == 'ANDS'):
            stack.append(t_token(symb1.data and symb2.data, 'bool'))

        # ORS
        elif(code[index].opcode == 'ORS'):
            stack.append(t_token(symb1.data or symb2.data, 'bool'))

    # NOTS
    elif(code[index].opcode == 'NOTS'):
        try:
            symb1 = stack.pop()
        except:
            print_error("Missing value on stack.", exit.MISSING_VALUE.value)

        # check for supported type
        if(symb1.type != 'bool'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        stack.append(t_token(not symb1.data, 'bool'))

    # INT2CHARS
    elif(code[index].opcode == 'INT2CHARS'):
        try:
            symb1 = stack.pop()
        except:
            print_error("Missing value on stack.", exit.MISSING_VALUE.value)

        # check for supported type
        if(symb1.type != 'int'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        try:
            stack.append(t_token(chr(symb1.data), 'string'))
        except:
            print_error('Wrong operation with string.', exit.STRING.value)

    # STRI2INTS
    elif(code[index].opcode == 'STRI2INTS'):
        try:
            symb2 = stack.pop()
            symb1 = stack.pop()
        except:
            print_error("Missing value on stack.", exit.MISSING_VALUE.value)

        # check for supported type
        if(symb1.type != 'string' or symb2.type != 'int'):
            print_error('Wrong operand types.', exit.OPERANDS.value)
        try:
            stack.append(t_token(ord(symb1.data[symb2.data]), 'string'))
        except:
            print_error('Wrong operation with string.', exit.STRING.value)

    # stack jump instructions
    elif(code[index].opcode in ('JUMPIFEQS', 'JUMPIFNEQS')):
        is_label_defined(code[index].arg1.data)
        try:
            symb2 = stack.pop()
            symb1 = stack.pop()
        except:
            print_error("Missing value on stack.", exit.MISSING_VALUE.value)

        # check for supported type
        if(symb1.type != symb2.type):
            print_error('Wrong operand types.', exit.OPERANDS.value)

        # JUMPIFEQS
        if(code[index].opcode == 'JUMPIFEQS' and symb1.data == symb2.data):
            index = labels[code[index].arg1.data]
            continue

        # JUMPIFNEQS
        elif(code[index].opcode == 'JUMPIFNEQS' and symb1.data != symb2.data):
            index = labels[code[index].arg1.data]
            continue

    # count all defined variables in all frames for STATI extension
    stats.handle_vars(scope, lf_stack)
    index += 1

# print stats
stats.print_stats(params)

# close input
if params.input:
    fp.close()
