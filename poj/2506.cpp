#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INLINE inline
#ifdef _MSC_VER
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
#define uint unsigned int

#define Integer unsigned int

typedef std::vector<unsigned char> BigIntegerReal, *BigInteger;

BigInteger f[251];
#define f(k) f[k]

BigInteger trim(BigInteger a)
{
	int newsize = a->size();
	forn2(i, a->size()-1, -1)
	{
		if(a->at(i) == 0)
			newsize = i;
		else
			break;
	}
	a->erase(a->begin() + newsize, a->end());
	return a;
}

BigInteger makeInteger(int x)
{
	ASSERT(x < 10);
	BigInteger ret = new BigIntegerReal();
	ASSERT(ret);
	ret->push_back(x);
	return ret;
}

// for print , set MOD to 10
#define MOD 10
BigInteger add(const BigInteger a, const BigInteger b)
{
	BigInteger ret = new BigIntegerReal();
	ASSERT(ret);
	int c = 0;
	int asize = a->size();
	int bsize = b->size();
	int n = max(asize, bsize)  + 1;
	ret->reserve(n);
	forn(i, 0, n)
	{
		int r = c + (i < asize ? a->at(i) : 0) + (i < bsize ? b->at(i) : 0);
		ret->push_back(r % MOD);
		c = r / MOD;
	}
	ASSERT(c == 0);
	return trim(ret);
}

BigInteger mul(const BigInteger a, int b)
{
	ASSERT(b == 2);
	BigInteger ret = new BigIntegerReal();
	ASSERT(ret);
	int c = 0;
	int asize = a->size();
	ret->reserve(asize + 1);
	forn(i, 0, (asize+1))
	{
		int r = c + (i < asize ? a->at(i) : 0) * b;
		ret->push_back(r % MOD);
		c = r / MOD;
	}
	ASSERT(c == 0);
	return trim(ret);
}

ostream& out(ostream&stream, const BigInteger a)
{
	forn2(i, a->size()-1, -1)
		stream << (int)a->at(i);
	return stream;
}

BigInteger get(int k)
{
	if(f(k))
		return f(k);
	return f(k) = add(get(k-1) , mul(get(k-2), 2));
}

bool testcase()
{
	int n;
	cin >> n;
	if(!cin)
		return false;
	out(cout, get(n));
	return true;
}

int main()
{
	memset(f, 0, sizeof(f));
	f[0] = makeInteger(1);
	f[1] = makeInteger(1);
	f[2] = makeInteger(3);
	f[3] = makeInteger(5);
#ifdef LOCAL
	forn(i, 1, 10)
	{
		out(cout, get(i));
		cout << endl;
	}
#endif
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}