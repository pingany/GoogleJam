#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
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
// People currently in the room
set<int> peoplesIn;

// the candidate names for a userID
map<int, set<int> > candidateNames;

#define MAXN 20
// Index of userIDString and name
map<string, int> userIndexs, nameIndexs;
// Save the userIdString and names from indexes
string names[MAXN+1], userNames[MAXN+1];

// the matched nameID of userID
int result[MAXN+1];
// indicate if a name matched
bool nameMatched[MAXN+1];
// the number of users
int n;

// the graph, converted from candidateNames
std::vector<int> nodes[MAXN+1];

#define INVALID_VALUE (-1)

struct Output
{
	string name;
	string other;
	Output(){}
	Output(const string&n, const string&o): name(n), other(o){}
	bool operator<(const Output&another)
	{
		return name < another.name;
	}
};

void interect(set<int>&a, const set<int>&b)
{
	for (std::set<int>::iterator i = a.begin(); i != a.end();)
	{
		if(b.find(*i) == b.end())
			i = a.erase(i);
		else 
			++i;
	}
}

// When do a match in graph, uid must match nameid, then do the match, and remove all related edges
void fixPair(int uid, int nameid)
{
	result[uid] = nameid;
	nameMatched[nameid] = true;
	nodes[uid].clear();
	forn(i, 1, n+1)
	{
		if(!nodes[i].empty())
		{
			std::vector<int>::iterator it = find(nodes[i].begin(), nodes[i].end(), nameid);
			if (it != nodes[i].end())
			{
				nodes[i].erase(it);
				if(nodes[i].size() == 1)
					fixPair(i, *nodes[i].begin());
			}
		}
	}
}

// Get the max match for a di-graph, XiongYaLi algorithm
bool visit[MAXN+1];
int theMatchingLeft[MAXN+1];
// depend on theMatchingLeft, visit
bool findAugment(int start)
{
	for (std::vector<int>::iterator it = nodes[start].begin();
		 it != nodes[start].end(); ++it)
	{
		int i = *it;
		if(!visit[i])
		{
			visit[i] = true;
			if(theMatchingLeft[i] == 0 || findAugment(theMatchingLeft[i]))
			{
				theMatchingLeft[i] = start;
				return true;
			}
		}
	}
	return false;
}

int getMaxMatch()
{
	int ret = 0;
	memset(theMatchingLeft, 0, sizeof(theMatchingLeft));
	forn(i, 1, n+1)
	{
		if(!nodes[i].empty())
		{
			memset(visit, 0, sizeof(visit));
			if(findAugment(i))
				ret++;
		}
	}
	return ret;
}

bool testcase()
{
	cin >> n;
	if(!cin)
		return false;
	peoplesIn.clear();
	candidateNames.clear();
	userIndexs.clear();
	nameIndexs.clear();
	string userIdString, name;
	forn(i, 1, n+1)
	{
		cin >> userIdString;
		userIndexs[userIdString] = i;
		userNames[i] = userIdString;
	}
	int uniqNameId = 1;
	memset(result, 0xff, sizeof(result));
	memset(nameMatched, 0,sizeof(nameMatched));
	forn(i, 1, n+1)
	{
		set<int>&candidates = candidateNames[i];
		forn(j, 1, n+1)
			candidates.insert(j);
	}
	char action;
	while(cin >> action, action != 'Q')
	{
		if(action == 'M')
		{
			cin >> userIdString;
			int uid = userIndexs[userIdString];
			set<int>&candidates = candidateNames[uid];
			interect(candidates, peoplesIn);
		}
		else
		{
			cin >> name;
			int& nameid = nameIndexs[name];
			if(!nameid)
			{
				nameid = uniqNameId++;
				names[nameid] = name;
			}
			if(action == 'E')
				peoplesIn.insert(nameid);
			else
				peoplesIn.erase(nameid);
		}
	}

	//// Convert to a Graph
	forn(i, 1, n+1)
		nodes[i].clear();
	for (std::map<int, set<int> >::iterator i = candidateNames.begin();
					 i != candidateNames.end(); ++i)
	{
		set<int>& condidates = i->second;
		for (std::set<int>::iterator j = condidates.begin(); j != condidates.end(); ++j)
		{
			nodes[i->first].push_back(*j);
		}
	}

	// Get the perfect match of this graph
	forn(i, 1, n+1)
	{
		if(nodes[i].size() == 1)
			fixPair(i, *nodes[i].begin());
	}
	int maxMatch = getMaxMatch();
	forn(i, 1, n+1)
	{
		vector<int> &node = nodes[i];
		for (std::vector<int>::iterator j = node.begin(); j != node.end(); ++j)
		{
			int x = *j;
			j = node.erase(j);
			int currentMaxMatch = getMaxMatch();
			if(currentMaxMatch < maxMatch)
			{
				j = node.insert(j, x);
				fixPair(i, x);
				maxMatch = getMaxMatch();
				break;
			}
			j = node.insert(j, x);
		}
	}
	//// Output
	std::vector<Output> outputs;
	forn(i, 1, n+1)
	{
		if(result[i] != INVALID_VALUE)
		{
			outputs.push_back(Output(names[result[i]], userNames[i]));
		}
	}
	forn(i, 1, n+1)
	{
		if(!nameMatched[i])
		{
			outputs.push_back(Output(names[i], "???"));
		}
	}
	sort(outputs.begin(), outputs.end());
	for (std::vector<Output>::iterator i = outputs.begin(); i != outputs.end(); ++i)
	{
		cout << i->name << ":" << i->other << "\n";
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