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

char s[101][101];
char board[101][101];
char inputs[27];
int rows, cols;

struct Point
{
	short row, col;
};

enum Direction
{
	UNKNOWN, UP,DOWN, RIGHT, LEFT
};
const char sp[] = {0, '|', '|', '-', '-'};

const Point ps[]=
{
	{0,0 },
	{-1, 0},
	{1, 0},
	{0, 1},
	{0, -1}
};

inline bool isID(char c)
{
	switch(c)
	{
		case 'o':
		case '>':
		case ')':
			return true;
		default:
		{
			if(c >= 'A' && c <='Z')
				return true;
		}
	}
	return false;
}
void gotoNextID(int& row, int &col)
{
	
	for(;;)
	{
		forn(nextDirection, UP, LEFT+1)
		{
			// if(!isOpp(nextDirection, d))
			{
				Point p = ps[nextDirection];
				p.row += row;
				p.col += col;
				if(p.row >=0 && p.col >=0 && p.row < rows && p.col < cols )
				{
					if( s[p.row][p.col] == sp[nextDirection])
					{
						s[row][col] = ' ';
						row = p.row;
						col = p.col;
						break;
					}
					else if(s[p.row][p.col] == '+')
					{
						if(((nextDirection == UP || nextDirection == DOWN) && s[row][col] != '-')
						|| ((nextDirection == LEFT || nextDirection == RIGHT) && s[row][col] != '|'))
						{
							s[row][col] = ' ';
							row = p.row;
							col = p.col;
							break;
						}
					}
					else if (isID(s[p.row][p.col]))
					{
						s[row][col] = ' ';
						row = p.row;
						col = p.col;
						return;
					}
				}
			}
		}
	}
}

int solve(int row, int col)
{
 	gotoNextID(row, col);
 	char c = s[row][col];
 	s[row][col] = ' '; // clean current position, we won't get back when find path
 	if(c == 'o')
 		return !solve(row, col);
 	else if(c == '>')
 		return solve(row-1, col-2) || solve(row+1, col-2);
 	else if(c == ')')
 		return solve(row-1, col-2) && solve(row+1, col-2);
 	else
 	{
 		ASSERT(c >='A' && c <= 'Z');
 		return inputs[c - 'A'] - '0';
 	}
}

Point findQuestionMark()
{
	forn(i, 0, rows)
		forn(j, 0, cols)
		{
			if(s[i][j] == '?')
			{
				Point p = {i, j};
				return p;
			}
		}
		ASSERT(false);
}

void solve()
{
	Point start = findQuestionMark();
	cout << solve(start.row, start.col) << "\n";
}
bool first = true;
bool testcase()
{
	memset(s, 0, sizeof(s));
	int i = 0;
	cols = -1;
	while(cin.getline(s[i], sizeof(s[i])) && s[i][0] != '*')
	{
		cols = max(cols, (int)strlen(s[i]));
		++i;
	}
	
	if(!cin)
		return false;
	if(first)
		first = false;
	else
		cout << "\n";
	s[i][0] = 0;//handle *
	rows = i;
	memcpy(board, s, sizeof(s));
	while(cin >> inputs, inputs[0] != '*')
	{
		solve();
		memcpy(s, board, sizeof(board));
	}

	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}