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

#ifdef WIN32
typedef unsigned __int64 u64;
#else
typedef unsigned long long u64;
#endif

u64 f[31][2];
#define f(i, j)  f[i][j]
u64 get(int n, int y)
{
	if(f(n, y) != -1)
		return f(n, y);
	u64 r;
	if(y ==0)
		r = 3 * get(n-2, 0) + 2* get(n-2, 1);
	else
		r = get(n-2, 0) + get(n-2, 1); 
	ASSERT(f(n, y) >= f(n-2, 0) && f(n, y) >= f(n-2, 1));
	return f(n, y) = r;
}

int main()
{
	ASSERT(freopen("in.txt", "r", stdin));
	int N;
	memset(f, 0xff, sizeof(f));
	f(0, 0) = 1;
	f(0, 1) = 0;
	f(1, 0) = 0;
	f(1, 1) = 0;
	ASSERT(get(2, 0) == 3);
	ASSERT(get(2, 1) == 1);
	while( cin >> N && N >= 0)
		cout << get(N, 0) << "\n";
	return 0;
}