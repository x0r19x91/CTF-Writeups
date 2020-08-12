from z3 import *

# Poseidon{yay_you_simplified_the_mba_expressi0ns_from_the_VM_c0de}

flag = [BitVec('f%d' % i, 8) for i in range(0x41)]
stack = []
s = Solver()

def GET(*args):
    index = stack.pop()
    mem = stack.pop()
    if mem == 3:
        stack.append(flag[index])

def LDLOC(*args):
    stack.append(int(args[0], 16))

def LDC(*args):
    stack.append(int(args[0], 16))

def XOR(*args):
    r = stack.pop()
    l = stack.pop()
    stack.append(r^l)

def AND(*args):
    r = stack.pop()
    l = stack.pop()
    stack.append(r&l)

def SHL(*args):
    count = stack.pop()
    val = stack.pop()
    stack.append(val<<count)

def ADD(*args):
    r = stack.pop()
    l = stack.pop()
    stack.append(l+r)

def MUL(*args):
    r = stack.pop()
    l = stack.pop()
    stack.append(l*r)

def OR(*args):
    r = stack.pop()
    l = stack.pop()
    stack.append(l|r)

def CMP(*args):
    global s
    r = stack.pop()
    l = stack.pop()
    if args[0] == 'EQ':
        s.add(l == r)
    elif args[0] == 'NE':
        s.add(l != r)

table = {
    'CMP': CMP, 'OR': OR, 'MUL': MUL, 'ADD': ADD,
    'SHL': SHL, 'AND': AND, 'XOR': XOR, 'LDC': LDC,
    'LDLOC': LDLOC, 'GET': GET
}

def process(code):
    for line in code:
        ops = line.split()
        m = ops[1].split(".")
        argv = ops[2:]
        if m[0] == 'CMP':
            argv = m[1:]
        if m[0] not in table.keys():
            continue
        table[m[0]](*argv)

raw = open('disas.txt').read()
code = raw.split("\n")
code = code[556:2893]
process(code)
if s.check() == sat:
    m = s.model()
    print ''.join(chr(m[i].as_long()) for i in flag)
