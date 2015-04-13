#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os,re,sys,commands,glob,json,collections,random
from random import randint
   
m= {
    'i':2,
    'j':3,
    'k':4,
}

i = 2
j = 3
k = 4

mulTable = (
    (),
    (0, 1, i, j, k),
    (0, i, -1, k, -j),
    (0, j, -k, -1, i),
    (0, k, j, -i, -1),
)

def mul(x, y):
    pos = (x * y) > 0
    x = abs(x)
    y = abs(y)
    r = mulTable[x][y]
    return r if pos else -r

def removeDuplicate(repeat):
    if repeat < 11:
        return repeat
    x = (repeat - 11) / 4
    return repeat - x * 4

def solve(s, repeat):
    s = [m[x] for x in s]
    repeat = removeDuplicate(repeat)
    t = 1
    needI = needJ = needK = True
    for _ in xrange(repeat):
        for x in s:
            # print t, mul(t,x), needI, needJ, needK
            t = mul(t, x)
            if needI:
                if t == i:
                    needI = False
                    t = 1
            elif needJ:
                if t == j:
                    needJ = False
                    t = 1
            elif needK:
                if t == k:
                    needK = False
                    t = 1
    # print t, needI, needJ, needK,s
    return not needI and not needJ and not needK and t == 1

def sp(*a):
    assert solve(*a[:-1]) == a[-1]
def test():
    sp('ijk', 1, True)
    sp('ij', 1, False)
    sp('kji', 1, False)
    sp('ji', 6, True)
    sp('i', 10000, False)
    sp('i', 100000, False)

    assert removeDuplicate(11) == 11
    assert removeDuplicate(12) == 12
    assert removeDuplicate(15) == 11
    assert removeDuplicate(1000) == 12
    pass

def readInt():
    return int(sys.stdin.readline().strip())
    
def readInts():
    return [int(x) for x in sys.stdin.readline().strip().split()]

def main():
    n = readInt()
    for i in xrange(n):
        l, repeat = readInts()
        s = sys.stdin.readline().strip()
        print 'Case #%d: %s' % (i+1, 'YES' if solve(s, repeat) else 'NO')
    pass

if __name__ == '__main__':
    main()