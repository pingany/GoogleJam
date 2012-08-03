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

#define MAX_INT 0x7fffffffL
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
#define uint unsigned int
uint f[100][100];
int n;
int d[100];
#define f(i, j)  f[i][j]
void solve()
{
	forn2(i, n-1, -1)
		forn(j, i+1, n)
			{
				if(j == i+1)
				{
					f(i, j) = 0;
				}
				else if(j == i+2)
				{
					f(i, j) = d[i] * d[i+1] * d[j];
				}
				else
				{
					uint minf = MAX_INT;
					// k: the last element to be taken out in internal (i, j)
					forn(k, i+1, j)
					{
						minf = min(minf, d[i]*d[k]*d[j] + f(i, k) + f(k, j));
					}
					f(i, j) = minf;
				}
			}
			cout << f(0, n-1);
}
bool testcase()
{
	cin >> n;
	if(!cin)
		return false;
	forn(i, 0, n)
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