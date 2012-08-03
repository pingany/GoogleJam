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
