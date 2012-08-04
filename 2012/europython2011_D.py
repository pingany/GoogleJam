#!/bin/python
import sys,os,re,commands
from decimal import Decimal
sys.setrecursionlimit(10000)

def	d(x):
	return int(x) #Decimal(str(x))

def	rl():
	return sys.stdin.readline().strip()

def	rls(type):
	return map(type, rl().split(' '))

def	log(*x):
	if not "NDEBUG" in os.environ:
		print x

sys.stdin = open("in.txt")
case = 1
tcase = int(rl())
while case <= tcase:
	n = int(rl())
	follows = rls(int)

	fs = [None]*n
	for i in range(0, n):
		fs[i] = []
	assert len(follows) == len(fs)
	for i in range(0, n):
		fs[follows[i]-1] += [i]

	print "Case #%d:" %(case)
	for i in range(0, n):
		vis = [False]*n
		def dfs(i):
			vis[i] = True
			for f in fs[i]:
				if not vis[f]:
					dfs(f)
		dfs(i)
		print sum(map(lambda x : x and 1 or 0, vis))
	case +=1
