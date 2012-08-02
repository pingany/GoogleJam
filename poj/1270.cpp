#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
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

int n,cn;
char vars[30];
char putted[128];
char dep[128][30];
char output[30];
char resultBuffer[301][30];
char* result[301];
int resultIndex = 0;
struct
{
	char x, y;
} cs[51];

bool canput(char v)
{
	char *s = dep[v];
	while(*s)
	{
		if(!putted[*s])
			return false;
		++s;
	}
	return true;
}

void put(int index)
{
	for(int i = 0; i < n; i++)
	{
		char v = vars[i];
		if (!putted[v] && canput(v))
		{
			putted[v] = 1;
			output[index] = v;
			if(index == n-1)
			{
				strcpy(result[resultIndex++], output);
			}
			else
			{
				put(index+1);
			}
			putted[v] = 0;
		}
	}
}

bool str_cmp(char*s1, char*s2)
{
	return strcmp(s1, s2) < 0;
}

void solve()
{
	memset(putted, 0, sizeof(putted));
	memset(dep, 0, sizeof(dep));
	memset(output, 0, sizeof(output));
	for(int i =0 ; i< cn; i++)
	{
		char ts[] = {cs[i].x, 0};
		strcat(dep[cs[i].y], ts);
	}
	for(int i = 0 ; i< sizeof(result)/sizeof(result[0]); i++)
		result[i] = resultBuffer[i];
	resultIndex = 0;
	put(0);
	sort(result, result + resultIndex, str_cmp);
	for(int i =0 ; i< resultIndex; i++)
	{
		cout << result[i] << "\n";
	}
}

static bool first = true;
bool testcase()
{
	char linebuffer[1000];
	cin.getline(linebuffer, sizeof(linebuffer));
	if(!cin)
		return false;
	char c;
	{
		n = 0;
		stringstream s(linebuffer);
		while(s >> c)
		{
			vars[n++]=c;
		}
	}
	cin.getline(linebuffer, sizeof(linebuffer));
	{
		cn = 0;
		char c2;
		stringstream s(linebuffer);
		while(s >> c)
		{
			s >> c2;
			cs[cn].x = c;
			cs[cn].y = c2;
			cn++;
		}
	}
	if(first)
		first = false;
	else
	{
		cout << "\n";
	}
	solve();
	return true;
}

int main()
{
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}