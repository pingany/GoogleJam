#!/bin/python
import sys,os,re,commands
from decimal import Decimal

def	d(x):
	return int(x) #Decimal(str(x))

def	rl():
	return sys.stdin.readline().strip()

def	rls(type):
	return map(type, rl().split(' '))

def	scmp(s1, s2):
	if s1 == s2:
		return 0
	elif s1 < s2:
		return -1
	else:
		return 1
sys.stdin = open("in.txt")
case = 1
tcase = int(rl())
while case <= tcase:
	s = rl()
	aeiou = []
	for i in range(0, len(s)):
		if s[i] in 'aeiou':
			aeiou.append(i)
	#print aeiou
	ret = "Nothing."
	if len(aeiou) < 5:
		pass
	else:
		subs = []
		for i in range(0, len(aeiou) - 1):
			subs.append([aeiou[i], aeiou[i+1]])
		#print s, subs
		def cmp1(i, j):
			s1 = s[i[0] : i[1]+1]
			s2 = s[j[0] : j[1]+1]
			#print s1,s2
			return scmp(s1, s2)
		ok = False
		for i in range(0, len(subs) - 1):
			for j in range(i+1, len(subs)):
				if cmp1(subs[i], subs[j]) == 0 and abs(subs[i][0] - subs[j][0]) > 2:
					ret = "Spell!"
					ok = True
			if ok:
				break


	print "Case #%d: %s" %(case, ret)

	case +=1
