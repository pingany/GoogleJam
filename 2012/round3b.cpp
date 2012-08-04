#include <stdio.h>
#include <memory.h>
#include <iostream>

using namespace std;

#define INLINE inline
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)

#define MAXS 3001
char board[MAXS*2][MAXS*2];
char vis[MAXS*2][MAXS*2];
int S;
int edgesVisited[7];
int corners, edges, ring;
int stopVisiting = 0;
void init()
{
	memset(board, 0, sizeof(board));
}

#define filled(x, y)   board[x][y]
#define visited(x, y)  vis[x][y]

typedef void (*VisitFunc)(int x, int y);

INLINE bool valid(int x, int y)
{
	return x > 0 && x <= S*2-1 && y > 0 && y <= S*2-1;
}

INLINE bool isCorner(int x, int y)
{
	return (x == 1 || x == S || x == 2*S-1) 
	&& (y == 1 || y == S || y == 2*S-1);
}

INLINE int getEdge(int x, int y)
{
	if (x == 1)
		return 1;
	else if(x == S*2-1)
		return 2;
	else if(y == 1)
		return 3;
	else if(y == S*2-1)
		return 4;
	else if(x - y == S -1)
		return 5;
	else if(x - y == 1 - S)
		return 6;
	else
		return 0;
}

#define CORNER 1
#define EDGE 2
#define RING 4

void visitForBridgeOrFork(int x, int y)
{
	ASSERT(!stopVisiting);
	ASSERT (!vis[x][y]);
	int edgeType = 0;
	vis[x][y] = 1;
	if (isCorner(x, y))
	{
		corners ++;
	}
	else if(edgeType = getEdge(x, y))
	{
		if (!edgesVisited[edgeType])
		{
			edgesVisited[edgeType] = 1;
			edges ++;
		}
	}
}

void visitForRing(int x, int y)
{
	ASSERT(!stopVisiting);
	ASSERT(!visited(x, y));
	vis[x][y] = 1;
	if(0 != getEdge(x, y))
	{
		ring = 0;
		stopVisiting = 1;
	}
}
struct Nb
{
	int x, y;
};
const Nb nbs[6] = {
	{0, -1},
	{0, 1},
	{-1, -1},
	{-1, 0},
	{1, 1},
	{1, 0}
};

void bfs(int x, int y, int visitFilled, VisitFunc visitFunc)
{
	ASSERT(filled(x, y) == visitFilled && visited(x, y));
	int nx, ny;
	int unvisitedCount = 0;
	Nb unvisited[6];
	for(int i = 0; i< 6; i++)
	{
		nx = x + nbs[i].x;
		ny = y + nbs[i].y;
		if (filled(nx, ny) == visitFilled)
		{
			if (!vis[nx][ny])
			{
				unvisited[unvisitedCount++] = nbs[i];
				visitFunc(nx, ny);
				if(stopVisiting)
					return;
			}
		}
	}
	for(int i = 0; i< unvisitedCount; i++)
	{
		nx = x + unvisited[i].x;
		ny = y + unvisited[i].y;
		bfs(nx, ny, visitFilled, visitFunc);
		if(stopVisiting)
			return;
	}
}

int findBridgeOrFork(int x, int y)
{
	corners = 0 ;
	edges = 0;
	stopVisiting = 0;
	memset(edgesVisited, 0, sizeof(edgesVisited));
	memset(vis, 0, sizeof(vis));
	visitForBridgeOrFork(x, y);
	if(!stopVisiting)
		bfs(x, y, 1, visitForBridgeOrFork);
	int result = 0;
	if (corners >= 2)
		result |= CORNER;
	if( edges >= 3)
		result |= EDGE;
	return result;
}

int findRing(int x, int y)
{
	ring = 0;
	memset(vis, 0, sizeof(vis));
	int nx, ny;
	for(int i = 0; i< 6; i++)
	{
		nx = x + nbs[i].x;
		ny = y + nbs[i].y;
		if (!filled(nx, ny) && !visited(nx, ny))
		{
			// Maybe we have ring
			ring = 1;
			stopVisiting = 0;
			visitForRing(nx, ny);
			if (!stopVisiting)
				// visit board for unfilled stone, if (nx, ny) can reach the Edge, then it is not encircled
				bfs(nx, ny, 0, visitForRing);
			if (ring)
				break;
		}
	}
	int result = 0;
	if(ring)
		result |= RING;
	return result;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int T;
	int M;
	cin >> T;
	int caseIndex = 1;
	while(caseIndex <= T)
	{
		cin >> S >> M;
		int move = 0;
		int result = 0;
		int x, y;
		init();
		while(M--)
		{
			cin >> x >> y;
			if (result)
				continue;
			move++;
			board[x][y] = 1;
			result = findBridgeOrFork(x, y) | findRing(x, y);
		}
		printf("Case #%d: ", caseIndex);
		caseIndex ++;
		if (result)
		{
			int addSlash =0 ;
			if(result & CORNER)
			{
				addSlash = 1;
				printf("bridge");
			}
			if(result & EDGE)
			{
				if(addSlash)
					printf("-");
				addSlash = 1;
				printf("fork");
			}
			if (result & RING)
			{
				if(addSlash)
					printf("-");
				printf("ring");
			}
			printf(" in move %d\n", move);
		}
		else 
			printf("none\n");
	} 
}