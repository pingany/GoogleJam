#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#ifdef NO_HASH_MAP
#	define MAP map
#	include <map>
#else
#	if 0 //def __GNUC__
#		define MAP hash_map
#		include <ext/hash_map>
		using namespace __gnu_cxx;
#	elif defined(_MSC_VER)
#		define MAP hash_map
#		include <hash_map>
		using namespace stdext;
#   else 
#		define MAP map
#		include <map>
#	endif
#endif /* NO_HASH_MAP */

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
typedef unsigned long long LONG;
#define MAXN 5000
#define MAXX 1000000
struct Point
{
	int x, y;
};

#define IMPOSSIBLE MAX_INT
#define INVALID_VALUE (-1)
struct Value
{
	int value;
	Value() { value = INVALID_VALUE; }
};
typedef MAP<int, Value> ValueMAP;
int n;
int y;
Point ps[MAXN];
LONG pow2Y[MAXN]; /* ps[j].y^2 */
LONG mul2Y[MAXN];	/* (ps[j].y-y)^2 */
// ValueMAP maps[MAXN];
// #define f(i, startX) maps[i][startX].value
int f[MAXX+1];
#define f(x)  f[x]

inline LONG pow2(int x)
{
	return ((LONG)x)*x;
}
// LONG dis2(int x1, int y1, int x2, int y2)
// {
// 	return pow2(x1 - x2) + pow2(y1 - y2);
// }
int get(int startX)
{
	int r = f(startX);
	if(r != INVALID_VALUE)
		return r;
	int ret = IMPOSSIBLE;

	{

		forn2(j, n-1, -1)
		{
			if(ps[j].x <= startX)
			{
				break; // no more x can less than nx
			}
			LONG dis = pow2(startX - ps[j].x) + mul2Y[j]; //dis2(nx, y, ps[j].x, ps[j].y);
			if(dis <= pow2Y[j])
			{
				if( j == n-1)
				{
					ret = 1;
					break;
				}
				else
				{
					int nx = ps[j].x * 2 - startX;
					int nextRet = nx >= ps[n-1].x ? 0 : get(nx);
					if(nextRet != IMPOSSIBLE && nextRet + 1 < ret)
						ret = nextRet + 1;
				}
			}
		}
	}
	f(startX) = ret;
	return ret;
}

int dp2()
{
	int xstart = ps[0].x;
	int xend = ps[n-1].x;
	for(int startX = xend-1; startX >= xstart; startX--)
	{
		int ret = IMPOSSIBLE;
		for(int j = n-1; j>=0 ;j--)
		{
			if(ps[j].x <= startX)
			{
				break; // no more x can less than nx
			}
			LONG dis = pow2(startX - ps[j].x) + mul2Y[j]; //dis2(nx, y, ps[j].x, ps[j].y);
			if(dis <= pow2Y[j])
			{
				if( j == n-1)
				{
					ret = 1;
					break;
				}
				else
				{
					int nx = ps[j].x * 2 - startX;
					if (nx >= xend)
					{
						ret = 1;
						break;
					}
					else
					{
						int nextRet = f(nx);
						if(nextRet != IMPOSSIBLE && nextRet + 1 < ret)
							ret = nextRet + 1;
					}
				}
			}
		}
		f(startX) = ret;
	}
	return f(xstart);
}

#include <cmath>
// The one who works
int dp()
{

	int xstart = ps[0].x;
	int xend = ps[n-1].x;
	memset(f, 0xff, sizeof(f));
	int j = n-1;
	{
		f[xend] = 0;
		int maxOffset = sqrt((float)(pow2Y[j] - mul2Y[j])); // floor, not ceil
		for(int x = max(ps[j].x - maxOffset, xstart), end = ps[j].x;
			x < end;
			++x)
		{
			f[x] = 1;
		}
	}
	for(int j = n-2; j >0; j--)
	{
		int maxOffset = sqrt((float)(pow2Y[j] - mul2Y[j])); // floor, not ceil
		for(int x = max(ps[j].x - maxOffset, xstart), end = ps[j].x;
			x < end;
			++x)
		{
			int nx = min(ps[j].x * 2 - x, xend);
			int nextRet = f[nx];
			if(nextRet != -1)
			{
				if(f[x] == -1)	
					f[x] = nextRet + 1;
				else 
					f[x] = min(f[x], nextRet+1);
			}
		}
	}
	return f[xstart];
}

// DP, but by remember the status, TIME exceed
void solveByRemember()
{
	memset(f, 0xff, sizeof(f));
	int r = get(ps[0].x);
	if(r == IMPOSSIBLE)
		 r = -1;
	cout << r;
}

void solve()
{
	int r = dp();
	if(r == IMPOSSIBLE)
		 r = -1;
	cout << r;
}

bool testcase()
{
	cin >> n;
	forn(i, 0, n)
	{	
		cin >> ps[i].x >> ps[i].y;
		// maps[i].clear();
		pow2Y[i] = pow2(ps[i].y);
	}
	y = ps[0].y;
	forn(i, 0, n)
		mul2Y[i] = pow2(ps[i].y - y);
	solve();
	return true;
}

int main()
{
	ASSERT(sizeof(Value) == 4);
	ASSERT(freopen("in.txt", "r",stdin));
	int T;
	cin >> T;
	while(T--)
	{
		testcase();
		cout << "\n";
	}
	return 0;
}