#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#define INLINE inline
#ifdef _MSC_VER
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

int p, q;
bool visited[27][27];
#define RUP(x, y)  ((x+y-1)/y)
struct Nb
{
	int x, y;
};
const Nb nbs[8] = {
	{-1, -2},
	{1, -2},
	{-2, -1},
	{2, -1},
	{-2, 1},
	{2, 1},
	{-1, 2},
	{1, 2}
};

struct Step
{
	int x, y;
};

Step steps[30];
int caseIndex = 1;
bool dfs(int ci, int cj, int step)
{
	steps[step].x = ci;
	steps[step].y = cj;
	if(step == p*q - 1)
	{
		for(int i = 0; i<= step; i++)
		{
			cout << (char)(steps[i].y + 'A') << steps[i].x + 1;
		}
		cout << "\n";
		return true;
	}
	visited[ci][cj] = 1;
	for (int i = 0; i < 8 ; i++)
	{
		int ni = ci + nbs[i].x;
		int nj = cj + nbs[i].y;
		if(ni >= 0 && ni < p && nj >=0 && nj < q)
		{
			if(!visited[ni][nj])
			{
				if(dfs(ni,nj, step+1))
					return true;
			}
		}
	}
	visited[ci][cj] = 0;
	return false;
}
bool solve()
{

	cout << "Scenario #" << (caseIndex++) << ":\n";
	if(p*q == 1)
	{
		cout << "A1" <<"\n";
		return true;
	}
	for(int j= 0; j < RUP(q, 2); j++)
		for(int i = 0; i <RUP(p, 2); i++)
		{
			memset(visited, 0, sizeof(visited));
			if(dfs(i, j, 0))
			{
				return true;
			}
		}
		cout << "impossible" << "\n";
		return false;
}
int main()
{
	ASSERT(freopen("in.txt", "r", stdin));
	int T;
	cin >> T;
	while(T--)
	{
		cin >> p >> q;
		solve();
		cout << "\n";
	}
}