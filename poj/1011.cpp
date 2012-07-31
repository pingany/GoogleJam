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
INLINE int findNext(int k);

int N;
int sumlen;
int maxlen;
int sticks[65];
bool used[65];
int unitlen;

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

bool solve(int totallen, int leftunit, int first)
{
	ASSERT(totallen >= unitlen && leftunit % unitlen == totallen % unitlen);
	if(totallen == unitlen)
		return true;
	if(leftunit == 0)
		leftunit = unitlen;
	if(leftunit == unitlen)
	{
		first = findUnused(0);
		used[first] = true;
		bool result = solve(totallen - sticks[first], leftunit - sticks[first], findUnused(first+1));
		if(result)
			return result;		
		used[first] = false;
	}
	else
	{
		for(int i = first; i < N;)
		{
			if(sticks[i] > leftunit)
			{
				i = findNext(i);
				continue;
			}
			else
			{
				used[i] = true;
				bool result = solve(totallen - sticks[i], leftunit - sticks[i], findUnused(i+1));
				if(result)
					return true;
				used[i] = false;
				i = findNext(i);
			}
		}
	}
	return false;
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
		unitlen = len;
		bool ok = solve(sumlen, unitlen, 0);
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
