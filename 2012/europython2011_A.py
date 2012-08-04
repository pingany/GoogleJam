#!/bin/python
import sys,os,re,commands
from decimal import Decimal

def	d(x):
	return int(x) #Decimal(str(x))

def	rl():
	return sys.stdin.readline().strip()

def	rls(type):
	return map(type, rl().split(' '))

sys.stdin = open("in.txt")
case = 1
tcase = int(rl())
while case <= tcase:
	name = rl()
	c = name[len(name) - 1].lower()
	out = ""
	if c in 'aeiou':
		out = "is ruled by a queen."
	elif c in "y":
		out = "is ruled by nobody."
	else:
		out = "is ruled by a king."
	print "Case #%d: %s %s" %(case, name, out)
	case +=1
