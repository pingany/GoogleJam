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

#define MAXN 10000
int n;
int targets[MAXN+1];
int traces[MAXN+1];
int freeSpace;

bool moved = false;
int findMoveable()
{
	forn(i, 1, n+1)
	{
		if(targets[i])
			return i;
	}
	return -1;
}

bool solve1()
{
	int start = findMoveable();
	if(start < 0)
		return false;
	int m = 0;
	int x = targets[start];
	traces[m++] = start;
	while(x != start && x != 0)
	{
		traces[m++] = x;
		x = targets[x];
	}
	if( m == 1)
	{
		targets[start] = 0;
		return true;	
	}
	if(x == 0)
	{
		moved = true;
		forn2(i, m-1, 0)
		{
			printf("%d %d\n", traces[i-1], traces[i]);
		}
		
		forn(i, 0, m)
			targets[traces[i]] = 0;
		freeSpace = start;
	}
	else
	{
		moved = true;
		// in cicle
		printf("%d %d\n", traces[m-1], freeSpace);
		forn2(i, m-1, 0)
		{
			printf("%d %d\n", traces[i-1], traces[i]);
		}
		printf("%d %d\n", freeSpace, traces[0]);
		forn(i, 0, m)
			targets[traces[i]] = 0;
	}
	return true;
}
bool testcase()
{
	int k, s, x;
	cin >> n >> k;
	if(!cin)
		return false;
	int place = 0;
	memset(targets, 0, sizeof(targets));
	while(k--)
	{
		cin >> s;
		while(s--)
		{
			cin >> x;
			++place;
			targets[x] = place;
		}
	}
	forn(i, 1, n+1)
	{
		if(!targets[i])
		{
			freeSpace = i;
			break;
		}
	}
	moved = false;
	while(solve1());
	if(!moved)
		printf("No optimization needed");
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