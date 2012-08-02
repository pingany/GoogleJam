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
bool f[MAXN+1][MAXK+1];

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
	int realN = 0;
	forn(i, 0, N)
	{
		d[i] = mod(d[i], K);
		//Don't consider the data who mod K to 0
		if(d[i] != 0)
			d[realN++] = d[i];
	}
	N =realN;
	#ifdef LOCAL
	forn(i, 0, N)
		cout << " " << d[i];
	cout << "\n"; 
	#endif
	memset(f, 0,sizeof(f));
	for(int i = N-1; i>= 0; i--)
	{
		forn(k, 0, K)
		{
			int t = d[i];
			if(i == N-1)
			{
				f[i][k] = (t == k);
			}
			else
			{
				f[i][k] = f[i+1][(t+k)%K] || f[i+1][(k-t+K)%K];
			}
			#ifdef LOCAL
			printf("f[%d][%d] :%d\n",  i, k, f[i][k]);
			#endif
		}
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