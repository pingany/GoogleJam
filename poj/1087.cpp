#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
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

#define PlugID(s) ("p " + s)

#if 0//def LOCAL
#define MAXM 5
#define MAXN 4
#define MAXK 3
#else
#define MAXM 100
#define MAXN 100
#define MAXK 100
#endif
#define MAX_LEFT MAXM //m
#define MAX_RIGHT MAXN //n
#define MAX_NODES  (MAXM + MAXK + MAXN)
typedef std::vector<int> Node;
Node nodes[MAX_NODES +1];

bool visit[MAX_NODES+1];
int theMatchingLeft[MAX_NODES+1];
// depend on theMatchingLeft, visit
bool findAugment(Node* nodes, int start)
{
	for (std::vector<int>::iterator it = nodes[start].begin();
		 it != nodes[start].end(); ++it)
	{
		int i = *it;
		if(!visit[i])
		{
			visit[i] = true;
			if(theMatchingLeft[i] == -1 || findAugment(nodes, theMatchingLeft[i]))
			{
				theMatchingLeft[i] = start;
				return true;
			}
		}
	}
	return false;
}

int getMaxMatch(Node* nodes, int leftNodeStart, int leftNodeEnd)
{
	int ret = 0;
	memset(theMatchingLeft, 0xff, sizeof(theMatchingLeft));
	forn(i, leftNodeStart, leftNodeEnd)
	{
		if(!nodes[i].empty())
		{
			memset(visit, 0, sizeof(visit));
			if(findAugment(nodes, i))
				ret++;
		}
	}
	return ret;
}

int receptacleIdStart, receptacleIdEnd;
void findReceptacle(int start, Node&result, bool visit[])
{
	visit[start] = true;
	for (Node::iterator i = nodes[start].begin(); i != nodes[start].end(); ++i)
	{
		if(!visit[*i])
		{
			if(*i >= receptacleIdStart)
			{
				ASSERT(*i < receptacleIdEnd);
				result.push_back(*i);
				visit[*i] = true;
			}
			else
				findReceptacle(*i, result, visit);
		}
	}
}

struct Adapter
{
	string a, b;
};

int adapterIdEnd, adapterIdStart;
Adapter adapters[MAXK];
#define adapters(i)   adapters[i - adapterIdStart]
string nodeStrings[MAX_NODES+1];
bool testcase()
{
	int n, m, k;
	int plugIdStart, plugIdEnd;
	cin >> n;
	if(!cin)
		return false;
	string s;
	int id = 1;
	receptacleIdStart = id = MAXM+MAXK+1;
	forn(i, 0, n)
	{
		cin >> s;
		//ids[s] = id;
		nodeStrings[id] = s;
		//nodes[id].push_back(Edge(1, destNode));
		++id;
	}
	receptacleIdEnd = id;
	cin >> m;
	plugIdStart = id = 1;
	forn(i, 0, m)
	{
		cin >> s;
		cin >> s;
		// ids[PlugID(s)] = id;
		nodeStrings[id] = s;
		forn(i, receptacleIdStart, receptacleIdEnd)
		{
			if(s == nodeStrings[i])
				nodes[id].push_back(i);
		}
		//nodes[sourceNode].push_back(Edge(1, id));
		++id;
	}
	plugIdEnd = id;
	cin >> k;
	adapterIdStart = id;
	forn(i, 0, k)
	{
		Adapter &a = adapters(id);
		cin >> a.a >> a.b;
		++id;
	}
	adapterIdEnd = id;
	forn(i, adapterIdStart, adapterIdEnd)
	{
		Adapter &a = adapters(i);
		
		forn(plugId, plugIdStart, plugIdEnd)
		{
			if(nodeStrings[plugId] == a.a)
				nodes[plugId].push_back(i);
		}
		forn(j, i+1, adapterIdEnd)
		{
			if(adapters(i).a == adapters(j).b)
				nodes[j].push_back(i);
			if(adapters(i).b == adapters(j).a)
				nodes[i].push_back(j);
		}
		forn(receptacleId, receptacleIdStart, receptacleIdEnd)
			if(nodeStrings[receptacleId] == a.b)
				nodes[i].push_back(receptacleId);
	}

	ASSERT(plugIdStart == 1);
	Node newNodes[MAXM+1];
	bool visit[MAX_NODES+1];
	forn(i, plugIdStart, plugIdEnd)
	{
		memset(visit, 0, sizeof(visit));
		findReceptacle(i, newNodes[i], visit);
	}
	int maxMatch = getMaxMatch(newNodes, plugIdStart, plugIdEnd);
	cout << m - maxMatch;
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