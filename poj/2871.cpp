#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <queue>
#include <algorithm>  
  
using namespace std;  
 
#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif
#define forn(i, a, b)  for(int i = (a); i < (b); i++)

int common1(const char*s, const char*d)
{
	int n = 0;
	while(*s && *d)
	{
		if(*s == *d)
			++n;
		++s;
		++d;
	}
	return n;
}
int common2(const char*s, const char*d)
{
	int n = 0;
	while(*d)
	{
		n = max(n, common1(s, d));
		++d;
	}
	return n;
}

int common(const char*s, const char*d)
{
	return max(common2(s, d), common2(d, s));
}
int N;
char ss[10][11];

typedef unsigned int State;
#define canput(state, x)  (!(state & (1 << x)))
#define put(state, x)   (state | (1 << x))

int f[1024+1][10][10];
int common_prepared[10][10];
#define common_prepared(i, j) common_prepared[i][j]
#define f(s, h, x) f[s][h][x]

int get(State s, int h, int x)
{
	if (h == N-1)
		return 0;
	int r = f(s, h, x);
	if (r != -1)
		return r;
	r = 0;
	forn(i, 0, N)
	{
		if(!canput(s, i))
			continue;
		ASSERT(x != i);
		State newstate = put(s, i);
		r = max(r, common_prepared(x, i) +  get(newstate, h+1, i));
	}
	return f(s, h, x) = r;
}
void solve()
{
	memset(f, 0xff, sizeof(f));
	memset(common_prepared, 0, sizeof(common_prepared));
	forn(i, 0, N)
		forn(j, 0, N)
		{
			if(i != j)
				common_prepared[i][j] = common(ss[i], ss[j]);
		}
	forn(i, 0, N)
		forn(j, 0, N)
		{
			ASSERT(common_prepared[i][j] == common_prepared[j][i]);
		}
	int r = 0;
	forn(x, 0, N)
		r = max(r, get(put(0, x), 0, x));
	cout << r << "\n";
}
int main()
{
	ASSERT(common1("123", "1") == 1);
	ASSERT(common1("123", "103") == 2);
	ASSERT(common1("1", "1") == 1);
	ASSERT(common1("2", "1") == 0);
	ASSERT(common1("", "1") == 0);
	ASSERT(common("abc", "bcd") == 2);
	ASSERT(common("bcd", "abc") == 2);

	ASSERT(freopen("in.txt", "r", stdin));
    while(cin >> N && N > 0)
    {
    	forn(i, 0, N)
    		cin >> ss[i];
    	solve();
    }
    return 0;
}