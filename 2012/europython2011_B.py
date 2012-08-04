#!/bin/python
import sys,os,re,commands
from decimal import Decimal

def	d(x):
	return int(x) #Decimal(str(x))

def	rl():
	return sys.stdin.readline().strip()

def	rls(type):
	return map(type, rl().split(' '))

def	resolve(ss, index):
	ss[0], ss[index] = ss[index], ss[0]
	s = ss[0]
	n = len(s)
	lenss = len(ss)
	ret = None
	if 1 == len(ss):
		ret = '""'
	else:
		for length in range(1, n+1):
			subs = []
			for i in range(0, n-length+1):
				subs.append( s[i:i+length])
			subs.sort()
			for sub in subs:
				ok = True
				for j in range(1, lenss):
					if sub in ss[j]:
						ok = False
						break
				if ok:
					ret = '"%s"'% sub
					break
			if ret is not None:
				break
	ss[0], ss[index] = ss[index], ss[0]
	if ret is None:
		ret = ":("
	return ret

def main():
	sys.stdin = open("in.txt")
	case = 1
	tcase = int(rl())
	while case <= tcase:
		n = int(rl())
		ss = [None]*n
		for i in range(0, n):
			ss[i] = rl().upper()
		#print ss
		print "Case #%d:" %(case)
		for i in range(0, n):
			print '%s' % resolve(ss, i)

		case +=1
main()