#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int

struct Edge
{
	int weight;
	int nodeIndex;
	Edge(): weight(0), nodeIndex(0) {}
	Edge(int n, int w): weight(w), nodeIndex(n){}
};
typedef std::vector<Edge> NodeAdjs;
struct Node
{
	int L;
	int index;
	int value; // for find shortest path
	NodeAdjs adjs;
};

#define MAX_VALUE 0x0fffffffL
#define MAXN 101
Node nodesBuffer[MAXN];
Node* nodes[MAXN];
int N, M;

bool node_cmp(const Node*n1, const Node*n2)
{
	return n1->value < n2->value;
}

bool visiting[MAXN];
int getMinCost(int startNode, int maxCost, int minLevel, int maxLevel)
{
	if(startNode == 1)
		return 0;
	int ret = maxCost;
	visiting[startNode] = true;
	Node&node = *nodes[startNode];
	for (NodeAdjs::iterator it = node.adjs.begin();
		 it != node.adjs.end(); ++it)
		{
			Edge &e = *it;
			if(!visiting[e.nodeIndex])
			{
				if(e.weight >= ret)
					continue;
				Node &adj = (*nodes[e.nodeIndex]);
				if(adj.L < minLevel || adj.L >maxLevel)
					continue;
				int maxL  = min(maxLevel, adj.L + M), minL = max(minLevel, adj.L - M);
				if(minL > maxL)
					continue;
				ret = min(ret, e.weight + getMinCost(adj.index, maxCost-e.weight,
					minL, maxL));
			}
		}
	visiting[startNode] = false;
	return ret;
}

// Wrong answer for 1062. but do Dijstla algorithm for the shortest path
int solve()
{
	(*nodes[0]).value = 0;
	forn(i, 1, N)
		(*nodes[i]).value = MAX_VALUE;
	Node* nodeMap[MAXN];
	forn(i, 0, N)
		nodeMap[i] = nodes[i];
	forn(i, 0, N)
	{
		Node& node = (*nodes[i]);
		if(node.index == 1)
		{
			return node.value;
		}
		for (NodeAdjs::iterator it = node.adjs.begin();
		 it != node.adjs.end(); ++it)
		{
			Edge &e = *it;
			Node &adj = (*nodeMap[e.nodeIndex]);
			adj.value = min(adj.value, node.value + e.weight);
		}
		sort(nodes+i+1, nodes+N, node_cmp);
		forn(j, i+1, N)
		{
			nodeMap[nodes[j]->index] = nodes[j];
		}
	}
	ASSERT(false);
	return 0;
}

bool testcase()
{
	int P, L, X, T, V;
	cin >> M >> N;
	if(!cin)
		return false;

	int maxCost = 0;
	N++; // include the node 0, himself
	forn(i, 0, N)
	{
		nodes[i] = &nodesBuffer[i];
		(*nodes[i]).adjs.clear();
		(*nodes[i]).index = i;
	}
	forn(i, 1, N)
	{
		cin >> P >> L >> X;
		(*nodes[0]).adjs.push_back(Edge(i, P));
		(*nodes[i]).L = L;
		forn(j, 0, X)
		{
			cin >> T >> V;
			(*nodes[T]).adjs.push_back(Edge(i, V));
		}
	}
	// remove edges by Level limitation
	forn(i, 1, N)
	{
		Node& node = (*nodes[i]);
		for (NodeAdjs::iterator it = node.adjs.begin();
		 it != node.adjs.end();)
		{
			if(abs(node.L - (*nodes[it->nodeIndex]).L) > M)
				it = node.adjs.erase(it);
			else 
				++it;
		}
	}
	// cout << solve();
	memset(visiting, 0,sizeof(visiting));
	cout << getMinCost(0, nodes[0]->adjs[0].weight, 0, MAX_INT);
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