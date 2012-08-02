#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define forn(i, n)  for(int i = 0; i < (n) ; i++)
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

int N;
char heights[1001][10];
/* max number of soldiers which are sorted in ascending order to the Kth soldier */
int maxNumDownFrom[1002];
/* max number of soldiers which are sorted in descending order from the Kth soldier */ 
int maxNumUpTo[1002];
/* max number of soldiers which are sorted in ascending order in the left of
the Kth soldier and in descending order in the right 
Notice: maybe we have two highest points like:
 3 4 5 5 4 3
*/
int result[1002];
bool testcase()
{
	cin >> N;
	memset(heights, 0, sizeof(heights));
	memset(maxNumDownFrom, 0, sizeof(maxNumDownFrom));
	memset(maxNumUpTo, 0, sizeof(maxNumUpTo));
	for(int i = 0; i < N; i++)
	{
		cin >> heights[i];
		//remove tailing '0' for string campare
		char *p = heights[i] + strlen(heights[i]) - 1;
		while(p >= heights[i] && *p == '0')
		{
			*p = 0;
			--p;
		}
	}
	maxNumDownFrom[N-1]=1;
	for(int k = N-2; k>=0; k--)
	{
		int maxf = 0;
		for(int i = k+1; i < N; i++)
		{
			if(strcmp(heights[i], heights[k]) < 0 && maxNumDownFrom[i] > maxf)
				maxf = maxNumDownFrom[i];
		}
		maxNumDownFrom[k] = maxf + 1;
	}
	maxNumUpTo[0] = 1;
	for(int k = 1; k < N; k++)
	{
		int maxf = 0;
		for(int i = 0; i < k; i++)
		{
			ASSERT(maxNumUpTo[i] > 0);
			if(strcmp(heights[i], heights[k]) < 0 && maxNumUpTo[i] > maxf)
				maxf = maxNumUpTo[i];
		}
		maxNumUpTo[k] = maxf + 1;
		ASSERT(maxNumUpTo[k] > 0);
	}
	forn(k, N)
	{
		int maxf = maxNumDownFrom[k] + maxNumUpTo[k] - 1;
		for(int i = k+1; i < N; i++)
		{
			if(strcmp(heights[i], heights[k]) == 0 && maxNumUpTo[k] + maxNumDownFrom[i] > maxf)
				maxf = maxNumUpTo[k] + maxNumDownFrom[i];
		}
		result[k] = maxf;
	}
	cout << N - maxn(result, result+N);
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	testcase();
	return 0;
}