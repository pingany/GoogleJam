#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
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
#define MAX_INT 0x7fffffff

#define N 200
char s[200];
int f[N+2][N+2];

struct Pos
{
	int pos;
	int k;
};
Pos pos[N+2][N+2];
Pos makePos(int pos, int k)
{
	Pos p ={ pos, k};
	return p;
}
int result[N+2];
int resultIndex = 0;

void getResult(int i, int j)
{
	int p = pos[i][j].pos;
	if(p == -3)
		return;
	else if(p == -2)
		getResult(i+1, j-1);
	else if(p == -1)
	{
		int k = pos[i][j].k;
		ASSERT( k >= i && k < j);
		getResult(i, k);
		getResult(k+1, j);
	}
	else
		result[resultIndex++] = p;
}

bool testcase()
{
	cin.getline(s, sizeof(s));
	int n = strlen(s);

	memset(f, 0, sizeof(f));
	for(int i = n-1; i >= 0; i--)
		for(int j = i; j < n; j++)
		{
			if(i==j)
			{
				f[i][j] = 1;
				pos[i][j] = makePos(i, 0);
			}
			else
			{
				ASSERT(i < n -1 && j > 0);
				int minf = MAX_INT;
				if((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']'))
				{
					if(i+1 > j-1)
					{
						pos[i][j] = makePos(-3, 0);
						minf = 0;
					}
					else
					{
						if(f[i+1][j-1] < minf)
						{
							minf = f[i+1][j-1];		
							pos[i][j] = makePos(-2, 0);
						}
					}
				}
				for(int k = i; k < j; k++)
				{
					int temp = f[i][k] + f[k+1][j];
					if(temp < minf)
					{
						minf = temp;
						pos[i][j] = makePos(-1, k);
					}
				}
				f[i][j] = minf;
			}
		}
		resultIndex = 0;
		memset(result, 0, sizeof(result));
		getResult(0, n-1);
		sort(result, result + resultIndex);
		int j = 0;
		for(int i = 0; i < n; i++)
		{
			if(j < resultIndex &&  i == result[j])
			{
				cout << ((s[i] == '(' || s[i] == ')')  ? "()" : "[]");
				++j;
			}
			else
				cout << s[i];
		}
		cout <<"\n";
		return false;
}


int main()
{
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}
