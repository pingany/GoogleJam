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
char board[10][16];
typedef char Board[10][16];
const int w = 15, h = 10;
int gameIndex = 1;
int moveIndex = 1;
int totalScore = 0;

struct Point
{
	short x, y;
	Point(short xx, short yy) : x(xx), y(yy){}
};

bool operator<(const Point&r1, const Point&r2)
{
	return r1.x == r2.x ? r1.y < r2.y : r1.x < r2.x;
}

const Point nbs[4] = {
	Point(0, -1),
	Point(0, 1),
	Point(-1, 0),
	Point(1, 0)
};

// find a sub conneted sub graph, with color 'color'
// Put the graph area in r
int dfs(Board&b, int x, int y, int color, Point&r)
{
	b[y][x] = 0;
	Point p = Point(x, y);
	if( p < r)
		r = p;
	int ret = 1;
	forn(i, 0, 4)
	{
		Point p = nbs[i];
		p.x += x;
		p.y += y;
		if(p.x >= 0 && p.x < w && p.y >= 0 && p.y < h && b[p.y][p.x] == color)
			ret += dfs(b, p.x, p.y, color, r);
	}
	return ret;
}

bool move()
{
	Board b;
	int maxPoints = -1;
	Point minRect = Point(w+1, h+1);
	int remainingPoints = 0;
	memcpy(b, board, sizeof(board));
	forn(x, 0, w)
		forn(y, 0, h)
		{
			if(b[y][x] != 0)
			{
				int color = b[y][x];
				Point r = Point(x, y);
				int points = dfs(b, x, y, color, r);
				ASSERT((r.x >= 0 && r.x < w && r.y >= 0 && r.y < h && board[r.y][r.x] == color));
				remainingPoints += points;
				if(points > maxPoints || (points == maxPoints && r < minRect))
				{
					maxPoints = points;
					minRect = r;
				}
			}
		}
	if(maxPoints >= 2)
	{
		char color = board[minRect.y][minRect.x];
		int score = (maxPoints-2) * (maxPoints-2);
		int x = minRect.x , y = minRect.y;
		totalScore += score;
		Point r = Point(x, y);
		int points = dfs(board, minRect.x, minRect.y, color, r);
		ASSERT(maxPoints == points);
		printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n",
			moveIndex++, minRect.y+1, minRect.x+1, maxPoints, color, score);
		return true;
	}
	else if(maxPoints == 1)
	{
		printf("Final score: %d, with %d balls remaining.\n", totalScore, remainingPoints);
	}
	else
	{
		printf("Final score: %d, with 0 balls remaining.\n", totalScore+1000);
	}
	return false;
}

bool empty_col(Board&b, int col)
{
	forn(row, 0, h)
		if(b[row][col])
			return false;
	return true;
}

void copy_col(Board&b, int fromCol, int toCol)
{
	forn(row, 0, h)
		b[row][toCol] = b[row][fromCol];
}

void clear_col(Board&b, int col)
{
	forn(row, 0, h)
		b[row][col] = 0;
}

void adjust()
{
	forn(col, 0, w)
	{
		int filledRow = 0;
		forn(row, 0, h)
		{
			if(board[row][col])
				board[filledRow++][col] = board[row][col];
		}
		forn(row, filledRow, h)
			board[row][col] = 0;
	}

	int filledCol = 0;
	forn(col, 0, w)
	{
		if(!empty_col(board, col))
			copy_col(board, col, filledCol++);
	}
	forn(col, filledCol, w)
		clear_col(board, col);
}

void solve()
{
	moveIndex = 1;
	totalScore = 0;
	printf("Game %d:\n\n", gameIndex++);
	while(move())
	{
		adjust();
	}

		printf("\n");
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	int T;
	cin >> T;
	while(T--)
	{
		forn2(i, h-1, -1)
			cin >> board[i];
		solve();
	}
	return 0;
}