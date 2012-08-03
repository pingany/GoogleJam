#!/bin/python
import os, sys, re
class Point:
	"""docstring for Point"""
	def __init__(self, x, y):
		self.x = x
		self.y = y

board = [None] * (10000*10000*2)

def 
def put(x, y):
	board

def main (argv):
	case = 1
	tcases = int(sys.stdin.readline().strip())
	while case <= tcases:
		S, M = map(int, sys.stdin.readline().strip().split(' '))
		ps = [None]*10000
		for i in range(M):
			x, y = map(int ,sys.stdin.readline().strip().split(' '))
			ps[i] = new Point(x, y)
		case = case + 1

if __name__ == "__main__":
	sys.stdin = open("in.txt")
	# sys.stdout = open("out.txt", "w")
	sys.exit(main(sys.argv))