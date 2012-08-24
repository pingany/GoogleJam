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
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int
char s[12][5];
const	int n = 12;


bool works(int i, int j, int k)
{
	forn(x , 0, 4)
	{
		int ok = (s[i][x] == s[j][x] && s[i][x] == s[k][x]) || 
			(s[i][x] != s[j][x] && s[i][x] != s[k][x] && s[j][x] != s[k][x]);
		if(!ok)
			return false;
	}
	return true;
}
bool testcase()
{
	forn(i, 0, 12)
	{
		cin >> s[i];
	}
	if(!cin)
		return false;
	printf("CARDS: ");
	forn(i, 0, 12)
		printf(" %s", s[i]);
	printf("\n");
	printf("SETS:   ");
	int outputIndex = 1;
	forn(i, 0, n-2)
		forn(j, i+1, n-1)
			forn(k, j+1, n)
			{
				if(works(i, j, k))
				{
					printf("%d.  %s %s %s\n", outputIndex++, s[i], s[j], s[k]);
					printf("        ");
				}
			}
	if(outputIndex == 1)
		printf("*** None Found ***\n");
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}