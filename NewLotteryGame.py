#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os,re,sys,commands,glob,json,collections,random
from random import randint
   
def solveSimple(a, b, k):
    c = 0
    for i in range(a):
        for j in range(b):
            if (i & j) < k:
                c +=1
    return c


def toBinary(a):
    r = [0] * 40
    i = 0
    while a:
        r[i] = a & 1
        i += 1
        a >>= 1
    r.reverse()
    return r

def solve(a, b, k):
    a -= 1
    b -= 1
    k -= 1
    a = toBinary(a)
    b = toBinary(b)
    k = toBinary(k)
    cache = {}
    def f(i, extendA, extendB, extendK):
        if i == 40:
            return 1
        p = (i, extendA, extendB, extendK)
        if p in cache:
            return cache[p]
        ai = 1 if extendA else a[i]
        bi = 1 if extendB else b[i]
        ki = 1 if extendK else k[i]
        res = 0
        for x in range(ai+1):
            for y in range(bi+1):
                if (x & y) <= ki:
                    res += f(i+1, extendA or x < ai, extendB or y < bi, extendK or (x&y) < ki)
        cache[p] = res
        return res
    return f(0, False, False, False)

def sp(*a):
    # assert solveSimple(*a[:-1]) == a[-1]
    assert solve(*a[:-1]) == a[-1]
    pass

def sp2(a, b, k, r):
    sp(a+1, b+1, k+1, r)
    pass
def pad(a):
    return [0]*(40-len(a)) + a

def test():
    assert pad([1]) == [0]*39 + [1]
    assert toBinary(2) == pad([1, 0])
    assert toBinary(5) == pad([1, 0, 1])
    assert toBinary(0) == pad([])
    assert toBinary(0) == pad([0])
    assert toBinary(1) == pad([1])

    sp(2, 2, 2, 4)
    sp(1, 2, 2, 2)
    sp(2, 1, 2, 2)
    sp(1, 1, 2, 1)
    sp(1, 1, 1, 1)
    sp(2, 2, 1, 3)

    sp2(3, 3, 1, 12)
    sp2(3, 0, 1, 4)
    sp2(4, 3, 1, 16)
    sp2(3, 4, 1, 16)

    sp(3, 4, 2, 10)
    sp(4, 5, 2, 16)
    sp(7, 8, 5, 52)
    sp(45, 56, 35, 2411)
    sp(103, 143 ,88, 14377)

    for i in range(50):
        a = randint(1, 100)
        b = randint(1, 100)
        k = randint(1, 100)
        sp(a, b, k, solveSimple(a, b, k))

    for i in range(10):
        a = randint(10000000, 10000000)
        b = randint(10000000, 10000000)
        k = randint(10000000, 10000000)
        solve(a, b, k)
    pass

def readInt():
    return int(sys.stdin.readline().strip())
    
def readInts():
    return [int(x) for x in sys.stdin.readline().strip().split()]
    pass
def main():
    n= readInt()
    for i in xrange(n):
        a, b, k = readInts()
        print 'Case #%d: %d' % (i+1, solve(a, b, k))
    pass

if __name__ == '__main__':
    main()