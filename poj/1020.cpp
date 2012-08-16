#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
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

int size, n ;
int s[16];
char lens[40];
int visit[16];
#define visited(x) visit[x]
inline int pow2(int a) { return a * a;}
inline void put(int x, int y, int index)
{
	visit[index] = 1;
	int a = s[index];
	memset(lens+x, y+a, a);
	// forn(i, x, x+a)
	// {
	// 	ASSERT(lens[i] == y);
	// 	lens[i] +=a;
	// }
}

inline void unput(int x, int y, int index)
{
	visit[index] = 0;
	int a = s[index];
	memset(lens+x, y, a);
	// forn(i, x, x+a)
	// {
	// 	ASSERT(lens[i] == y+a);
	// 	lens[i] = y;
	// }
}

bool canput(int x, int y, int index)
{
	int a = s[index];
	if(!(y + a <= size && x + a <= size))
		return false;
	int xend = x+a;
	forn(i, x, xend)
	{
		if(lens[i] != y)
			return false;
	}
	return true;
}

bool tryPut(int x, int putted)
{
	int prev = -1;
	if(putted == n)
		return true;
	if(x == size)
		x = 0;
	forn(i, 0, n)
	{
		int y = lens[x];
		if(!visited(i))
		{
			if(s[i] == prev)
				continue;
			else
				prev = s[i];
			if(canput(x, y, i))
			{
				put(x, y, i);
				if(tryPut(x + s[i], putted+1))
					return true;
				unput(x, y, i);
			}
		}
	}
	return false;
}

bool solve()
{
	int sum = 0;
	forn(i, 0, n)
		sum += pow2(s[i]);
	if(sum != pow2(size))
		return false;
	sort(s, s+n, greater<int>());
	memset(lens, 0, sizeof(lens));
	memset(visit, 0, sizeof(visit));
	put(0, 0, 0);
	return tryPut(s[0], 1);
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	int T;
	cin >> T;
	while(T--)
	{
		cin >> size;
		cin >> n;
		forn(i, 0, n)
			cin >> s[i];
		cout << (solve() ? "KHOOOOB!\n" : "HUTUTU!\n");
	}
	return 0;
}