#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int
struct InputPair
{
	int color, len, originLen;
	InputPair(){}
	InputPair(int c, int l): color(c), originLen(l), len(l){}
};
#define MAXN 1002
InputPair inputPairs[MAXN];
int inputPairsNum;

struct Pair
{
	/* data */
	int color, len, originLen;
	Pair(){}
	Pair(int c, int l): color(c), originLen(l), len(0){}
	void restoreLen(){ len = originLen; }
};
typedef std::vector<Pair> LinePairs;
LinePairs lines[3], *prev, *cur, *next, results;

int min3(int a, int b, int c)
{
	return min(a, min(b, c));
}

int max4(int a, int b, int c, int d)
{
	return max(max(a, b), max(c, d));
}

int max8(int a, int b, int c, int d, int e, int f, int g, int h)
{
	return max(max4(a, b, c, d), max4(e, f, g, h));
}

int max5(int a, int b, int c, int d, int e)
{
	return max(a, max4(b, c, d, e));
}

void mergeDuplicate(LinePairs::iterator first, LinePairs::iterator last);

void reduceOrMove(LinePairs::iterator& it, int len, LinePairs::iterator end)
{
	ASSERT(it->len >= len);
	if(it->len == len)
	{
		++it;
		if(it != end)
			it->restoreLen();
	}
	else
		it->len -= len;
}
#define right(it)  (it->len == len ? (it+1)->color : it->color)
#define left(it)   (it->originLen == it->len ? (it-1)->color : it->color)

void solve()
{
	int pos = 0;
	LinePairs::iterator prevIt = prev->begin()+1,
		curIt = cur->begin()+1, nextIt = next->begin()+1;
	prevIt->restoreLen();
	curIt->restoreLen();
	nextIt->restoreLen();
	int itBefore = results.end() - results.begin();

	while(curIt != cur->end()-1)
	{
		int len = min3(prevIt->len, curIt->len, nextIt->len);
		ASSERT(len > 0);
		int itBefore = results.end() - results.begin();
		if(len == 1)
			results.push_back(Pair(max8(
			abs(left(curIt) - curIt->color),
			abs(left(prevIt) - curIt->color),
			abs(left(nextIt) - curIt->color),
			abs(curIt->color - prevIt->color),
			abs(curIt->color - nextIt->color),
			abs(right(curIt) - curIt->color),
			abs(right(prevIt) - curIt->color),
			abs(right(nextIt) - curIt->color)), 1));
		else
			results.push_back(Pair(max5(
			abs(curIt->color - prevIt->color),
			abs(curIt->color - nextIt->color),
			abs(left(curIt) - curIt->color),
			abs(left(prevIt) - curIt->color),
			abs(left(nextIt) - curIt->color)
			), 1));

		if (len > 2)
			results.push_back(Pair(max(
			abs(curIt->color - prevIt->color),
			abs(curIt->color - nextIt->color)
			), len-2));
		if( len > 1)
			results.push_back(Pair(max5(
			abs(curIt->color - prevIt->color),
			abs(curIt->color - nextIt->color),
			abs(right(curIt) - curIt->color),
			abs(right(prevIt) - curIt->color),
			abs(right(nextIt) - curIt->color)
			), 1));
		mergeDuplicate(results.begin() + itBefore, results.end());
		reduceOrMove(nextIt, len, next->end()-1);
		reduceOrMove(prevIt, len, prev->end()-1);
		reduceOrMove(curIt, len, cur->end()-1);
	}
	ASSERT(prevIt == prev->end()-1);
	ASSERT(nextIt == next->end()-1);

	mergeDuplicate(results.begin() + itBefore, results.end());
}

void mergeDuplicate(LinePairs::iterator first, LinePairs::iterator last)
{
	ASSERT(first != last);
	LinePairs::iterator prevIt = first;
	bool hasRemove = false;
	for (std::vector<Pair>::iterator it = first+1; it != last; ++it)
	{
		if(it->color == prevIt->color)
		{
			prevIt->originLen += it->originLen;
			it->originLen = 0; // remove it
			hasRemove = true;
		}
		else
		{
			prevIt = it;
		}
	}

	if(!hasRemove)
		return;
	prevIt = first;
	for (std::vector<Pair>::iterator it = first; it != last; ++it)
	{
		if(it->originLen)
			*prevIt++ = *it;
	}
	results.erase(prevIt, last);
}

void mergeDuplicate()
{
	mergeDuplicate(results.begin(), results.end());
}

void addPlaceHolder(LinePairs* v)
{
	// We add a padding data in the begining and end of a line, then we don't need
	// to check if we are on the left or right side of line
	(*v)[0] = (*v)[1];
	v->push_back(*(v->end()-1));
}

bool testcase()
{
	int color, len;
	int width;
	cin >> width;
	if(!width)
		return false;
	inputPairsNum = 0;
	while(cin >> color >> len , len)
	{
		inputPairs[inputPairsNum++] = InputPair(color, len);
	}
	results.clear();
	results.reserve(MAXN*100);

	prev = &lines[0];
	cur = &lines[1];
	next = &lines[2];
	prev->clear();
	cur->clear();
	next->clear();

	prev->reserve(MAXN);
	cur->reserve(MAXN);
	next->reserve(MAXN);

	int x = 0;
	// read cur line
	int pairIndex = 0;
	cur->push_back(Pair(0, 0)); //placeholder, see addPlaceHolder
	for(; pairIndex < inputPairsNum;)
	{
		InputPair& pair = inputPairs[pairIndex];
		int len = min(width - x, pair.len);
		if(len < pair.len)
			pair.len -= len;
		else
			pairIndex++;
		cur->push_back(Pair(pair.color, len));
		x += len;
		if( x == width)
			break;
	}
	addPlaceHolder(cur);
	// in the begining, we handle the first line, 
	// set prev to be same with cur, then the diff is 0
	prev->insert(prev->begin(), cur->begin(), cur->end());
	x = 0;
	// read next line

	next->push_back(Pair(0, 0)); //placeholder, see addPlaceHolder
	for(; pairIndex < inputPairsNum; )
	{
		InputPair& pair = inputPairs[pairIndex];
		int len = min(width - x, pair.len);
		if(len < pair.len)
			pair.len -= len;
		else
			pairIndex++;
		next->push_back(Pair(pair.color, len));
		x += len;
		if (x == width)
		{
			addPlaceHolder(next);
			solve();
			LinePairs* oldPre = prev;
			prev = cur;
			cur = next;
			next = oldPre;
			next->clear();
			next->push_back(Pair(0, 0)); //placeholder, see addPlaceHolder
			x = 0;
			/* handle special case, in which situation, line by line is so slow.
			we have at most 1000 pairs, then if we have many rows(more than 1000), we must have many duplicate lines
				10
				35 500000000
				200 500000000
				0 0
			*/
			if(pairIndex < inputPairsNum 
				&& prev->begin()->originLen == width
				&& cur->begin()->originLen == width
				&& prev->begin()->color == cur->begin()->color)
			{
				//pre, cur and next line is same
				InputPair& pair = inputPairs[pairIndex];
				if(pair.color == cur->begin()->color && pair.len >= width)
				{
					int len = pair.len - pair.len%width;
					results.push_back(Pair(0, len /* including cur line */));
					// cur, prev don't change, they are same, but the next line is not same with it
					if(len < pair.len)
						pair.len -= len;
					else
						pairIndex++;
				}
			}
		}
	}

	// in the end, we handle the last line, we set "next" to be same with cur, then diff is 0
	next->clear();
	next->insert(next->begin(), cur->begin(), cur->end());
	solve();

	mergeDuplicate();

	printf("%d\n", width);
	for (std::vector<Pair>::iterator it = results.begin(); it != results.end(); ++it)
	{
		printf("%d %d\n", it->color, it->originLen);
	}
	printf("0 0\n");
	return true;
}

int main()
{

	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		;
	cout << "0\n";
	return 0;
}
