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
typedef map<string, int> IDs;
IDs ids;

#define PlugID(s) (s.append(" p"))

bool testcase()
{
	cin >> n
	if(!cin)
		return false;
	string s;
	int id = 1;
	forn(i, 0, n)
	{
		cin >> s;
		ids[s] = id;
		nodes[id].push_back(Edge(1, destNode));
		++id;
	}
	cin >> m;
	forn(i, 0, m)
	{
		cin >> s;
		cin >> s;
		ids[PlugID(s)] = id;
		nodes[sourceNode].push_back(Edge(1, id));
		++id
	}
	cin >> k;
	string receptacle, plug;
	forn(i, 0, k)
	{
		cin >> receptacle >> plug;
		plug = PlugID(plug);
		int plugID = ids[plug];
		int receptacleID = ids[receptacle];
		ASSERT(plugID > 0 && receptacleID > 0);
		nodes[plugID].push_back(Edge(1, receptacleID));
	}
	int ret = 0;
	while(c = bfs())
		ret += c;
	cout << m - ret;
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