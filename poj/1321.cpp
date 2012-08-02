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


char board[8][8];
int rows[8];
int n,k;
int solution;
bool canput(int row, int col)
{
	if(board[row][col] != '#')
		return false;
	for (int i = 0; i < row; i++)
	{
		if(rows[i] == col)
			return false;
	}
	return true;
}
void solve1(int row, int chessIndex)
{
	for(int j = 0; j < n; j++)
	{
		if(canput(row, j))
		{
			if(chessIndex == k - 1)
			{
				solution ++;
				continue;
			}
			rows[row] = j;
			for (int i = row + 1; i < n; i++)
				solve1(i, chessIndex+1);
			rows[row] = -1;
		}
	}
}

void solve()
{
	for(int row = 0; row < n; row++)
		solve1(row, 0);
}

bool testcase()
{
	solution = 0;
	memset(rows, 0xff, sizeof(rows));
	cin >> n >> k;
	if (n < 0)
		return false;
	for(int i =0 ;i < n; i++)
		cin >> board[i];
	solve();
	cout << solution << "\n";
	return true;
}

int main()
{
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}