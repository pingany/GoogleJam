#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	{if(!(x)) __asm{int 3};}
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int
struct SelectedStamp
{
	int stampIndex;
	int number;
	SelectedStamp(){}
	SelectedStamp(int s, int n): stampIndex(s), number(n){}
};

struct Result
{
	int types;
	int number;
	int highestValue;
	SelectedStamp stamps[4];

	int candidate;
};
Result result, bestRecord;
#define MAXN 100
int stamps[MAXN];
int n;

int result_cmp(const Result&r1, const Result&r2)
{
	return r1.types != r2.types ? r1.types-r2.types :
				( r1.number != r2.number ? r2.number - r1.number :
					(r1.highestValue - r2.highestValue) );
}

#ifdef LOCAL
int searches, realSearchs;
#endif
bool search(int request, int leftCount, int stampIndex)
{	
#ifdef LOCAL
	searches++;
#endif
	if(request == 0)
	{
		int ret = result_cmp(result, bestRecord) ;
		if(ret > 0)
		{
			memcpy(&bestRecord, &result, sizeof(result));
			bestRecord.candidate = 1;
			return true;
		}
		else if(ret == 0)
		{
			bestRecord.candidate++;
			return false;
		}
		else
			return false;
	}
	// Cut branches
	if(leftCount == 0 || stampIndex == n)
	{
		return false;
	}
	ASSERT(leftCount > 0 && stampIndex < n);
	int value = stamps[stampIndex];
	if(leftCount * value < request)
		return false;
	if(request < value)
	{
		forn(j, stampIndex+1, n)
		{
			if(stamps[j] <= request)
				return search(request, leftCount, j);
		}
		return false;
	}
	if(result.types + leftCount < bestRecord.types)
		return false;
	else if(result.types + leftCount == bestRecord.types)
	{
		// to get result.types + leftCount == bestRecord.types, we must select leftCount elements
		if(result.number + leftCount > bestRecord.number)
			return false;
		else if(result.number + leftCount == bestRecord.number)
		{
			//highestValue won't changes, because we traverse from high to low price
			if(result.highestValue < bestRecord.highestValue)
				return false;
			else if(result.highestValue == bestRecord.highestValue)
			{
				// It will be at most same with bestRecord. If we already have two candicates, don't need more
				if(bestRecord.candidate > 1)
					return false;
			}
		}
	}
#ifdef LOCAL
	realSearchs++;
#endif
	int avaibleCount = min(leftCount, request / value);
	bool foundSolution = false;
	for(int count = 1; count <= avaibleCount; ++count)
	{
		result.stamps[result.types++] = SelectedStamp(stampIndex, count);
		result.number+=count;
		int oldHighestValue = result.highestValue;
		result.highestValue = max(result.highestValue, value);
		if(search(request - value * count, leftCount - count, stampIndex+1))
		{
			foundSolution = true;
		}
		result.types--;
		result.number-= count;
		result.highestValue = oldHighestValue;
	}
	if (foundSolution)
	{
		// consider count ==0 here
		if(search(request, leftCount, stampIndex+1))
			foundSolution = true;
	}
	else
	{
		forn(j, stampIndex+1, n)
		{
			if(stamps[j] != stamps[stampIndex])
			{
				if(search(request, leftCount, j))
					foundSolution = true;
				break;
			}
		}
	}
	return foundSolution;
}

bool testcase()
{
	int stamp, request;
	n = 0;
	while(cin >> stamp && stamp)
	{
		stamps[n++] = stamp;
	}
	if(!cin)
		return false;
	ASSERT(n <= MAXN);
	sort(stamps, stamps+n, greater<int>());
	while(cin >> request && request)
	{
#ifdef LOCAL
		searches = realSearchs = 0;
#endif
		memset(&result, 0, sizeof(result));
		memset(&bestRecord, 0, sizeof(bestRecord));
		bool foundSolution = search(request, 4, 0);
		ASSERT(foundSolution == (bestRecord.candidate >= 1));
#ifdef LOCAL
		printf("searches: %d %d\n", searches, realSearchs);
#endif		
		if(bestRecord.candidate < 1)
			printf("%d ---- none\n", request);
		else if(bestRecord.candidate == 1)
		{
			printf("%d (%d): ", request, bestRecord.types);
			bool first = true;
			forn2(i, bestRecord.types-1, -1)
			{
				forn(j, 0, bestRecord.stamps[i].number)
				{
					if(first)
						first = false;
					else
						printf(" ");
					printf("%d", stamps[bestRecord.stamps[i].stampIndex]);
				}
			}
			printf("\n");
		}
		else
		{
			printf("%d (%d): tie\n", request, bestRecord.types);
		}
	}
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		;
	return 0;
}