#!/bin/python

import os,re,sys

from decimal import Decimal

def main (argv):
	tcases = int(sys.stdin.readline().strip())
	case = 1
	while case <= tcases:
		js = map(int, sys.stdin.readline().strip().split(' '))
		n = js[0]
		js = map(float, js[1:])
		X = sum(js)	

		t = js[:]
		while True:
			A = ( X + sum(t) )/len(t)
			t2 = filter(lambda x : x < A, t)
			if len(t2) == len(t) or len(t2) == 0:
				break
			t = t2
		
		#print "A " + str(A) + " t " + str(t)

		rs = []
		for m in js:
			if m not in t:
				r = 0
			else:
				r = ( A - m )/X * 100
			rs.append(r)
		
		print ("Case #%d: " % case) + " ".join([ "%.6f" % r for r in rs ])
		case +=1

if __name__ == "__main__":
	sys.exit(main(sys.argv))
