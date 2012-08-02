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

#define forn(i, a, b) for(int i = a; i < b; i++)
#define uint unsigned int

struct  Board
{
	int end[2], h;
};
int N, X, Y, MAXH;
Board board[1001];
uint record[1001][2];

#define MAX_UINT  (0xffffffffUL)
#define MAX_VALUE (MAX_UINT/2)
#define INVALID_VALUE MAX_UINT
#define MIN_X (-20002)
#define MAX_X (20002)

int findBoard(int x, int y, int start);
uint go(int bi, int end)
{
	if(bi == N - 1)
		return 0;
	if(record[bi][end] != INVALID_VALUE)
		return record[bi][end];
	uint result = MAX_VALUE;
	int x = board[bi].end[end];
	int y = board[bi].h;
	int i = findBoard(x, y, bi+1);
	{
		ASSERT(y >= board[i].h);
		if(y > board[i].h && board[i].h >= y - MAXH && board[i].end[0] <= x && x <= board[i].end[1])
		{
			uint time = y - board[i].h;
			if (i != N - 1)
				time += min(
					go(i, 0) + abs(x - board[i].end[0]),
					go(i, 1) + abs(x - board[i].end[1]));
			result = std::min(result, time);
		}
	}
	//printf("record [%d][%d]:%u\n", bi, end, result);
	return record[bi][end] = result;
}

bool cmp_board(const Board&b1, const Board&b2)
{
	if(b1.h == b2.h)
		return b1.end[0] == b2.end[0] ? b1.end[1] < b2.end[1] : b1.end[0] < b2.end[0];
	else 
		return b1.h > b2.h;
}

int findBoard(int x, int y, int start)
{
	forn(i, start, N)
	{
		if(y > board[i].h && board[i].h >= y - MAXH && board[i].end[0] <= x && x <= board[i].end[1])
		{
			return i;
		}
	}
	ASSERT(false);
}

void solve()
{
	//Add background
	board[N].h = 0;
	board[N].end[0] = MIN_X;
	board[N].end[1] = MAX_X;
	N++;
	memset(record, 0xff, sizeof(record));
	sort(board, board+N, cmp_board);
	int start = findBoard(X, Y, 0);
	int time = Y - board[start].h;
	if (start != N-1)
		time +=
			  min(abs(X - board[start].end[0]) + go(start, 0), 
				   abs(X - board[start].end[1]) + go(start, 1));
	cout << time << "\n";
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	int T;
	cin >> T;
	while(T --)
	{
		cin >> N >> X >> Y >> MAXH;
		forn(i, 0, N)
		{
			cin >> board[i].end[0] >> board[i].end[1] >> board[i].h;
		}
			solve();
	}
	return 0;
}