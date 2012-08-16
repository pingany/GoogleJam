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


#define MAXK 64
int k;
char s[MAXK+1];
long long N;

unsigned long long getRepr(int index, bool positive)
{
	char* sp = s+index, *spEnd = s+k;
	char pChar, nChar;
	if(positive)
	{
		pChar = 'p'; nChar = 'n';
	}
	else
	{
		pChar = 'n'; nChar = 'p';
	}
	if(*sp == pChar)
		return (1ULL << index);
	unsigned long long ret = 0;
	while(sp < spEnd && *sp == nChar)
	{
			ret += (1ULL << index);
			++index;
			++sp;
	}
	if(sp == spEnd)
		return 0; // failed;
	ASSERT(*sp == pChar);
	ret += (1ULL << index);
	return ret;
}

void reverse(char*s, int len)
{
	char *p = s+len-1;
	while(s < p)
	{
		swap(*s, *p);
		++s;
		--p;
	}
}

unsigned long long add(unsigned long long a, unsigned long long b)
{
	int c = 0;
	char prev = 'p';
	unsigned long long ret = 0;
	int index = 0;
	while(a || b || c)
	{
		if(index >= k)
			return 0;
		if(s[index] != prev)
			c = -c;
		prev = s[index];
		int x = c + (a&1) + (b&1);
		if( x > 0)
		{	
			c = x / 2;
			if(x & 1)
				ret += (1ULL << index);
		}
		else if(x < 0)
		{
			ASSERT( x == -1);
			c = -1;
			ret += (1ULL << index);
		}
		a >>=1; 
		b >>=1;
		++index;
	}
	return ret;
}

char result[MAXK+1] = {0};
bool solve()
{
	bool positive = N >= 0;
	unsigned long long UN;
	if( N == -9223372036854775808LL)
	{
		UN = 9223372036854775808ULL;
	}
	else
		UN = positive ? N : -N;
	int index = 0;
	unsigned long long ret = 0;
	unsigned long long limit = (~0ULL) >> (64-k);
	reverse(s, k);
	while(UN)
	{
		if(UN&1)
		{
			unsigned long long x = getRepr(index, positive);
			if(!x)
				return false;
			ret = add(ret, x);
			if(!ret || ret > limit)
				return false;
		}
		++index;
		UN >>= 1;
	}
	memset(result, 0,sizeof(result));
	int i =0 ;
	while(ret)
	{
		if(ret & 1)
			result[i++] = '1';
		else 
			result[i++] = '0';
		ret >>= 1;
	}
	while(i < k)
		result[i++] = '0';
	result[k] = 0;
	reverse(result, k);
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	int T;
	cin >> T;
	while(T--)
	{
		cin >> k  >> s >> N;

		if(!cin)
			break;
		const char *re = result;
		if(!solve())
			re = "Impossible";
		cout << re << "\n";
#ifdef SPECIAL
		char ans[MAXK+1];
		cin >> ans;
		ASSERT(0 == strcmp(re, ans));
#endif
	}
	return 0;
}