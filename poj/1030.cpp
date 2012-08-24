#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
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
enum RealPos
{
	NOT_DETERMINED = 0,
	CONFLICT = -1
};
struct Team
{
	int pos[2];
	bool both;
	int realPos;
};

Team ts[101];

struct Contest
{
	int n;
	int teamIndexes[101];
};

Contest cs[2];
bool resultLessThan(int i, int j)
{
	int x = ts[i].pos[0] - ts[j].pos[0] + ts[i].pos[1] - ts[j].pos[1];
	return x < 0;
}

bool sortResult(int i, int j)
{
	if(ts[i].realPos == ts[j].realPos)
	{
		if(ts[i].both || ts[j].both)
			return i < j;
		else
		{
			int posi = ts[i].pos[0] + ts[i].pos[1];
			int posj = ts[j].pos[0] + ts[j].pos[1];
			if(posi == posj)
				return i < j;
			else 
				return posi < posj;
		}
	}
	else
		return ts[i].realPos < ts[j].realPos;
}

bool realPosLessThan(int i, int j)
{
	if(ts[i].realPos == ts[j].realPos)
	{
		if(ts[i].both || ts[j].both)
			return false;
		else
		{
			int posi = ts[i].pos[0] + ts[i].pos[1];
			int posj = ts[j].pos[0] + ts[j].pos[1];
			if(posi == posj)
				return false;
			else 
				return posi < posj;
		}
	}
	else
		return ts[i].realPos < ts[j].realPos;
}

bool testcase()
{
	memset(ts, 0, sizeof(ts));
	memset(cs, 0, sizeof(cs));
	string line;
	int nteam = 0;
	forn(i, 0, 2)
	{
		int pos = 1;
		int team = 0;
		int n;
		cin >> n;
		getline(cin, line);
		if(!cin)
			return false;
		while(n--)
		{
			getline(cin, line);
			stringstream lines(line);
			int x;
			while(lines >> x)
			{
				ts[x].pos[i] = pos;
				nteam = max(nteam, x);
				cs[i].teamIndexes[team++] = x;
			}
			pos = team+1;
		}
		cs[i].n = team;
	}
	int resultNum = 0;
	int result[100];
	forn(i, 1, nteam+1)
	{
		if(ts[i].pos[0] && ts[i].pos[1])
		{
			ts[i].both = true;
			result[resultNum++] = i;
		}
	}

	sort(result, result+resultNum, resultLessThan);
	int realPos = 1;
	if(resultNum > 0)
		ts[result[0]].realPos = realPos*1000;
	forn(i, 1, resultNum)
	{
		if(resultLessThan(result[i-1], result[i]))
		{
			realPos++;
		}
		ts[result[i]].realPos = realPos*1000;
	}
	forn(c, 0, 2)
	{
		forn(ti, 0, cs[c].n)
		{
			Team& t = ts[cs[c].teamIndexes[ti]];
			if(!(t.both))
			{
				int pos = NOT_DETERMINED;
				forn(i, 0, cs[c].n)
				{
					Team &other = ts[cs[c].teamIndexes[i]];
					if(i != ti && other.both && other.pos[c] == t.pos[c])
					{
						if(pos == NOT_DETERMINED)
							pos = other.realPos;
						else if(pos != other.realPos)
						{
							pos = CONFLICT;
							break;
						}
					}
				}
				if(pos == NOT_DETERMINED)
				{
					int maxPrev = -1, minNext = MAX_INT;
					forn(i, 0, ti)
					{
						Team &other = ts[cs[c].teamIndexes[i]];
						if(other.both)
						{
							maxPrev = max(maxPrev, other.realPos);
						}
					}
					forn(i, ti+1, cs[c].n)
					{
						Team &other = ts[cs[c].teamIndexes[i]];
						if(other.both)
						{
							minNext = min(minNext, other.realPos);
						}	
					}
					if(maxPrev >= minNext)
						pos = CONFLICT;
					else
					{
						ASSERT(maxPrev+1 < minNext);
						pos = maxPrev +1;
					}
				}
				t.realPos = pos;
				if(pos != CONFLICT)
				{
					result[resultNum++] = cs[c].teamIndexes[ti];
				}
			}
		}		
	}
	sort(result, result+resultNum, sortResult);
	cout << result[0];
	bool first = false;
	forn(i, 1, resultNum)
	{
		if(realPosLessThan(result[i-1], result[i]))
		{
			cout << "\n";
			first = true;
		}
		if(first)
			first = false;
		else
			cout << " ";
		cout << result[i];
	}
	cout << "\n";

	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
#ifdef LOCAL
	while(testcase());
#else
	testcase();
#endif
	return 0;
}