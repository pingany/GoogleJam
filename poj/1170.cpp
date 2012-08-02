#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <queue>
#include <algorithm>  
  
using namespace std;  
 
#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif
#define forn(i, a, b)  for(int i = (a); i < (b); i++)

#define MAXB 5
#define MAXK (5+1)
struct Item
{
	int code;
	int number;
	int price;
};

struct Offer
{
	int n;
	struct Pair
	{
		int code;
		int number;
	} ps[MAXK+1];
	int total;
};
int b;
Item items[MAXB+1];
int s;
#define MAXS 100
Offer offers[MAXS+1];
int codeIndexTable[1001];
//hardcode, MAXB times of MAXK
int f[MAXK*MAXK*MAXK*MAXK*MAXK + 1];
#define getIndexByCode(code) codeIndexTable[code]
struct Good
{
	char ns[MAXB];
};
int getInt(const Good& good)
{
	int ret = 0;
	forn(i, 0, b)
		ret = ret * MAXK + good.ns[i];
	return ret;
}

int getMaxPrice(const Good&good)
{
	int ret = 0;
	forn(i, 0, b)
		ret += good.ns[i] * items[i].price;
	return ret;
}

bool satisfied(const Good&good, const Offer& offer)
{
	forn(i, 0, offer.n)
	{
		if(getIndexByCode(offer.ps[i].code) <0 || good.ns[getIndexByCode(offer.ps[i].code)] < offer.ps[i].number)
			return false;
	}
	return true;
}

Good buy(const Good&good, const Offer&offer)
{
	Good ng = good;
	forn(i, 0, offer.n)
		ng.ns[getIndexByCode(offer.ps[i].code)] -= offer.ps[i].number;
	return ng;
}

int calc(const Good&good)
{
	int t = getInt(good);
	if(f[t] != -1)
		return f[t];
	int minprice = getMaxPrice(good);
	forn(i, 0, s)
	{
		if(satisfied(good, offers[i]))
		{
			Good ng = buy(good, offers[i]);
			int cost = offers[i].total + calc(ng);
			minprice = min(minprice, cost);
		}
	}
	return f[t] = minprice;
}
void solve()
{
	memset(f, 0xff, sizeof(f));
	memset(codeIndexTable, 0xff, sizeof(codeIndexTable));
	forn(i, 0, b)
	{
		codeIndexTable[items[i].code] = i;
	}
	Good good = {0};
	forn(i, 0, b)
		good.ns[i] = items[i].number;
	cout << calc(good) << "\n";
}

int main()
{
	ASSERT(freopen("in.txt", "r", stdin));
	cin >> b;
	forn(i, 0, b)
		cin >> items[i].code >> items[i].number >> items[i].price;
	cin >> s;
	forn(i, 0, s)
	{
		cin >> offers[i].n;
		forn(j, 0, offers[i].n)
		{
			cin >> offers[i].ps[j].code >> offers[i].ps[j].number;
		}
		cin >> offers[i].total;
	}
	solve();;
	return 0;
}
