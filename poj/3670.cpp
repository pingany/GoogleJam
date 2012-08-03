#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define INLINE inline
#ifdef _MSC_VER
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
#define uint unsigned int
template<typename T>
T maxn(T* start, T*end)
{
	ASSERT(start != end);
	T result = *start;
	++start;
	while(start != end)
	{
		if(*start > result)
			result = *start;
		start++;
	}
	return result;
}

template<typename T>
T sumn(T*start, T*end)
{
	T result = T(0);
	while(start != end)
	{
		result += *start;
		start++;
	}
	return result;
}
#ifdef LOCAL
#define MAXN 5
#else
#define MAXN 30000
#endif
#define MAXGROUP 3

int f[MAXN+1][MAXGROUP+1];
int f2[MAXN+1][MAXGROUP+1];
int d[MAXN+1];
int n;
#define MAX_INT 0x7fffffffL
void solve()
{
	memset(f, 0, sizeof(f));
	memset(f2, 0, sizeof(f2));
	//f[n-1][x] = 0
	forn2(i, n-2, -1)
		forn(j, 0, MAXGROUP)
		{
			{
				int minf = MAX_INT;
				forn(k, j, MAXGROUP)
				{
					minf = min(minf, f[i+1][k]+ (d[i+1]==k ? 0 : 1));
				}
				f[i][j] = minf;


				int minf2 = MAX_INT;
				forn(k, 0, j+1)
				{
					minf2 = min(minf2, f2[i+1][k]+ (d[i+1]==k ? 0 : 1));
				}
				f2[i][j] = minf2;
			}
		}
	int minf = MAX_INT;
	forn(i, 0, MAXGROUP)
	{
		minf = min(minf, f[0][i] + (d[0] == i ? 0 : 1));
		minf = min(minf, f2[0][i] + (d[0] == i ? 0 : 1));
	}

	cout << minf;
}

bool testcase()
{
	cin >> n;
	if(!cin)
		return false;
	forn(i, 0, n)
	{
		cin >> d[i];
		d[i] --;
	}
	solve();
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	#ifdef LOCAL
	while(testcase())
		cout << endl;
	#else
	testcase();
	#endif
	return 0;
}