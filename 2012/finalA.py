#!/bin/python
import sys,os,re,commands
from decimal import Decimal

def	d(x):
	return int(x) #Decimal(str(x))

def	rl():
	return sys.stdin.readline().strip()

def	rls(type):
	return map(type, rl().split(' '))

def PermutationEnumerator(items, n=None):
    if n is None:
        n = len(items)
    for i in range(len(items)):
        v = items[i:i+1]
        if n == 1:
            yield v
        else:
            rest = items[:i] + items[i+1:]
            for p in PermutationEnumerator(rest, n-1):
                yield v + p

class Zommbie:
	def __init__(self, x, y, t):
		self.x = x
		self.y = y
		self.t = t

def dis(z1, z2):
	return max(abs(z1.x - z2.x), abs(z1.y - z2.y))

sys.stdin = open("in.txt")
sys.stdout= open("out.txt", "w")
case = 1
tcase = int(rl())
while case <= tcase:
	z = int(rl())
	zs = [None]*z
	for i in range(z):
		x, y, t = rls(int)
		zs[i] = Zommbie(x, y, t)
	maxscore = 0
	for indexs in PermutationEnumerator(range(z)):
		chargeTime = 0
		prevZommbie = Zommbie(0, 0, 0)
		now = 0
		score = 0
		for index in indexs:
			distance = dis(prevZommbie, zs[index])
			possibleTime = now + max(chargeTime, distance*100)
			if possibleTime > zs[index].t + 1000:
				break
			score += 1
			chargeTime = 750
			prevZommbie = zs[index]
			now = max(zs[index].t, possibleTime)
		if score > maxscore:
			maxscore = score

	print "Case #%d: %d" %(case, maxscore)
	case +=1
