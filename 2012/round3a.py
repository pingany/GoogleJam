#!/bin/python
import os, sys, re

class Level:
	def __init__(self, t, p, order):
		self.t = t
		self.p = p 
		self.order = order

	def __cmp__(self, another):
		if self.order == another.order and self.t == another.t and self.p == another.p:
			return 0
		else:
			return 1

	def __str__(self):
		return str([self.t, self.p, self.order])

	def __repr__(self):
		return self.__str__()

def calc(l1, l2):
	return l1.t * (100 * l1.p + 100 * l2.p - l1.p*l2.p) + (100 - l1.p)*l2.p * l2.t

def cmpLs(l1, l2):
	c = calc(l1, l2) - calc(l2, l1)
	if c == 0:
		return l1.order - l2.order
	else:
		return c

def cmpLsSimple(l1, l2):
	c = l2.p - l1.p
	# if c == 0:
	# 	c = l1.t - l2.t
	if c == 0:
		c = l1.order - l2.order
	return c

def main (argv):
	case = 1
	tcases = int(sys.stdin.readline().strip())
	while case <= tcases:
		n = int(sys.stdin.readline().strip())
		ls = [None]*n;
		ts = map(int, sys.stdin.readline().split(' '))
		ps = map(int, sys.stdin.readline().split(" "))
		for i in range(len(ts)):
			ls[i] = Level(ts[i], ps[i], i)
		# ls2 = ls[:]
		ls.sort(cmp=cmpLs)
		# ls2.sort(cmp=cmpLsSimple)
		# assert all([ls[i] == ls2[i] for i in range(len(ls))])
		print "Case #%d: %s" % (case, " ".join([str(l.order) for l in ls]))
		case = case + 1

if __name__ == "__main__":
	sys.stdin = open("in.txt")
	# sys.stdout = open("out.txt", "w")
	sys.exit(main(sys.argv))