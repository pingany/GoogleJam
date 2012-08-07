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
#ifdef LOCAL
#define MAXN 10
#else
#define MAXN 200
#endif
char s[MAXN+1];
unsigned char f[MAXN][MAXN];
#define INVALID_VALUE 0xff
#define f(i, j) f[i][j]
enum
{
	LIST = 4,
	ATOM = 2,
	SET = 1,
	LIST_ELEMENT = ATOM | SET, 
	SET_ELEMENT = SET | ATOM | LIST,
};

int findCommaIndex(int firstIndex, int lastIndex)
{
	ASSERT(firstIndex <= lastIndex);
	char *p = s + firstIndex;
	char *end = s+ lastIndex;
	while(p <= end)
	{
		if(*p == ',')
			return p-s;
		++p;
	}
	return -1;
}

int getPossibleType(int firstIndex, int lastIndex)
{
	ASSERT(firstIndex <= lastIndex);
	if(firstIndex == lastIndex)
		return ATOM;
	int ret = f(firstIndex, lastIndex);
	if(ret != INVALID_VALUE)
		return ret;
	ret = 0;
	// Check if a set
	if(s[firstIndex] == '{' && s[lastIndex] == '}')
	{
		if(lastIndex - firstIndex > 1)
		{
			int type = getPossibleType(firstIndex+1, lastIndex-1);
			if (type & SET_ELEMENT)
				ret |= SET;
		}
		else
		{
			ret |= SET;
		}
	}
	// Check if a list
	int comma = findCommaIndex(firstIndex+1, lastIndex);
	while(comma >= 0)
	{
		if ( comma + 1 > lastIndex)
			break; // be nothing
		int left = getPossibleType(firstIndex, comma-1);
		int right = getPossibleType(comma+1, lastIndex);
		if((left & LIST_ELEMENT) && (right & (ATOM|SET|LIST)))
		{
			ret |= LIST;
			break;
		}
		comma = findCommaIndex(comma+1, lastIndex);
	}
	return f(firstIndex, lastIndex) = ret;
}

char * outs[]=
{
	"No Set", "Set"
};
#define out(x) outs[x]
bool testcase()
{
	static int caseIndex = 1;
	cin >> s;
	int n = strlen(s);
	memset(f, 0xff, sizeof(f));
	cout << "Word #" << (caseIndex++) << ": " << out((getPossibleType(0, n-1) & SET) ? 1 : 0) << "\n";
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	int T;
	cin >> T;
	while(T--)
		testcase();
	return 0;
}