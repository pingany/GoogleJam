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

bool trysolve(int len, int first);

int N;
int sumlen;
int maxlen;
int sticks[65];
bool used[65];

bool greater1(int i, int j)
{
	return i > j;
}

INLINE int findUnused(int start)
{
	for(int i = start; i < N; i++)
	{
		if(!used[i])
			return i;
	}
	return N;
}

bool solve(int totallen)
{
	int len = totallen;
	int first = findUnused(0);
	ASSERT(first < N);
	used[first] = true;
	len -= sticks[first];
	return trysolve(len, first+1);
}

INLINE int findNext(int k)
{
	for(int i =k+1; i < N; i++)
	{
		if(sticks[i] != sticks[k] && !used[i])
			return i;
	}
	return N;
}

bool trysolve(int len, int first)
{
	ASSERT(len >= 0);
	if(len == 0)
		return true;
	if(first >= N)
		return false;
	for(int i = findUnused(first); i < N;)
	{
		int k = i;
		if(sticks[k] >len)
		{
			i = findNext(k);
			continue;
		}
		else
		{
			used[k] = true;
			if(trysolve(len - sticks[k], k+1))
				return true;
			used[k] = false;
			i = findNext(k);
		}
	}
	return false;
}

bool testcase()
{
	cin >> N;
	if(!N)
		return false;
	for(int i =0; i< N; i++)
		cin >> sticks[i];
	sumlen = sumn(sticks, sticks+N);
	sort(sticks, sticks+N, greater1);
	maxlen = sticks[0];
	int result = sumlen;
	//len == sumlen is of curse OK
	for (int len = maxlen; len < sumlen; len++)
	{
		if (sumlen % len != 0)
			continue;
		memset(used, 0, sizeof(used));
		int n = sumlen/len - 1;
		bool ok = true;
		while(n--)
		{
			if(!solve(len))
			{
				ok = false;
				break;
			}
		}
		if(ok)
		{
			result = len;
			break;
		}
	}
	cout << result << "\n";
	return true;
}

int main()
{
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}