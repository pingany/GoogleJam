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
int n;
void reverse(char *s, int len)
{
	char*p = s+len-1;
	while(s < p)
	{
		swap(*s, *p);
		--p;
		++s;
	}
}
char* get10(int x)
{
	static char c[11];
	if(x==0)
	{
		strcpy(c, "0");
		return c;
	}
	int i=0 ;
	while(x)
	{
		c[i++] = x % 10 + '0';
		x /=10 ;
	}
	c[i] = 0;
	reverse(c, i);
	return c;
}
int sum(const char*s, int len)
{
	int ret = 0;
	const char *p = s+len;
	while(s < p)
		ret += *s++ - '0';
	return ret;
}
int sum(const char*s)
{
	return sum(s, strlen(s));
}
bool isok(const char*s, int len)
{
	int l = len/2;
	return sum(s, l) == sum(s+len-l, l);
}
bool isok(const char*s)
{
	return isok(s, strlen(s));
}
void solve4()
{
#ifdef LOCAL
	ASSERT(!strcmp("0", get10(0)));
	ASSERT(!strcmp("1", get10(1)));
	ASSERT(!strcmp("10", get10(10)));
	ASSERT(!strcmp("999", get10(999)));

	ASSERT(sum("0", 0 )==0);
	ASSERT(sum("1", 0 )==0);
	ASSERT(sum("0", 1 )==0);
	ASSERT(sum("1", 1 )==1);
	ASSERT(sum("9999999", 7 )==63);

	forn(i, 0, 9)
	{
		ASSERT(isok(get10(i)));
		ASSERT(isok(get10(i*10+i)));
		ASSERT(isok(get10(i*100 +i*10+i)));
	}
	ASSERT(isok("101"));
	ASSERT(isok("090"));
	ASSERT(isok("000"));
	ASSERT(isok("111"));
	ASSERT(isok("909"));
	ASSERT(isok("919"));
#endif
	char s[11] = {0};
	int ret = 0;
	forn(i, '0', '9'+1)
	{
		s[0]=i;
		// if(isok(s,1))
		// 	ret ++;
		forn(j, '0', '9'+1)
		{
			s[1]=j;
			// if(isok(s,2))
			// 	ret ++;
			forn(k, '0', '9'+1)
			{
				s[2]=k;
				// if(isok(s,3))
				// 	ret ++;
				forn(l, '0', '9'+1)
				{
					s[3]=l;
					if(isok(s,4))
						ret ++;
				}
			}
		}
	}
	cout << ret;
}

const int pow10[11] = {1, 10, 100, 1000, 10000, 100000};
int f[100];
#define RUP(x, y) ((x+y-1)/(y))
void solve()
{
	int l = n/2;
	int maxsum = 0;
	memset(f, 0, sizeof(f));
	forn(x, 0, pow10[l])
	{
		int y = sum(get10(x));
		ASSERT(y < 100);
		f[y]++;
		maxsum = max(maxsum, y);
	}
	int ret = 0;
	int x = (n&1) ? 10 : 1;
	forn(i, 0, maxsum+1)
		ret+= f[i]*f[i]*x;
	cout << ret;
}

bool testcase()
{
	cin >> n;
	if(!cin)
		return false;
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