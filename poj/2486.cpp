#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
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
#define uint unsigned int

#if 0 //def LOCAL
#define MAXN 6
#define MAXK 3
#else
#define MAXN 100
#define MAXK 200
#endif
int N, K;
typedef std::vector<int> Node;
int apples[MAXN];
Node nodes[MAXN];
enum Type
{
	BACK,
	NO_BACK
};
#define INVALID_VALUE (-1)

int mergedSubTree[MAXN][MAXK+1][2];
int f[MAXN][MAXK+1][2];
// bool visited[MAXN];
int getImpl(int startNode, int k, Type type, int &ret);
inline int get(int startNode, int k, Type type)
{
	if(k < 0)
		return 0;
	else if(k == 0)
		return apples[startNode];
	ASSERT( k > 0 && k <= K);
	ASSERT(type == BACK || type == NO_BACK);
	ASSERT(startNode >=0 && startNode < N);
	int &ret = f[startNode][k][type];
	if(ret != INVALID_VALUE)
		return ret;
	return getImpl(startNode, k, type, ret);
}

#define left(k, type) mergedSubTree[startNode][k][type]

int tmp1[MAXN][MAXK+1][2];
#define tmp(k, type) tmp1[startNode][k][type]
#define right(k, type)  get(child, k, type)
int getImpl(int startNode, int k, Type type, int &ret)
{
	// ASSERT(!visited[startNode]);
	//visited[startNode] = true;
	int childSize = nodes[startNode].size();
	forn(x, 0, k+1)
	{
		left(x, BACK) = left(x, NO_BACK) = 0;
	}
	forn(childIndex, 0, childSize)
	{
		int child = nodes[startNode][childIndex];
		ASSERT(child >= 0 && child < N);
		// if(visited[child])
		// 	continue;
		forn(total, 1, k+1)
		{
			int maxBack = 0;
			int maxNoBack = 0;
			forn(x, 0, total+1)
			{
				maxBack = max(maxBack, left(x, BACK) + right(total-x-2, BACK));
				maxNoBack = max(maxNoBack, left(x, NO_BACK) + right(total-x-2, BACK));
				maxNoBack = max(maxNoBack, left(x, BACK) + right(total-x-1, NO_BACK));
			}
			tmp(total, BACK) = maxBack;
			tmp(total, NO_BACK) = maxNoBack;
		}
		forn(total, 1, k+1)
		{
			left(total, BACK) = tmp(total, BACK);
			left(total, NO_BACK) = tmp(total, NO_BACK);
		}
	}
	ret = left(k, type) + apples[startNode];
	//visited[startNode] = false;
	return ret;
}

// bool visited[MAXN];
void dfs(int startNode)
{
	Node &node = nodes[startNode];
	for (Node::iterator i = node.begin(); i != node.end(); ++i)
	{
		Node & child = nodes[*i];
		child.erase(find(child.begin(), child.end(), startNode));
	}
	for (Node::iterator i = node.begin(); i != node.end(); ++i)
	{
		dfs(*i);
	}
}

void remove_dup_egdes(int startNode)
{
	dfs(startNode);
}

bool testcase()
{
	int x, y;
	cin >> N >> K;
	if(!cin)
		return false;
	forn(i, 0, N)
	{
		nodes[i].clear();
		cin >> apples[i];
	}
	forn(i, 0, N-1)
	{
		cin >> x >> y;
		--x;
		--y;
		nodes[x].push_back(y);
		nodes[y].push_back(x);
	}
	memset(f, 0xff, sizeof(f));
	remove_dup_egdes(0);
	cout << get(0, K, NO_BACK);
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}