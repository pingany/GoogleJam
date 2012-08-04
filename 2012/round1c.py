#!/bin/python

import os,re,sys

sys.path.append("E:/work/sdk/tools")
from FucusUtils import log

sys.setrecursionlimit(2000)

def dfs (g, v, i):
	v[i] = True
	for j in g[i]:
		if v[j]:
			return True
		else:
			x = dfs(g, v, j)
			if x:
				return x
	return False
		

def main (argv):
	case = 1
	tcases = int(sys.stdin.readline().strip())
	while case <= tcases:
		n = int(sys.stdin.readline().strip())
		g = [None]* (n+1)
		for i in range(1, n+1):
			g[i] = map(int, sys.stdin.readline().strip().split(" ")[1:])
		log(g)	
		
		r = False
		for i in range(1, n+1):
			v = [False] *(n+1)
			if dfs(g, v, i):
				r = True
				break

		print "Case #%d: %s" %(case, r and "Yes" or "No")
		case +=1

if __name__ == "__main__":
	sys.stdin = open("in.txt")
	sys.exit(main(sys.argv))
# =======
# import sys,os,re,commands
# from decimal import Decimal

# def  d(x):
# 	return int(x) # Decimal(str(x))

# def	rl():
# 	return sys.stdin.readline().strip()

# def	main(argv):
# 	case = 1
# 	tcase = int(rl())

# 	while case <= tcase:
# 		N, M = map(int, rl().split(' '))
# 		a = map(d, rl().split(' '))
# 		b = map(d, rl().split(' '))

# 		hashmap = {}
# 		def sf(i, j):
# 			return "%d_%d_%d_%d" % (i, j, a[i], b[j])

# 		def has(i, j):
# 			return  sf(i,j) in hashmap

# 		def get(i, j):
# 			return hashmap[sf(i,j)]

# 		def store(i, j, value):
# 			hashmap[sf(i,j)] = value

# 		#print a, b
# 		def next(a, i1, bj):
# 			i = i1
# 			i +=2
# 			while i < len(a):
# 				if a[i+1] == bj:
# 					break
# 				i +=2
# 			#print "next ",a, i1, i, bj
# 			return i
# 		def func(a, b, i, j):
# 			r = 0
# 			if i >= len(a) or j >= len(b) :
# 				r = 0
# 			else:
# 				if has(i, j):
# 					r = get(i, j)
# 				else:
# 					if a[i+1] == b[j+1]:
# 						m = min(a[i], b[j])
# 						if a[i] == b[j]:
# 							r = m + func(a, b, i+2, j+2)
# 						elif a[i] > b[j]:
# 							a[i] -= m
# 							r = m + func(a, b, i, j+2)
# 							a[i] += m
# 						else :
# 							b[j] -= m
# 							r = m+ func(a, b, i+2, j)
# 							b[j] += m
# 					else:
# 						r = max(func(a, b, next(a, i, b[j+1]), j), func(a, b, i, j+2))
# 				store(i, j, r)
# 			#print i, j, "ret = ",  r

# 			return r
# 		print "Case #%d: %d" %(case, func(a, b, 0, 0))
# 		case +=1
# 	pass

# if __name__ == "__main__":
# 	sys.stdin = open("in.txt")
# 	main(sys.argv)
# >>>>>>> Google jam 2012
