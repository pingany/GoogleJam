#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
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
#define MAXN 200
typedef char Message[MAXN+1];
int n;
int pos[MAXN], finalPos[MAXN];
void encode(char *message)
{
	Message a;
	memcpy(a, message, n+1);
	forn(i, 0, n)
		a[finalPos[i]] = message[i];
	memcpy(message, a, n+1);
}

char visit[MAXN];
int f[MAXN][MAXN];
int cicle[MAXN];
int findCicle(int i)
{
	f[i][0] = i;
	int j = 0;
	int cicle = 1;
	memset(visit, 0, n);
	for(;;)
	{
		visit[f[i][j]] = 1;
		++j;
		int x = pos[f[i][j-1]];
		if(visit[x])
		{
			cicle = j;
			break;
		}
		f[i][j] = x;
	}
	return cicle;
}
bool testcase()
{
	cin >> n;
	if(!n)
		return false;
	forn(i, 0, n)
	{
		cin >> pos[i];
		--pos[i];
	}
	forn(i, 0, n)
		cicle[i] = findCicle(i);
	int k;
	char space;
	Message message;
	while(cin >> k, k)
	{
		forn(i, 0, n)
			finalPos[i] = f[i][k % cicle[i]];
		getchar();
		gets(message);
		int len = strlen(message);
		forn(i, len, n)
			message[i] = ' ';
		message[n] = 0;
		encode(message);
		cout << message << "\n";
	}
	
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}