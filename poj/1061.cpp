#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	{if(!(x)) __asm{int 3};}
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int

// return a % b, consider nagetive number
int mod(int a,int b)
{
	if(a >= 0)
		return a % b;
	else
		return a % b + b;
}

// return gcd(a, b), please make sure a > b
int gcd(int a,int b)
{
	ASSERT(a >= b);
	if(b == 0)
		return a;
	else
		return gcd(b,mod(a,b));
}

struct triple
{
	int x, y, d; /* result of ax + by = gcd(a,b), d = gcd(a, b) */
};

// resolve x from ax + by = gcd(a,b)
triple gcdEx(int a,int b)
{
	triple result;
	if(b == 0)
	{
		result.d = a;
		result.x = 1;
		result.y = 0;
	}
	else
	{
		triple ee = gcdEx(b,mod(a,b));
		result.d = ee.d;
		result.x = ee.y;
		result.y = ee.x - (a/b)*ee.y;
	}
	return result;
}

// resolve x from a*x == b(mod n)
int MLES(int a,int b,int n)
{
	triple ee = gcdEx(a,n);
	if(mod(b,ee.d) == 0)
		return mod((ee.x * (b / ee.d)),n / ee.d);
	else
		return -1;
}

bool testcase()
{
	int x, y, m, n, L;
	cin >> x >> y >> m >> n >> L;
	if(!cin)
		return false;
	int ret = MLES(m-n, y-x, L);
	if(ret >= 0)
		cout << ret;
	else 
		cout << "Impossible";
	return true;
}

int main()
{

	ASSERT(freopen("in.txt", "r",stdin));
#ifdef LOCAL
	while(testcase())
		cout << "\n";
#else
	testcase();
#endif
	return 0;
}