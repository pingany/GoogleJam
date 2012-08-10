#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
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
const char * out[] = {
	"Sorted sequence determined after %d relations: %s.",
	"Inconsistency found after %d relations.",
	"Sorted sequence cannot be determined."
};

int n;
struct Node
{
	std::vector<char> adjs;
	int inDegree;
};

#define MAXN 26
Node nodes[MAXN];

#define getNodeIndex(a) (a - 'A')
#define getAscii(i)  (i + 'A')
#define getNode(a)  nodes[getNodeIndex(a)]

enum SortResult
{
	SORTED,
	INCONSISTENCY,
	NOT_DETERMINED
};

struct SortNode
{
	short inDegree;
	short index;
};

char sortedList[30];

bool visited[MAXN];
bool visiting[MAXN];
bool dfs(int startNode)
{
	visited[startNode] = true;
	visiting[startNode] = true;
	bool ret = false;
	for (std::vector<char>::iterator i = nodes[startNode].adjs.begin();
	 i != nodes[startNode].adjs.end(); ++i)
	{
		if(visited[*i])
		{
			// We don't init visiting in the begining because we always check visited false
			// if visited, then visiting is always valid
			if(visiting[*i])
			{
				ret = true;
				break;
			}
			else
			{
				continue;
			}
		}
		if(dfs(*i))
		{
			ret = true;
			break;
		}
	}
	visiting[startNode] = false;
	return ret;
}

// haveCircle, for digraph
bool haveCircle()
{
	bool totallyVisited[MAXN];
	memset(totallyVisited, 0, sizeof(totallyVisited));
	forn(i, 0, n)
	{
		if(!totallyVisited[i])
		{
			memset(visited, 0, sizeof(visited));
			if(dfs(i))
				return true;
			forn(j, 0, n)
				totallyVisited[j] |= visited[j];
		}
	}
	return false;
}

// Topologically sort
SortResult trySort()
{
	list<SortNode> snodes;
	list<SortNode>::iterator nodeMap[MAXN];
	int sortedListLength = 0;
	forn(i, 0, n)
	{
		SortNode node;
		node.inDegree = nodes[i].inDegree;
		node.index = i;
		if(node.inDegree == 0)
		{
			snodes.push_front(node);
			nodeMap[i] = snodes.begin();
		}
		else
		{
			snodes.push_back(node);
			nodeMap[i] = --snodes.end();
		}
	}
	if(haveCircle())
		return INCONSISTENCY;
	bool notDetermined = false;
	while(snodes.size() > 1)
	{
		if(snodes.begin()->inDegree != 0)
			return INCONSISTENCY;
		//if(snodes.size() > 1)
		{
			// Two node with inDegree == 0 means sorting not determined
			// if(!notDetermined && (++snodes.begin())->inDegree == 0)
			// {
			// 	notDetermined = true;
			// }
			if((++snodes.begin())->inDegree == 0)
				return NOT_DETERMINED;
			int index = snodes.begin()->index;
			sortedList[sortedListLength++] = getAscii(index);
			snodes.erase(snodes.begin());
			for (std::vector<char>::iterator i = nodes[index].adjs.begin(); 
				i != nodes[index].adjs.end(); ++i)
			{
				list<SortNode>::iterator adjNode = nodeMap[*i];
				adjNode->inDegree --;
				if(adjNode->inDegree == 0)
				{
					snodes.push_front(*adjNode);
					snodes.erase(adjNode);
					nodeMap[*i] = snodes.begin();
				}
			}
		}
	}
	if(notDetermined)
		return NOT_DETERMINED;
	ASSERT(snodes.size() == 1);
	sortedList[sortedListLength++] = getAscii(snodes.begin()->index);
	sortedList[sortedListLength] = 0;
	return SORTED;
}

void skip(int lines)
{
	char s[10];
	while(lines--)
		cin >> s;
}
bool testcase()
{
	char a, b, flag;
	int m;
	cin >> n >> m;
	if(!n)
		return false;
	forn(i, 0, n)
	{
		nodes[i].inDegree = 0;
		nodes[i].adjs.clear();
	}
	SortResult result = NOT_DETERMINED; // for m == 0
	forn(e, 0, m)
	{
		cin >> a >> flag >> b;
		getNode(b).inDegree++;
		getNode(a).adjs.push_back(getNodeIndex(b));
		result = trySort();
		if(result == SORTED)
		{
			skip(m-e-1);
			printf(out[SORTED], e+1, sortedList);
			break;
		}
		else if(result == INCONSISTENCY)
		{
			skip(m-e-1);
			printf(out[INCONSISTENCY], e+1);
			break;
		}
	}
	if (result == NOT_DETERMINED)
	{
		printf(out[NOT_DETERMINED]);
	}
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}