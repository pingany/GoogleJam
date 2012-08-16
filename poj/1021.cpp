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

struct Point
{
	short x, y;
	Point(short xx, short yy) : x(xx), y(yy){}
};
#if 0 //def LOCAL
#define MAXW 2
#define MAXH 2
#else
#define MAXW 100
#define MAXH 100
#endif
int w, h;
typedef short Board[MAXW][MAXH];
Board board[2];
Point self(int x, int y, int w, int h) { return Point(x, y);}
Point r90(int x, int y, int w, int h) { return Point(y, w -1 -x);}
Point r180(int x, int y, int w, int h) { return Point(w -1 -x, h - 1 -y);}
Point r270(int x, int y, int w, int h) { return Point(h - 1 -y, x);}
Point hori(int x, int y, int w, int h) { return Point(w -1 -x, y);}
Point vert(int x, int y, int w, int h) { return Point(x, h - 1 -y);}
Point r90hori(int x, int y, int w, int h) { return Point(h - 1 -y, w -1 -x);}
Point r90vert(int x, int y, int w, int h) { return Point(y, x);}
typedef Point (*TransFunc)(int x, int y, int w, int h);
const int transFuncSize = 8;
const int transFuncsNeedSameSize = 4;
const TransFunc transFuncs[transFuncSize] = 
{
	self, hori, vert, r180, r90, r270, r90hori, r90vert
};

struct SubGraph
{
	short boardIndex;
	short mark;
	short x, y, w, h;
	short maxWH, minWH;
	bool matched;
	SubGraph(){}
	SubGraph(int bI, int f, int x1, int y1, int w1, int h1):
		boardIndex(bI), mark(f), x(x1), y(y1), w(w1), h(h1)
	{
		maxWH = max(w, h);
		minWH = min(w, h);
		matched = false;
	}

	bool hasChess(const Point&p) const
	{
		ASSERT(p.x < w && p.y < h);
		return mark == board[boardIndex][x + p.x][y + p.y];
	}

	bool sameSize(const SubGraph&g) const
	{
		return g.maxWH == maxWH && g.minWH == minWH;
	}

	bool operator<(const SubGraph&g) const
	{
		return maxWH != g.maxWH ? maxWH > g.maxWH : minWH > g.minWH;
	}
};

bool equal(const SubGraph&g1, const SubGraph&g2)
{
	for(int i = 0; i < transFuncSize;)
	{
		if(i < transFuncsNeedSameSize)
		{
			if(!(g1.w == g2.w && g1.h == g2.h))
			{
				i = transFuncsNeedSameSize;
				continue;
			}
		}
		else
		{
			if(!(g1.w == g2.h && g1.h == g2.w))
			{
				break;
			}
		}
		bool ok = true;
		TransFunc func = transFuncs[i];
		++i;
		forn(x, 0, g1.w)
			forn(y, 0, g1.h)
			{
				bool ret = g1.hasChess(Point(x, y)) == g2.hasChess(func(x, y, g1.w, g1.h));
				if(!ret)
				{
					ok = false;
					x = g1.w;
					break;
				}
			}
		if(ok)
			return true;
	}
	return false;
}

SubGraph subs[2][MAXW*MAXH];
int subsNum[2];

const Point nbs[4] = {
	Point(0, -1),
	Point(0, 1),
	Point(-1, 0),
	Point(1, 0)
};
struct Rect
{
	short x, y, x2, y2;
};

// find a sub conneted sub graph, mark all pixel with 'mark'(mark > 1). 
// Put the graph area in r
void dfs(Board&b, int x, int y, int mark, Rect&r)
{
	b[x][y] = mark;
	if( x < r.x)
		r.x = x;
	else if(x > r.x2)
		r.x2 = x;
	if( y < r.y)
		r.y = y;
	else if(y > r.y2)
		r.y2 = y;
	forn(i, 0, 4)
	{
		Point p = nbs[i];
		p.x += x;
		p.y += y;
		if(p.x >= 0 && p.x < w && p.y >= 0 && p.y < h && b[p.x][p.y] == 1)
			dfs(b, p.x, p.y, mark, r);
	}
}

void findSubs(int index)
{
	int &n = subsNum[index];
	Board &b = board[index];
	n = 0;
	int mark = 2;
	forn(x, 0, w)
		forn(y, 0, h)
		{
			if(b[x][y] == 1)
			{
				Rect r = {x, y, x, y};
				dfs(b, x, y, mark, r);
				subs[index][n++] = SubGraph(index, mark, r.x, r.y, r.x2-r.x+1, r.y2-r.y+1);
				++mark;
			}
		}
}

bool solve()
{
	forn(index, 0, 2)
	{
		findSubs(index);
	}
	if(subsNum[0] != subsNum[1])
		return false;
	int n = subsNum[0];
	sort(subs[0], subs[0]+n);
	sort(subs[1], subs[1]+n);
	forn(i, 0, n)
	{
		SubGraph &s = subs[0][i];
		ASSERT(!s.matched);
		// Find a sub graph who equal with it
		forn(j, 0, n)
		{
			if(subs[1][j].matched)
				continue;
			if(subs[1][j].sameSize(s))
			{
				if(equal(subs[1][j], s))
				{
					subs[1][j].matched = true;
					s.matched = true;
					break;
				}
			}
			else
			{
				// If all graph with same size don't match it, then we can't match it
				return false;
			}
		}
		if(!s.matched)
			return false;
	}
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	int T;
	int n, x, y;
	cin >> T;
	while(T--)
	{
		memset(board, 0, sizeof(board));
		cin >> w >> h >> n;
		int nn = n;
		while(nn--)
		{
			cin >> x >> y;
			board[0][x][y] = 1;
		}
		nn = n;
		while(nn--)
		{
			cin >> x >> y;
			board[1][x][y] = 1;
		}
		cout << (solve() ? "YES" : "NO") << "\n";
	}
	return 0;
}