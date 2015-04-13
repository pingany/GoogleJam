#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os,re,sys,commands,glob,json,collections,random
from random import randint
   
# WRONG

hack = {
    (4, 2, 4): True
}

def solve(x, r, c):
    if r > c:
        r, c = c, r
    assert r <= c
    if (x, r, c) in hack:
        return hack[(x, r, c)]
    rc = r * c
    if x >= rc:
        return True
    return rc % x != 0 or \
            (c >= 3 and (c + 3) <= x) or \
            (c >= 3 and (c + r - 1) <= x) or \
            (r >= 3 and c >= 3 and 7 <= x) # cicle
    pass

def sp(*a):
    assert solve(*a[:-1]) == a[-1]
def test():
    sp(2,2,2, False)
    sp(2,1,3, True)
    sp(4,4,1, True)
    sp(3,2,3, False)
    sp(4,3,2, True)
    sp(1,4,1, False)
    sp(2,3,4, False)
    sp(3,1,3, True)
    sp(2,1,1, True)
    sp(4,2,3, True)
    sp(1,2,3, False)
    sp(1,1,3, False)
    sp(1,4,4, False)
    sp(2,1,2, True)
    sp(3,4,4, True)
    sp(1,3,4, False)
    sp(4,2,4, True) #
    sp(2,4,4, False)
    sp(2,4,1, False)
    sp(1,1,1, True)
    sp(2,4,2, False)
    sp(1,3,2, False)
    sp(1,4,2, False)
    sp(1,1,2, False)
    sp(3,1,2, True)
    sp(3,1,4, True)
    sp(4,1,4, True)
    sp(4,3,4, False)
    sp(3,3,4, False)
    sp(4,1,1, True)
    sp(4,2,2, True)
    sp(2,3,3, True)
    sp(2,3,1, True)
    sp(1,2,2, False)
    sp(1,3,1, False)
    sp(4,1,3, True)
    sp(3,2,4, True)
    sp(3,4,3, False)
    sp(3,3,3, False)
    sp(3,2,1, True)
    sp(4,3,1, True)
    sp(1,2,1, False)
    sp(4,4,4, False)
    sp(4,1,2, True)
    sp(3,2,2, True)
    sp(1,3,3, False)
    sp(4,4,2, True)
    sp(4,2,1, True)
    sp(3,3,2, False)
    sp(1,1,4, False)
    sp(1,4,3, False)
    sp(2,2,3, False)
    sp(3,1,1, True)
    sp(2,1,4, False)
    sp(2,4,3, False)
    sp(3,4,1, True)
    sp(4,3,3, True)
    sp(2,2,1, True)
    sp(4,4,3, False)
    sp(2,2,4, False)
    sp(3,3,1, True)
    sp(1,2,4, False)
    sp(3,4,2, True)
    sp(2,3,2, False)
    pass

def readInt():
    return int(sys.stdin.readline().strip())
    
def readInts():
    return [int(x) for x in sys.stdin.readline().strip().split()]

def main():
    n = readInt()
    for i in xrange(n):
        x, r, c = readInts()
        # print "sp(%s,%s,%s, %s)" % (x, r, c, solve(x, r, c))
        print 'Case #%d: %s' % (i+1, 'RICHARD' if solve(x, r, c) else 'GABRIEL')
    pass

if __name__ == '__main__':
    main()