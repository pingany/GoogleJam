#!/bin/python
import sys,os,re,commands
from decimal import Decimal

def	d(x):
	return int(x) #Decimal(str(x))

def	rl():
	return sys.stdin.readline().strip()

def	rls(type):
	return map(type, rl().split(' '))

def	is0(x):
	return abs(x) < 1e-9
class Car:
	def __init__(self, r, s, p):
		self.r = r
		self.s = s
		self.p = p

	def __str__(self):
		return "[Car at %d(%s) speed %d]" % (self.p, self.r, self.s)

cs = []

class Line:
	def __str__(self):
		return "[Line (%.2f, %.2f), s = %.2f]" % (self.ts, self.p, self.s)
	def __init__(self, ts, te, car, cl=0):
		assert te > ts or te == -1
		self.ts = ts
		self.te = te
		self.s = car.s
		self.p = car.p + cl + self.s * self.ts
		if self.limited():
			self.pe = self.y(te)


	def y(self, t):
		return self.p + self.s * (t-self.ts)

	def limited(self):
		return self.te != -1

	def interect(l11, l22):
		l = [l11, l22]
		l.sort(lambda x, y: int(x.ts - y.ts))
		l1 = l[0]
		l2 = l[1]
		lm1 = l1.limited()
		lm2 = l2.limited()
		if lm1:
			if lm2:
				c1 = l1.cmpPos(l2.ts, l2.p)
				c2 = l1.cmpPos(l2.te, l2.pe)
				c3 = l2.cmpPos(l1.ts, l1.p)
				c4 = l2.cmpPos(l1.te, l1.pe)
				assert (is0(c1) and is0(c2)) == (is0(c3) and is0(c4))
				if is0(c1) and is0(c2):
					return l2.te > l1.ts and l2.te < l1.te
				else:
					return c1 * c2 < 0 and c3 * c4 < 0

			else: # lm1 and not lm2
				ts2 = l2.ts
				if ts2 == l1.ts or ts2 >= l1.te:
					return False
				else:
					# if l1 above l2(ts, p)
					c1 = l1.cmpPos(l2.ts, l2.p)
					# if l2 above l1(te, pe)
					c2 = l2.cmpPos(l1.te, l1.pe)
					return (is0(c1) or is0(c2)) \
						or (c1 * c2 > 0)
		else:
			if lm2:
				c1 = l1.cmpPos(l2.ts, l2.p)
				c2 = l1.cmpPos(l2.te, l2.pe)
				return (is0(c1) or is0(c2)) \
					or (c1 * c2 < 0)
			else:
				c = l1.cmpPos(l2.ts, l2.p)
				if is0(c):
					return l1.s == l2.s
				elif c > 0:
					return l1.s < l2.s
				else:
					return l1.s > l2.s


	def cmpPos(self, x, y):
		sy = self.y(x)
		return sy - y
class Block:
	def __init__(self, lines):
		self.lines = lines
		assert len(lines) == 2 or len(lines) == 4
		if self.limited():
			self.ps = [(self.lines[0].ts, self.lines[0].p),\
			(self.lines[0].te, self.lines[0].pe),\
			(self.lines[2].ts, self.lines[2].p),\
			(self.lines[2].te, self.lines[2].pe)\
			]
		else:
			self.ps = [(self.lines[0].ts, self.lines[0].y(self.lines[0].ts)),\
			(self.lines[1].ts, self.lines[1].y(self.lines[1].ts))]
	def __str__(self):
		return " Block " + " ".join([str(x) for x in self.lines])

	def limited(self):
		return len(self.lines) == 4

	def containPoint(b, x, y):
		if b.limited():
			return b.lines[0].cmpPos(x, y) <= 0 \
			and b.lines[1].cmpPos(x, y) >= 0\
			and b.lines[2].cmpPos(x, y) >= 0 \
			and b.lines[3].cmpPos(x, y) <=0
		else:
			return b.lines[0].cmpPos(x, y) <= 0 \
			and b.lines[1].cmpPos(x, y) >= 0


	def containBlock(b1, b2):
		if b2.limited():
			ret = True
			for x, y in b2.ps:
				if not b1.containPoint(x, y):
					ret = False
					break
		else:
			ret = True
			for x, y in b2.ps:
				if not b1.containPoint(x, y):
					ret = False
					break
			ret = ret and (not b1.limited()) and b1.lines[0].s == b2.lines[0].s
		print "%s contain %s ? %d" % (str(b1), str(b2), ret)
		return ret

	def interect(b1, b2):
		if b1.containBlock(b2) or b2.containBlock(b1):
			ret = True
		else:
			ret = False
			for l1 in b1.lines:
				for l2 in b2.lines:
					if l1.interect(l2):
						ret = True
						break
		print "%s interect %s ? %d" % (str(b1), str(b2), ret)
		return ret

class Crash:
	# cari's speed is bigger than carj's
	# cari's pos is near than carj's
	def __init__(self, cari, carj, ts, te):
		assert cs[cari].s >= cs[carj].s
		self.cari = cari
		self.carj = carj
		self.ts = ts
		self.te = te
		self.tm = (ts + te)/2

	def createBlock(self):
		if self.te != -1:
			assert self.te > 0
			return Block([Line(self.ts, self.tm, cs[self.carj]), Line(self.ts, self.tm, cs[self.cari], CL), \
				Line(self.tm, self.te, cs[self.carj], CL), Line(self.tm, self.te, cs[self.cari])])
		else:
			return Block([Line(self.ts, self.te, cs[self.cari]), Line(self.ts, self.te, cs[self.carj], CL)])

	def __str__(self):
		return "%s and %s crash: t = [%.2f, %.2f]" \
		% (str(cs[self.cari]), str(cs[self.carj]), self.ts, self.te)

def cmp_p(x, y):
	return x.p - y.p

CL = 5
sys.stdin = open("in.txt")
case = 1
tcase = int(rl())
while case <= tcase:
	n = int(rl())
	cs = [None]*n
	for i in range(0, n):
		r, s, p = rl().split(' ')
		cs[i] = Car(r, int(s), int(p))
	cs.sort(cmp_p)
	crashs = []
	for i in range(0, n-1):
		for j in range(i+1, n):
			assert cs[j].p >= cs[i].p

			if cs[i].s == cs[j].s:
				if cs[j].p - cs[i].p < CL:
					crashs.append(Crash(i, j, 0, -1))
			elif cs[i].s > cs[j].s:
				dis = cs[j].p - cs[i].p
				speeddif = cs[i].s - cs[j].s
				ts = max(0, (dis - CL + 0.0)/speeddif)
				te = (dis + CL + 0.0)/speeddif
				crashs.append(Crash(i, j, ts, te))

	for c in crashs:
		print str(c)

	blocks = map(Crash.createBlock, crashs)
	blocks.sort(lambda x, y: int(x.lines[0].ts - y.lines[0].ts))

	nb = len(blocks)
	possible = True
	ret = 0.0
	def hello():
		for i in range(0, nb-1):
			for j in range(i+1, nb):
				if blocks[i].interect(blocks[j]):
					ret = blocks[i].lines[0].ts
					return False
		return True
	possible = hello()
	if possible:
		print "Case #%d: Possible" %(case)
	else:
		print "Case #%d: %.6f" %(case, ret)
	case +=1
