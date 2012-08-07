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
#define uint unsigned int
typedef unsigned long long LONG;

#ifdef LOCAL
#define MAXN 12
#else
#define MAXN 100000
#endif
int n;

struct Node
{
	int height;
	// The node's original position on list. (The node will node)
	int position;
	// The number of elements bigger than this one, in its left.
	int left;
};
Node nodes[MAXN];

bool node_cmp(const Node&n1, const Node&n2)
{
	return n1.height < n2.height;
}
void solveSlow()
{
	nodes[n].height = -1; // for while in solve()
	LONG maxf = 0;
	forn(i, 0, n)
	{
		int h = nodes[i].height;
		int j = i+1;
		while(nodes[j].height >= h)
			j++;
		maxf = max(maxf, (j-i)*(LONG)h);
	}
	printf("%d\n", maxf);
}

void solve()
{
	LONG maxf = 0;
	forn(i, 0, n)
	{
		nodes[i].position = i;
		nodes[i].left = 0;
	}
	// Always make nodes[0 ... nonDecreasingLength) is a non-decreasing list
	int nonDecreasingLength = 1;
	forn(i, 1, n)
	{
		if(nodes[i].height >= nodes[nonDecreasingLength-1].height)
		{
			nodes[nonDecreasingLength] = nodes[i];
			nonDecreasingLength++;
		}
		else
		{
			// find the first element whose height is bigger than nodes[i]'s
			int x = upper_bound(nodes, nodes+nonDecreasingLength, nodes[i], node_cmp) - nodes;
			// Essiential code begin
			forn(j, x, nonDecreasingLength)
			{
				maxf = max(maxf, (i - nodes[j].position + nodes[j].left) * (LONG)nodes[j].height);
			}
			nodes[i].left = i - nodes[x].position + nodes[x].left;
			// Essiential code end
			nodes[x] = nodes[i];
			nonDecreasingLength = x+1;
		}
	}
	forn(j, 0, nonDecreasingLength)
	{
		maxf = max(maxf, (n - nodes[j].position+ nodes[j].left) * (LONG)nodes[j].height);
	}
	cout << maxf << "\n";
}

bool testcase()
{
	scanf("%d", &n);
	if(!n)
		return false;
	forn(i, 0, n)
		scanf("%d", &nodes[i].height);
	solve();
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}