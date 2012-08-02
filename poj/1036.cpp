#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <queue>
#include <algorithm>  
  
using namespace std;  
 
#define INLINE inline
#ifdef _MSC_VER
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif
#define forn(i, a, b)  for(int i = (a); i < (b); i++)


#define MAXN 100
#define MAXT 30000
#define MAXK 102
int N, K, T;

struct Ganster
{
	int time;
	int pers;
	int state;
};
Ganster gs[MAXN + 1];
int f[MAXN+1][MAXK+1];
bool cmp_gs(const Ganster&g1, const Ganster&g2)
{
	return g1.time < g2.time;
}
void solve()
{
	memset(f, 0, sizeof(f));
	sort(gs, gs + N, cmp_gs);
	for(int i = N-1; i>=0; i--)
		for(int k = 0; k < K; k++)
	{
		int base_pers = (k == gs[i].state) ? gs[i].pers : 0;
		int maxp = base_pers;
		if(i + 1 < N)
		{
			int t = gs[i+1].time - gs[i].time;
			forn(j, max(k-t, 0), min(k+t, K-1)+1)
			{
				maxp = max(base_pers + f[i+1][j], maxp);
			}
		}
		f[i][k] = maxp;
	}
	int maxp = 0;
	forn(k, 0, min(0 + gs[0].time, K-1)+1)
	{
		maxp = max(maxp, f[0][k]);
	}
	cout << maxp << "\n";
}
int main()
{
	ASSERT(freopen("in.txt", "r", stdin));
	cin >> N >> K >>T;
	K++;
	forn(i, 0, N)
		cin >> gs[i].time;
	forn(i, 0, N)
		cin >> gs[i].pers;
	forn(i, 0, N)
		cin >> gs[i].state;
	solve();
	return 0;
} 