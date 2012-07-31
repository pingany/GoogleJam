#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#define INLINE inline
#ifdef _MSC_VER
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

char mazz[41][41];
int w,h;
struct Point
{
	int x, y;
};

Point operator+(Point p1, Point p2)
{
	Point ret = {p1.x + p2.x, p1.y + p2.y};
	return ret;
}

Point getPosition(char c)
{
	for(int i = 0; i < w; i++)
		for (int j = 0 ; j <h;j++)
		{
			if (mazz[j][i]==c)
			{
				Point p = {i, j};
				return p;
			}	
		}
		ASSERT(false);
}

/*
The coordinate:
mazz:
------->X
|
|
V
Y
*/
enum Direction
{
	LEFT, UP, RIGHT, DOWN
};

const Point nextPointOffset[4] = 
{
	{-1, 0}, {0, -1}, {1, 0}, {0, 1}
};

#define prevDirection(dir) ((Direction)((dir + 4 - 1)%4))
#define nextDirection(dir) ((Direction)((dir + 1)%4))

#define valid(ret) (ret.x >= 0 && ret.x < w \
	&& ret.y >= 0 && ret.y <h && mazz[ret.y][ret.x] != '#')

Point getNextByHand(Point p, Direction&currentDir, bool leftMost)
{
	Direction nextDir = leftMost ? 
		prevDirection(currentDir) : nextDirection(currentDir); 
	int n = 4;
	while(n--)
	{
		Point ret = p + nextPointOffset[nextDir];
		ASSERT(ret.x >= 0 && ret.x < w && ret.y >= 0 && ret.y <h);
		ASSERT(mazz[ret.y][ret.x] != 'S');
		if(mazz[ret.y][ret.x] != '#')
		{
			currentDir = nextDir;		
			return ret;
		}
		nextDir = leftMost ? 
			nextDirection(nextDir) : prevDirection(nextDir);
	}
	ASSERT(false);
}

void path(Point p, Direction dir, bool leftMost)
{
	int step = 0;
	Point next = getNextByHand(p, dir, leftMost);
	while(mazz[next.y][next.x] != 'E')
	{
		step++;
		next = getNextByHand(next, dir, leftMost);
	}
	/* include the start and end point, then +2 */
	cout << step+2 << " ";
}

struct PointEx
{
	Point p;
	int layer;
};

PointEx allPoints[41*41];
bool visitedSet[41][41];
#define visit(p) visitedSet[p.x][p.y] = 1
#define visited(p) visitedSet[p.x][p.y]

PointEx makePointEx(const Point&p, int layer)
{
	PointEx pex = {p, layer};
	return pex;
}

// bfs
void shortpath(Point sp)
{
	memset(visitedSet, 0, sizeof(visitedSet));
	int allPointIndex = 0;
	allPoints[allPointIndex++]= makePointEx(sp, 0);
	for(int i = 0; i < allPointIndex; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			Point next = allPoints[i].p + nextPointOffset[j];
			
			if(valid(next) && !visited(next))
			{
				if(mazz[next.y][next.x] == 'E')
				{
					cout << allPoints[i].layer + 2 << "\n";
					return;
				}
				visit(next);
				allPoints[allPointIndex++]= makePointEx(next, allPoints[i].layer+1);
			}
		}
	}
}

void solve()
{
	Direction dir;
	Point sp = getPosition('S');
	if(!sp.x)
		dir = RIGHT;
	else if(!sp.y)
		dir = DOWN;
	else if(sp.x == w - 1)
		dir = LEFT;
	else if(sp.y == h - 1)
		dir = UP;
	else
		ASSERT(false);
	path(sp, dir, true);
	path(sp, dir, false);
	shortpath(sp);
}

int main()
{
	ASSERT(freopen("in.txt", "r", stdin));
	int T;
	cin >> T;
	while(T--)
	{
		cin >> w >> h;
		for (int i = 0;i <h; i++)
			cin >> mazz[i];
		solve();
	}
}