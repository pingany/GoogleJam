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
#define MAXN 100
#define MAXM 100
struct Point
{
	int x, y;
};
Point routes[MAXN], places[MAXM];
inline int pow2(int x) { return x*x;}
float dis(const Point&p1, const Point&p2)
{
	return (float)sqrt((float)(pow2(p1.x - p2.x) + pow2(p1.y - p2.y)));
}
#define PlaceID(j) (j+n+2)
struct Bridge
{
	int i, j; //  1 <= i < n, PlaceID(0) <= j < PlaceID(m)
};

std::vector<Bridge> bridges;

bool testcase()
{
	cin >> n >> m;
	if(!cin)
		return false;
	int sourceNode = 0, destNode = n+1;
	forn(i, 0, n)
	{
		cin >> routes[i].x >> routes[i].y;
	}
	forn(i, 0, m)
	{
		nodes[PlaceID(i)].push_back(Edge(1, destNode));
		cin >> places[i].x >> places[i].y;
	}
	forn(i, 1, n)
	{
		nodes[sourceNode].push_back(Edge(1, i));
		float c = dis(routes[i-1], routes[i]);
		forn(j, 0, m)
		{
			float a = dis(routes[i-1], places[j]);
			float b = dis(routes[i], places[j]);
			if(a + b <= 2*c + 1e-9)
			{
				nodes[i].push_back(Edge(1, PlaceID(j)));
			}
		}
	}
	int ret = 0, c;
	Bridge bridge;
	while(c = bfs(bridge) )
	{
		ret += c;
		bridges.push_back(bridge);
	}
	
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
#ifdef LOCAL
	while(testcase())
		cout << "\n";
#else
	testcase();
#endif
	return 0;
}