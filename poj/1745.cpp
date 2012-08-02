#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

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
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define uint unsigned int
#define MAXN 10001
#ifdef LOCAL
// for debug
#define MAXK 7
#else
#define MAXK 101
#endif
int N, K;
int d[MAXN+1];
int first;
struct Data
{
	int times;
	int data;
};
Data datas[MAXK+1];
int dataNumber;
bool f[MAXK+1][MAXK+1];
bool modable[MAXK+1][MAXK+1];
int times[MAXK+1];
Data makeData(int t, int d)
{
	Data data = {t, d};
	return data;
}

int mod(int x, int y)
{
	ASSERT(y > 0);
	//consider nagetive x
	int z = (y-1)%y;
	return x >= 0 ? (x%y) : ((abs(x)*z)%y);
}
#define result(x) (x ? "Divisible" : "Not divisible")
void solve()
{
	ASSERT(mod(-1, 2) == 1);
	ASSERT(mod(-1, 10) == 9);
	ASSERT(mod(-2, 7) == 5);
	ASSERT(mod(-7, 7) == 0);
	ASSERT(mod(-7, 1) == 0);
	first = mod(first, K);
	if( N == 0)
	{
		cout << result(first == 0);
		return;
	}
	memset(times, 0, sizeof(times));
	forn(i, 0, N)
	{
		d[i] = mod(d[i], K);
		times[d[i]]++;
	}
	//Don't consider the data who mod K to 0
	dataNumber = 0;
	forn(i, 1, K)
	{
		if(times[i])
		{
			datas[dataNumber++] = makeData(times[i], i);
		}
	}

	memset(modable, 0, sizeof(modable));
	memset(f, 0,sizeof(f));
	for(int i = dataNumber - 1; i >= 0; i--)
		{
			forn(x, 0, datas[i].times+1)
			{
				// x means number of "+", then k is the mod of sum of x "+"s and (n-x) "-"s
				//k = (x * data - (n-x)*data)% K
				int k = mod((2* x - datas[i].times)*datas[i].data, K);
				modable[i][k] = true;
			}
		}

	for(int k = 0; k < K; k++)
			f[dataNumber-1][k] = modable[dataNumber-1][k];

	for(int i = dataNumber - 2; i >= 0; i--)
			for(int k = 0; k < K; k++)
		{
			bool possible = false;
			forn(x, 0, K)
			{
				possible = (modable[i][x] && (f[i+1][(x+k)%K] || f[i+1][(k-x+K)%K]));
				if(possible)
					break;
			}
			f[i][k] = possible;
			#ifdef LOCAL
			printf("f[%d][%d] :%d\n",  i, k, f[i][k]);
			#endif
		}

		cout << result(f[0][first] || f[0][(K-first)%K] ) ;
}

bool testcase()
{
	cin >>N >> K;
	if(!cin)
		return false;
	N--;
	//Skip first one
	cin >> first;
	forn(i, 0 , N)
		cin >> d[i];
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