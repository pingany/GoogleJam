#include <stdio.h>
#include <iostream>
using namespace std;

#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#define MAXN (10)
#define MAX_STATE (1ULL << (MAXN+1))

typedef unsigned __int64 uint64;
typedef uint64 State;
char paths[MAXN+1][2];
char visited[MAX_STATE+1][MAXN+1];
int N;

void solve()
{
	State state = 0;
	memset(visited, 0 , sizeof(visited));
	int x = 1;
	uint64 steps = 0;
	for(;;)
	{
		if (x == N)
		{
			printf("%d", steps);
			break;
		}
		if(visited[state][x])
		{
			printf("Infinity");
			break;
		}
		++steps;
		visited[state][x] = 1;
		state ^= 1ULL << x;
		int y = x;
		x = paths[x][(state & ( 1ULL << x)) ? 1 : 0];
		ASSERT(x > 0 && x <= N);
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T;
	cin >> T;
	int caseIndex = 0;
	while(T--)
	{
		int x, y ;
		cin >> N;
		memset(paths, 0, sizeof(paths));
		for(int i = 1 ;i < N; i++)
		{
			cin >> x >> y;
			paths[i][0] = y;
			paths[i][1] = x;
		}
		printf("Case #%d: ", ++caseIndex);
		solve();
		printf("\n");
	}
}