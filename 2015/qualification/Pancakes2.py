#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os,re,sys,commands,glob,json,collections,random
from random import randint
   
def ROUNDUP(x, y):
    return (x + y -1 ) / y
    pass
def solve(p):
    p.sort(reverse=True)
    minTime = p[0]
    for eatTime in xrange(p[0]-1, 0, -1):
        time = eatTime
        for x in p:
            if x <= eatTime:
                break
            time += ROUNDUP(x - eatTime, eatTime)
            if time >= minTime:
                break
        minTime = min(minTime, time)
    return minTime

def sp(*a):
    assert solve(*a[:-1]) == a[-1]

def test():
    sp([3], 3)
    sp([1, 2, 1,2], 2)
    sp([4], 3)
    sp([9], 5)
    sp([1], 1)
    sp([2], 2)
    sp([2]*1000, 2)
    sp([1]*1000, 1)
    sp([3]*1000, 3)
    sp([1000]*1000, 1000)
    sp([2,3,4,6], 5)
    pass

def readInt():
    return int(sys.stdin.readline().strip())
    
def readInts():
    return [int(x) for x in sys.stdin.readline().strip().split()]

def main():
    n = readInt()
    for i in xrange(n):
        d = readInt()
        p = readInts()
        print 'Case #%d: %s' % (i+1, solve(p))
    pass

if __name__ == '__main__':
    main()