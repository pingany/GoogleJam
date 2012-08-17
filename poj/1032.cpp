#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
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

int a[1000];
bool testcase()
{
	int x;
	cin >> x;
	if(!cin)
		return false;
	int n = (-1 + sqrt((float)(9 + 8 * x)))/2;
	int left = x - ((n+2)*(n-1)/2);
	ASSERT(left >= 0 && left <= n);
	forn(i, 2, n+1)
		a[i] = i;
	while(left)
	{
		forn2(i, n, 1)
		{
			a[i]++;
			left--;
			if(!left)
				break;
		}
	}
	bool firstNoSpace = true;
	forn(i, 2, n+1)
	{
		if(firstNoSpace)
			firstNoSpace = false;
		else
			putchar(' ');
		printf("%d", a[i]);
	}
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