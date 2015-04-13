#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os,re,sys,commands,glob,json,collections,random
from random import randint
   
def solve(s):
    n = len(s)
    s= [int(x) for x in list(s)]
    sum = 0
    need = 0
    for i in xrange(n):
        if s[i] != 0:
            if sum >= i:
                sum += s[i]
            else:
                need += i - sum
                sum += s[i] + need
    return need

def sp(*a):
    assert solve(*a[:-1]) == a[-1]
def test():
    sp('11111', 0)
    sp('09', 1)
    sp('01', 1)
    sp('110011', 2)
    sp('1100011', 3)
    sp('11000011', 4)
    sp('91000011', 0)
    sp('1',0)
    sp('0',0)
    sp('2',0)
    pass

def readInt():
    return int(sys.stdin.readline().strip())
    
def readInts():
    return [int(x) for x in sys.stdin.readline().strip().split()]

def readStrs():
    return sys.stdin.readline().strip().split()
    pass
def main():
    n = readInt()
    for i in xrange(n):
        _, s = readStrs()
        print 'Case #%d: %s' % (i+1, solve(s))
    pass

if __name__ == '__main__':
    main()