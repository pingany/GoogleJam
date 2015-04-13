#!/usr/bin/env python
#-*- coding: utf-8 -*-


# Wrong


import os,re,sys,commands,glob,json,collections,random,heapq
from random import randint

DEBUG = False

class PriorityQueue:  
    def __init__(self, asec=True):  
        self._queue = []  
        self.asec = asec
  
    def push(self, item):  
        priority = -item if self.asec else item
        heapq.heappush(self._queue, (-priority, item))  
  
    def pop(self):  
        return heapq.heappop(self._queue)[-1]  

    def empty(self):
        return len(self._queue) == 0

def solve(p):
    n = len(p)
    def ok(minutes):
        s = PriorityQueue(False)
        for x in p:
            s.push(x)
        for m in range(minutes, 0, -1):
            x = s.pop()
            if x <= m:
                return True
            x -= (m-1)
            s.push(x)
        return False

    p.sort(reverse=True)
    l = 0
    h = p[0]
    while l < h:
        m = (l+h)/2
        if ok(m):
            h = m
        else:
            l = m+1
        pass
    return h

def sp(*a):
    assert solve(*a[:-1]) == a[-1]
def test():
    sp([3], 3)
    sp([1, 2, 1,2], 2)
    sp([4], 3)
    sp([9], 5)
    sp([10], 5)
    sp([11], 5)
    sp([12], 6)
    sp([15], 6)
    sp([16], 6)
    sp([17], 7)
    sp([1], 1)
    sp([2], 2)
    sp([2]*1000, 2)
    sp([1]*1000, 1)
    sp([3]*1000, 3)
    sp([1000]*1000, 1000)
    sp([2,3,4,6], 4)
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
        if DEBUG:
            print p
        print 'Case #%d: %s' % (i+1, solve(p))
    pass

if __name__ == '__main__':
    main()