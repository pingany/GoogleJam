
#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <queue>
#include <algorithm>  
#include <map>
#include <sstream>
using namespace std;  

#define INLINE inline
#ifdef LOCAL
#include <time.h>
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#define TIME() ((unsigned int)((float)clock()/CLOCKS_PER_SEC))
#define TIMING_START_ALL()  allTimeStart = TIME()
#define TIMING_END_ALL()  cout << "All cases: " << (TIME() - allTimeStart) << "\n";
#define TIMING_START_CASE() caseStart = TIME()
#define TIMING_END_CASE()  cout << "A case: " << (TIME() - caseStart) << "\n";
float caseStart, allTimeStart;
#else
#define ASSERT(x)
#define TIMING_START_ALL()
#define TIMING_START_CASE()
#define TIMING_END_ALL()
#define TIMING_END_CASE()
#endif
#define forn(i, a, b)  for(int i = (a); i < (b); i++)
#if 0//def LOCAL
#define MAXN 6
#define MAXM 10
#else
#define MAXN 150
#define MAXM 10
#endif

#define COUNTOF(x)  (sizeof(x)/sizeof(x[0]))
typedef unsigned long long LONG;
typedef unsigned char ResultType;
#define INVALID_VALUE  (0xff)
typedef unsigned int State;
int N,M;
char board[MAXN][MAXM];
#define boardOk(x, y) (!board[x][y])

#define MAX_LINE_STATES 275
ResultType f[MAXN][MAX_LINE_STATES+1][MAX_LINE_STATES+1];
unsigned short index[1 << (2*MAXM)];
#define f(row, s1, s2)  f[row][index[s1]][index[s2]]

std::vector<State> state_vectors[MAXN+1];

//#define get(s, i)  ((s >> (i*2)) & 3)
#define clearS(s, i) (s &= (~(3UL << ((i)*2))))
#define set(s, i, x)  (clearS(s, (i)), s|= ((x) << ((i)*2)))

void setBack(State& s, const int i, const int x)
{
	unsigned char buffer[20] = {0};
	int n = 0;
	State s2 = s;
	while(s2)
	{
		buffer[n++] = s2&3;
		s2>>=2;
	}
	buffer[i] = x;
	n = max(n, i+1);
	State ret = 0;
	for(int j = n-1; j>= 0; j--)
		ret = ret*4 + buffer[j];

	{
		State s2 = s;
		set(s2, i, x);
		ASSERT(s2 == ret);
	}
	s = ret;
}
void enumerate(State initial_state, char*taken, int row, int col, std::vector<State> &v);

inline bool canput(char* taken, int row, int col, int w, int h)
{
	if(!(row + h <= N && col + w <= M))
		return false;
	forn(i, 0, w)
	{
		if(taken[col+i])
			return false;
	}
	forn(i, 0, w)
		forn(j, 1, h)
			{
				if(!boardOk(row+j, col+i))
					return false;
			}
	return true;;
}
#define canput1(taken, row, col) canput(taken, row, col, 3, 2)
#define canput2(taken, row, col) canput(taken, row, col, 2, 3)
void enumerateAllStates(int row, State s1, State s2, std::vector<State>&v)
{
	v.reserve(MAX_LINE_STATES);
	State s = 0;
	char taken[MAXM] = {0};
	int x = s1, y = s2;
	forn(col, 0, M)
	{
		if(!boardOk(row, col) || (y & 3) >= 2 || (x & 3) >= 1)
			taken[col] = 1;
		x >>= 2;
		y >>= 2;
	}
	enumerate(s, taken, row, 0, v);
}

void enumerate(State initial_state, char*taken, int row, int col, std::vector<State> &v)
{
	ASSERT(col <= M);
	if(col == M-1)
	{
		v.push_back(initial_state);
		return;
	}
	//forn(col, col, M)
	{
		// 3 * 2
		if(canput1(taken, row, col))
		{
			State s = initial_state;
			set(s, col, 0x15);
			// equal to
			// set(s, col, 1);
			// set(s, col+1, 1);
			// set(s, col+2, 1);
			enumerate(s, taken, row, col+3, v);
		}
		if(canput2(taken, row, col))
		{
			State s = initial_state;
			set(s, col, 0xa);
			// equal to:
			// set(s, col, 2);
			// set(s, col+1, 2);
			enumerate(s, taken, row, col+2, v);
		}
		enumerate(initial_state, taken, row, col+1, v);
	}
}

unsigned char blockNumber[1 << (2*MAXM)];
inline ResultType getBlockNumber(State s)
{
	if(blockNumber[s] != 0xff)
		return blockNumber[s];
	State origin_s = s;
	int x;
	ResultType ret = 0;
	while(s)
	{
		x = s &3;
		if(x == 1)
		{
			ASSERT((s&0x3f) == 0x15);
			s >>= 2*3;
			ret++;
		}
		else if (x == 2)
		{
			ASSERT((s&0xf) == 0xa);
			s >>= 2*2;
			ret++;
		}
		else
			s >>= 2;
	}
	return blockNumber[origin_s] = ret;
}

ResultType solve(int row, State s1, State s2)
{
	if(row == N-1)
		return 0;
	ResultType ret = f(row, s1, s2);
	if(ret != INVALID_VALUE)
		return ret;
	ret = 0;
	std::vector<State>&v = state_vectors[row];
	v.clear();
	enumerateAllStates(row, s1, s2, v);
	for (std::vector<State>::iterator it = v.begin(); it != v.end(); ++it)
	{
		ret = max(ret, (ResultType)(getBlockNumber(*it) + solve(row+1, *it, s1)));
	}
	return f(row, s1, s2) = ret;
}

int main()
{
#if 0 // def LOCAL
	{
		State s = 0xff00;
		set(s, 0, 2);
		ASSERT(s == 0xff02);
		set(s, 1, 2);
		ASSERT(s == 0xff0a);
		set(s, 1, 1);
		ASSERT(s == 0xff06);
		set(s, 2, 1);
		ASSERT(s == 0xff16);
		set(s, 2, 0);
		ASSERT(s == 0xff06);
		set(s, 1, 0);
		ASSERT(s == 0xff02);
	}
#endif
	ASSERT(freopen("in.txt", "r", stdin));
	int T;
	int x, y, K;

	memset(blockNumber, 0xff, sizeof(blockNumber));

	N = MAXN, M = MAXM;
	int indexTableLength = 0;
	memset(index, 0, sizeof(index));
	memset(board, 0, sizeof(board));
	std::vector<State> &v = state_vectors[0];
	v.clear();
	enumerateAllStates(0, 0, 0, v);
	ASSERT(v.size () <=  MAX_LINE_STATES);
	for (std::vector<State>::iterator i = v.begin(); i != v.end(); ++i)
	{
		ASSERT((*i) < COUNTOF(index));
		index[*i] = indexTableLength++;
	}
	TIMING_START_ALL();
	cin >>T;
	while(T--)
	{
		TIMING_START_CASE();
		memset(board, 0, sizeof(board));
		memset(f, 0xff, sizeof(f));
		cin >> N >> M >> K;
		while(K--)
		{
			cin >> x >> y;
			board[x-1][y-1] = 1;
		}
		cout << (int)solve(0, 0, 0) << "\n";
		TIMING_END_CASE();
	}
	TIMING_END_ALL();
}