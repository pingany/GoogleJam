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
const char* out[]=
{
	"The last domino falls after %.1f seconds, at key domino %d.\n",
	"The last domino falls after %.1f seconds, between key dominoes %d and %d.\n"
};

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
	int index;
	int value; // for find shortest path
	NodeAdjs adjs;
};

#define MAX_VALUE 0x0fffffffL
#define MAXN 501
Node nodesBuffer[MAXN];
Node* nodes[MAXN];

int n, m;
static int caseIndex = 1;

bool node_cmp(const Node*n1, const Node*n2)
{
	return n1->value < n2->value;
}

bool node_cmp_for_heap(const Node*n1, const Node*n2)
{
	return n1->value > n2->value;
}

// do Dijstla algorithm for the shortest path

// template<typename T>
void moveSmallestFirst(Node* * begin, Node* * end,  bool (*node_less)(const Node* n1, const Node* n2))
{
	if(begin == end || begin+1 == end)
		return; // size is 0 or 1
	Node* * minValuePointer = begin;
	Node*  minValue = *begin;
	for(Node* *p = begin+1; p != end; ++p)
	{
		if(node_less(*p, minValue))
		{
			minValuePointer = p;
			minValue = *p;
		}
	}
	if(minValuePointer == begin)
		return;
	for(Node* *p = minValuePointer; p != begin; --p)
	{
		*p = *(p-1);
	}
	*begin = minValue;
}

int solve()
{
	(*nodes[0]).value = 0;
	Node* nodeMap[MAXN];
	char visited[MAXN] = {0};
	forn(i, 0, n)
		nodeMap[i] = nodes[i];
	int maxValue = -1;
	int maxNodeIndex;
	forn(i, 0, n)
	{
		Node& node = (*nodes[i]);
		visited[node.index] = 1;
		if(node.value > maxValue)
		{
			maxValue = node.value;
			maxNodeIndex = node.index;
		}
		for (NodeAdjs::iterator it = node.adjs.begin();
		 it != node.adjs.end(); ++it)
		{
			Edge &e = *it;
			if(visited[e.nodeIndex])
				continue;
			Node &adj = (*nodeMap[e.nodeIndex]);
			adj.value = min(adj.value, node.value + e.weight);
		}
		// Following code all works here. For differents on time/space, see
		// http://poj.org/status?problem_id=1135&user_id=yipingan&result=&language=
		//make_heap(nodes+i+1, nodes+n, node_cmp_for_heap); // RunID: 10648517
		// sort(nodes+i+1, nodes+n, node_cmp); // 10648436
		moveSmallestFirst(nodes+i+1, nodes+n, node_cmp); // 10641083
		forn(j, i+1, n)
		{
			nodeMap[nodes[j]->index] = nodes[j];
		}
	}
	Node& node = *nodeMap[maxNodeIndex];
	float maxEdgeValue = (float)0;
	int edgeX, edgeY;
	forn(i, 0, n)
	{
		Node& node = (*nodes[i]);
		for (NodeAdjs::iterator it = node.adjs.begin();
		 it != node.adjs.end(); ++it)
		{
			Edge &e = *it;
			Node &adj = (*nodeMap[e.nodeIndex]);
			int big = node.value;
			int small = adj.value;
			float edgeValue = (e.weight + big + small)/2.0;
			if(edgeValue > maxEdgeValue)
			{
				maxEdgeValue = edgeValue;
				edgeX = adj.index;
				edgeY = node.index;
			}
		}
	}
	if(maxEdgeValue > (float)maxValue)
	{
		if(edgeX > edgeY)
			swap(edgeX, edgeY);
		printf(out[1], maxEdgeValue, edgeX+1, edgeY+1);
	}
	else
	{
		printf(out[0], (float)maxValue, maxNodeIndex+1);
	}

	return 0;
}

bool testcase()
{
	int x, y, path;
	cin >> n >> m;
	if(!n)
		return false;
	forn(i, 0, n)
	{
		nodes[i] = &nodesBuffer[i];
		nodes[i]->adjs.clear();
		nodes[i]->index = i;
		nodes[i]->value = MAX_VALUE;
	}
	while(m--)
	{
		cin >> x >> y >> path;
		nodes[x-1]->adjs.push_back(Edge(y-1, path));
		nodes[y-1]->adjs.push_back(Edge(x-1, path));
	}
	printf("System #%d\n", caseIndex ++);
	solve();
	return true;
}

int main()
{
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}