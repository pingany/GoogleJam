#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os,re,sys,commands,glob,json,collections,random
from random import randint
# from LeetCodeUtils import *
   
head = tail = cycles = mid = None

def simplify(car):
    car = list(car)
    k = 1
    for i in range(1, len(car)):
        if car[i] != car[i-1]:
            car[k] = car[i]
            k += 1
    del car[k:]
    return car

def handle(car):
    if car[0] in head:
        return False
    head[car[0]] = car

    if car[-1] in tail:
        return False
    tail[car[-1]] = car

    for i in range(1, len(car)-1):
        x = car[i]
        if x in mid:
            return False
        mid.add(x)
    for list in (head, tail, cycles):
        for x in list:
            if x in mid:
                return False
    return True

def countFrom(cars, car):
    c = 0
    while True:
        c += 1
        x = car[-1]
        if x in head:
            car = head[x]
        else:
            break
    return c

def mul(*args):
    r = 1
    for x in args:
        r = (r * x) % 1000000007
    return r

def fact(x):
    s = 1
    i = 1
    while i <= x:
        s = (s * i) % 1000000007
        i += 1
    return s

def solve(cars):
    global head, tail, cycles, mid
    head = {}
    tail = {}
    cycles = collections.defaultdict(lambda:0)
    mid = set()

    cars2 = []
    for car in cars:
        if not car:
            continue
        car = simplify(car)
        if len(car) == 1:
            cycles[car[0]] += 1
        else:
            cars2.append(car)
    cars = cars2
    for car in cars:
        if not handle(car):
            return 0

    chains = 0
    visitedCount = 0
    for car in cars:
        if car[0] not in tail:
            chains += 1
            visitedCount += countFrom(cars, car)
    if visitedCount < len(cars):
        return 0
            
    independentUnits = chains
    for x in cycles.keys():
        if x not in head and x not in tail:
            independentUnits += 1

    r = 1
    for x in cycles.values():
        r = (r * fact(x)) % 1000000007
    r = (r * fact(independentUnits)) % 1000000007
    return r        
def sp(*a):
    assert solve(*a[:-1]) == a[-1]
    pass
def test():
    assert simplify("1") == ['1']
    assert simplify("11") == ['1']
    assert simplify("111") == ['1']
    assert simplify("1221") == list('121')
    assert simplify("1122") == list('12')
    assert simplify("112233") == list('123')

    assert fact(0) == 1
    assert fact(1) == 1
    assert fact(2) == 2
    assert fact(3) == 6
    assert fact(4) == 24

    sp(["ab", "bbbc", "cd"], 1)
    sp(["a", "aa", "bc", 'c'], 4)
    sp(["a", "aa", "bc", 'c', 'cd'], 4)
    sp(["abc", "bcd"], 0)

    sp([''], 1)
    sp(['a'], 1)
    sp(['aa'], 1)
    sp(['aa', 'a'], 2)
    sp(['aaaa']*100, fact(100))
    sp(['aaaa']*100+['bbb']*101, mul(fact(100), fact(101), 2))
    sp(['aaaa']*100+['b']*101, mul(fact(100), fact(101), 2))
    sp(['ab', 'ba'], 0)
    sp(['ab', 'bc', 'ca'], 0)
    sp(['aba'], 0)
    sp(['ab'], 1)
    sp(['az'], 1)
    sp(['abcdefg'], 1)
    sp(['abcbde'], 0)
    sp(['abc', 'bbbb'], 0)
    sp(['ac', 'ca'], 0)
    sp(['abc', 'bd'], 0)
    sp(['abc', 'db'], 0)
    sp(['abcdefghijklmoqprstuvwxyz'], 1)
    pass

def main():
    f = sys.stdin
    n = int(f.readline().strip())
    for index in range(1, n+1):
        t = int(f.readline().strip())
        list = f.readline().strip().split(' ')
        print 'Case #%d: %d' % (index, solve(list))
    pass

if __name__ == '__main__':
    main()