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
#define MAXN 10000
char s[MAXN+20];
struct Word
{
	char*s;
	int len;
};
Word makeWord(char*s, int l)
{
	Word w = {s, l};
	return w;
}
Word words[MAXN];
int nws;
int n;
struct Result
{
	int next;
	int wordsLen;
};

Result makeResult(int next, int wordsLen)
{
	Result r = {next, wordsLen};
	return r;
}
#define INVALID_VALUE (-1)
int f[MAXN];
Result g[MAXN];
#define f(x) f[x]
#define g(x) g[x]

inline int pow2(int x) {return x*x;}
int getSmallestBadness(int spaces, int words)
{
	ASSERT(words >=1);
	if(words == 1)
		return 500;
	int splits = words - 1;
	ASSERT(spaces >= splits);
	int x = spaces/splits;
	int n2 = spaces%splits;
	return pow2(x+1-1)*n2 + (splits-n2)*pow2(x-1);
}

// put the wordIndexth word in the new line
int get(int wordIndex)
{
	if(wordIndex == nws)
		return 0;
	// if(wordIndex == nws-1)
	// 	return words[wordIndex] == n ? 0 : 500;
	int ret = f(wordIndex);
	if(ret != INVALID_VALUE)
		return ret;
	ret = MAX_INT;
	int lineCount = words[wordIndex].len;
	forn(i, wordIndex+1, nws+1)
	{
		// put the ith word in the next line
		int x = get(i);
		int t = getSmallestBadness(n - lineCount, i - wordIndex);
		if(x + t <= ret)
		{
			ret = x+t;
			g(wordIndex) = makeResult(i, lineCount);
		}
		lineCount += words[i].len;
		// Check if we can put this word in current line
		if(lineCount + (i - wordIndex + 1 - 1) /* spaces */ > n)
			break;
	}
	ASSERT(ret != MAX_INT);
	return f(wordIndex) = ret;
}

void print(char c, int n)
{
	while(n--)
		putchar(c);
}

void solve()
{
	ASSERT(getSmallestBadness(5, 4) == 9);
	ASSERT(getSmallestBadness(5, 3) == 13);
	ASSERT(getSmallestBadness(5, 1) == 500);
	ASSERT(getSmallestBadness(5, 6) == 5);
	nws = 0;
	memset(f, 0xff, sizeof(f));
	char *p = s;
	for(;;)
	{
		while(*p && isspace(*p))
			++p;
		if(!*p)
			break;
		char*start = p;
		while(*p && !isspace(*p))
			++p;
		words[nws++] = makeWord(start, p-start);
		if(*p)
		{
			*p = 0;
			++p;
		}
		else
			break;
	}
	if(nws == 0)
		return;
	get(0);
	int i = 0;
	while(i < nws)
	{
		int next = g(i).next;
		int splits = next - i - 1;
		int spaces = n - g(i).wordsLen;
		ASSERT(spaces >= splits);
		printf("%s", words[i].s);
		if(splits == 0)
		{
		}
		else
		{
			int x = spaces/splits;
			int n1 = splits - spaces%splits;
			int index = 1;
			forn(j, i+1, next)
			{
				if(index++ <= n1)
					print(' ', x);
				else 
					print(' ', x+1);
				printf("%s", words[j].s);
				/*forn(k, 0, words[j].len)
				putchar(words[j].s[k]);*/
			}
		}
		printf("\n");
		i = next;
	}
}

bool testcase()
{
	cin >> n;
	if(!n)
		return false;

	memset(s, 0, sizeof(s));
	char*p = s;
	gets(p);
	while(gets(p), *p)
	{
		p += strlen(p);
		*p++ = ' ';
	}
	solve();
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}