#!/bin/python
import sys,os,re,commands
from decimal import Decimal

def	log(*x):
	if "NDEBUG" not in os.environ:
		print x

def	d(x):
	return int(x) #Decimal(str(x))

def	rl():
	return sys.stdin.readline().strip()

def	rls(type):
	return map(type, rl().split(' '))

class Node:
	def __init__(self, pos, length, maxn):
		self.pos = pos
		self.len = length
		self.maxn = maxn
	def __str__(self):
		return "(pos: %d, len: %d, max: %d)" %(self.pos, self.len, self.maxn)

sys.stdin = open("in.txt")
case = 1
tcase = int(rl())
while case <= tcase:
	n = int(rl())
	p = [None]*n
	assert n > 0
	for i in range(0, n):
		pos, length = rls(int)
		p[i] = Node(pos, length, -1)

	D = int(rl())
	p.append(Node(D, 0, -1))
	n = len(p)

	#p.sort(cmp=lambda x, y: x.pos - y.pos)

	ok = None
	def getNextMax(cur, prePos):
		return cur.pos + min(cur.len, cur.pos - prePos)

	p[0].maxn = getNextMax(p[0], 0)

	for i in range(0, n-1):
		#log(i, [x.__str__() for x in p])
		v = p[i]
		for j in range(i+1, n):
			uv = p[j]
			if uv.pos <= v.maxn:
				x = getNextMax(uv, v.pos)
				if x > uv.maxn:
					uv.maxn = x
			else:
				break

	ok = p[n-1].maxn != -1

	assert ok is not None
	print >>sys.stderr, "Case #%d: %s" %(case, ok and 'YES' or "NO")
	case +=1
