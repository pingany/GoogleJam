#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	{if(!(x)) __asm{int 3};}
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define MIN_INT (-2147483648L)

#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int
#define MAXN 200
int low[MAXN], up[MAXN], pairs[MAXN], multi[MAXN], limit[MAXN], table[MAXN];
int n;

#define MAXX (25*20*200)
int f[MAXX+1]; //, g[MAXX+1];
#define f(X) f[X]
// #define g(X) gg[X]
#define IMPOSSBILE (-1)
#define reset(x)  memset(x, 0xff, sizeof(x))

int generateKs(int x, int out[])
{
	int outi = 0;
	int k = 1;
	for(;;)
	{
		if(k < x)
		{
			out[outi++] = k;
			x -= k;
		}
		else
		{
			out[outi++] = x;
			break;
		}
		k <<= 1;
	}
	return outi;
}

int solve2()
{
	int lowSum = 0;
	forn(i, 0, n)
		lowSum += low[i] * multi[i];
	forn(i, 0, n)
		limit[i] = up[i] - low[i];

	int question = -lowSum;
	ASSERT(question >= 0);
	const int minX = 0, maxX = 25*20*200;
	
	reset(f);

	//handle i = 0 first;
	forn(k, 0, limit[0]+1)
	{
		f(k*multi[0]) = k*pairs[0];
	}
	int out[100];
	int start;
	const int end = maxX;
	forn(i, 1, n)
	{
		// if(i == n-1)
		// {
		// 	start = question;
		// 	end = question; // just consider X=0
		// }
		// else
		{
			start = minX;
			// end = maxX;
		}

		int kn = generateKs(limit[i], out);
		forn(j, 0, kn)
		{	
			int k = out[j];
			start = max(start, minX + k * multi[i]);
			for(int X = end; X >=start; --X)
			{
				int prevX = X - k*multi[i];
				{
					int subf = f(prevX);
					if(subf != IMPOSSBILE)
						f(X) = max(f(X), k*pairs[i] + subf);
				}
			}
		}
	}
	int lowPairSum = 0;
	forn(i, 0, n)
		lowPairSum += low[i] * pairs[i];

	return f(question) + lowPairSum;
}

bool testcase()
{
	if(1 != scanf("%d", &n))
		return false;
	forn(i, 0, n)
	{
		scanf("%d%d%d%d", &pairs[i] , &multi[i], &low[i] , &up[i]);
	}
	printf("%d\n", solve2());
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}