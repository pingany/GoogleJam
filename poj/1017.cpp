#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int
#define RUP(x, y) ((x+y-1)/y)

int s3LeftsFor2[4] = {9, 5, 3, 1};
int s3LeftsFor1[4] = {36, 7, 6, 5};
bool testcase()
{
	int a, b, c, d, e, f;
	cin >> f >> e >> d >> c >> b >> a;
	if(!(a||b||c||d||e||f))
		return false;
	int dn = RUP(d, 4);
	int ret = a + b + c + dn; //6x6, 5x5, 4x4, 3x3
	int s2left = 5*c + (d%4 != 0 ? s3LeftsFor2[d%4] : 0);
	if(e < s2left)
	{
		s2left -= e;
		e = 0;
	}
	else
	{
		e -= s2left;
		s2left = 0;
		if (e > 0)
		{	
			ret += RUP(e, 9);
			s2left = 9 - e % 9;
		}
	}
	int s1left = 11*b + s2left*4 + (d%4 != 0 ? s3LeftsFor1[d%4] : 0);
	f = max(0, f - s1left);
	ret += RUP(f, 36);
	cout << ret;
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}