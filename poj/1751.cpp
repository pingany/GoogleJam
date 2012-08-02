#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define INLINE inline
#ifdef _MSC_VER
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

template<typename T>
T maxn(T* start, T*end)
{
	ASSERT(start != end);
	T result = *start;
	++start;
	while(start != end)
	{
		if(*start > result)
			result = *start;
		start++;
	}
	return result;
}

template<typename T>
T sumn(T*start, T*end)
{
	T result = T(0);
	while(start != end)
	{
		result += *start;
		start++;
	}
	return result;
}

#define N 4
#define flip(x) (x = (0 + 1 - x))

struct Board
{
	char b[N][N];
	int layer;
};
bool visitedSet[1 << 17];
Board whiteboard, blackboard;
Board visitedBoards[1<<17];

unsigned int getInt(const Board& b)
{
	unsigned int ret = 0;
	for(int i = 0 ;i < N; i++)
		for(int j=0 ; j<N ; j++)
			ret = ret * 2 + b.b[i][j];
	return ret;
}
#define visited(b)  visitedSet[getInt(b)]
#define visit(b)  visitedSet[getInt(b)] = 1

bool isok(const Board& b)
{
	return 0 == memcmp(&b.b, &whiteboard.b, sizeof(b.b))
		|| 0 == memcmp(&b.b, &blackboard.b, sizeof(b.b));
}

bool bfs(Board&initialBoard)
{
	if(isok(initialBoard))
	{
		cout << 0;
		return true;
	}
	int vn = 0;
	visit(initialBoard);
	initialBoard.layer = 0;
	visitedBoards[vn++] = initialBoard;
	for (int v = 0; v< vn; v++)
	{
		for(int i = 0 ;i < N; i++)
			for(int j=0 ; j<N ; j++)
			{

				Board b = visitedBoards[v];
				b.layer = b.layer +1;
				flip(b.b[i][j]);
				if(i > 0)
					flip(b.b[i-1][j]);
				if (i < N-1)
					flip(b.b[i+1][j]);
				if( j > 0)
					flip(b.b[i][j-1]);
				if(j < N-1)
					flip(b.b[i][j+1]);
				if(!visited(b))
				{
					if(isok(b))
					{
						cout << b.layer;
						return true;
					}
					visit(b);
					visitedBoards[vn++]=b;
				}
			}
	}

	return false;
}

bool testcase()
{

	Board board;
	memset(visitedSet, 0, sizeof(visitedSet));
	memset(blackboard.b, 0, sizeof(blackboard.b));
	memset(whiteboard.b, 1, sizeof(whiteboard.b));
	for(int i =0 ; i < N; i++)
		cin >> board.b[i];
	for(int i = 0 ;i < N; i++)
		for(int j=0 ; j<N ; j++)
			board.b[i][j] = board.b[i][j] == 'w' ? 1 : 0;
	visit(board);
	if(!bfs(board))
		cout << "Impossible";
	return false;
}

int main()
{

	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}
