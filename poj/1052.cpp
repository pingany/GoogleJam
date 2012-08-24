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
char cube[20][20][20];
char inputs[3][20][21], inputsBackup[3][20][21];
int n;
typedef char Cube[20][20][20];

char visitable[20][20][20];
struct Offset
{
	int x, y, z;
};
const Offset offsets[]=
{
	{0, 0, -1},
	{0, 0, 1},
	{0, -1, 0},
	{0, 1, 0},
	{-1, 0, 0},
	{1, 0, 0}
};
void dfs(int i, int j, int k)
{
	visitable[i][j][k] = 0;
	forn(x, 0, sizeof(offsets)/sizeof(offsets[0]))
	{
		Offset o = offsets[x];
		o.x += i;
		o.y += j;
		o.z += k;
		if(o.x >=0 && o.x < n && o.y >= 0 && o.y < n && o.z >= 0 &&o.z <n && visitable[o.x][o.y][o.z])
			dfs(o.x, o.y, o.z);
	}
}
bool connected()
{
	memcpy(visitable, cube, sizeof(visitable));
	forn(i, 0, n)
		forn(j, 0, n)
			forn(k, 0, n)
			{
				if(visitable[i][j][k])
				{
					dfs(i, j, k);
					goto stopDfs;
				}
			}
stopDfs:
	forn(i, 0, n)
		forn(j, 0, n)
			forn(k, 0, n)
			{
				if(visitable[i][j][k])
					return false;
			}
	return true;
}

bool solve1()
{
	memset(cube, 1, sizeof(cube));
	forn(m, 0, 3)
		forn(i, 0, n)
			forn(j, 0, n)
			{
				if(inputs[m][i][j] == '-')
				{
					forn(k, 0, n)
					{
						if(m==0)
							cube[i][j][k] = 0;
						else if(m==1)
							cube[i][k][j] = 0;
						else
							cube[k][i][j] = 0;
					}
				}
			}
	if(!connected())
		return false;
	forn(m, 0, 3)
		forn(i, 0, n)
			forn(j, 0, n)
			{
				if(inputs[m][i][j] == 'X')
				{
					// forn(k, 0, n)
					{
						if(m==0)
						{
							int ret = 0;
							forn(k, 0, n) 
								ret |= cube[i][j][k];
							if(ret == 0)
								return false;
						}
						else if(m==1)
						{
							int ret = 0;
							forn(k, 0, n) 
								ret |= cube[i][k][j];
							if(ret == 0)
								return false;
						}
						else
						{
							int ret = 0;
							forn(k, 0, n) 
								ret |= cube[k][i][j];
							if(ret == 0)
								return false;
						}
					}
				}
			}	
	return true;		

}
int caseIndex = 1;

struct Point
{
	short x, y;
	Point(){}
	Point(short xx, short yy) : x(xx), y(yy){}
	bool operator==(Point&p)
	{
		return x == p.x && y == p.y;
	}
};
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
const TransFunc transFuncs[transFuncSize] = 
{
	self, hori, vert, r180, r90, r270, r90hori, r90vert
};

void trans(const char in1[20][21], char out[20][21], TransFunc func)
{
	forn(i, 0, n)
		forn(j, 0, n)
		{
			Point p = func(i, j, n, n);
			out[p.x][p.y] = in1[i][j];
		}
}

void test()
{
	Point p;
	forn(x, 0, n)
		forn(y, 0, n)
		{
			Point p270 = r270(x, y, n, n);
			Point  p180 = r270(p270.x, p270.y, n, n);
			Point  p90 = r270(p180.x, p180.y, n, n);
			Point self = r270(p90.x, p90.y, n, n);
			ASSERT(r180(x, y, n, n) == p180);
			ASSERT(r90(x, y, n, n) == p90);
			ASSERT(Point(x, y) == self);

			ASSERT(vert(p270.x, p270.y, n,n ) == r90hori(x, y, n, n));
			ASSERT(vert(p180.x, p180.y, n,n) == hori(x, y, n, n));
			ASSERT(vert(p90.x, p90.y, n, n) == r90vert(x, y, n, n));
		}
}

bool solve()
{
#ifdef LOCAL
	test();
#endif
	memcpy(inputsBackup, inputs, sizeof(inputs));
	// trans(inputsBackup[0], inputs[0], hori);
	// trans(inputsBackup[1], inputs[1], r180);
	// trans(inputsBackup[2], inputs[2], hori);
	// return solve1();
	forn(i, 0, transFuncSize)
	{
		trans(inputsBackup[0], inputs[0], transFuncs[i]);
		forn(j, 0, transFuncSize)
		{
			trans(inputsBackup[1], inputs[1], transFuncs[j]);
			forn(k, 0, transFuncSize)
			{
				trans(inputsBackup[2], inputs[2], transFuncs[k]);
				if(solve1())
					return true;
			}
		}
	}
	return false;
}
bool testcase()
{
	cin >> n;
	if(!n)
		return false;
	forn(i, 0, 3)
		forn(j, 0, n)
			cin >> inputs[i][j];

	cout << "Data set " << (caseIndex++) << ": ";
	cout << (solve() ? "Valid set of patterns\n" : "Impossible combination\n");
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}