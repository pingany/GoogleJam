#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	{if(!(x)) __asm{int 3};}
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define MIN_INT (-2147483648)
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int
struct Value
{
	int value;
	int pos;
};

int n,k;
#define MAXN 1000000
int a[MAXN];
Value vs[MAXN];
int front,back;
template <typename _Compare>
void push(int i, _Compare cmp)
{
	bool found = false;
	for(int x = back; x >=front; --x)
	{
		if(!cmp(a[i], vs[x].value))
		{
			found = true;
			back = x+1;
			vs[back].value = a[i];
			vs[back].pos = i;
			break;
		}
	}
	if(!found)
	{
		back = front;

		vs[back].value = a[i];
		vs[back].pos = i;
	}
}
template <typename _Compare>
void solve(_Compare cmp)
{
	if(n <= 0)
		return;
	front = 0;
	vs[0].value = a[0];
	vs[0].pos = 0;
	back = 0;
	forn(i, 1, k)
	{
		push(i, cmp);
	}
	printf("%d", vs[0].value);
	forn(i, k, n)
	{
		ASSERT(back >= front);
		if(i - vs[front].pos >= k)
			front++;
		push(i, cmp);
		printf(" %d", vs[front].value);
	}
	printf("\n");
}

bool testcase()
{
	if(2 != scanf("%d%d", &n, &k))
		return false;
	forn(i, 0, n)
	scanf("%d", a+i);
	solve(less<int>());
	solve(greater<int>());
	return true;
}

#include <time.h>
int rand(int i , int j)
{
	return rand() % (j-i+1) + i;
}
void createTestData()
{
	FILE * fout = fopen("test.txt", "w");
	srand(time(0));
	int n = rand(1, 10);
	int k = rand(1, n);
	fprintf(fout, "%d %d\n", n, k);
	forn(i, 0, n)
	fprintf(fout, "%d ", rand(1, 10));
	fclose(fout);
}

int main()
{
#ifdef TEST
	createTestData();
	freopen("test.txt", "r",stdin)
#endif
	ASSERT(freopen("in.txt", "r",stdin));
#ifdef LOCAL
	while(testcase())
		cout << "\n";
#else
	testcase();
#endif
	return 0;
}