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
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define forn2(i, a, b) for(int i = (a); i > (b); i--)
typedef unsigned long long LONG;
#define uint unsigned int

string codeMap[127];
map<string, char> decodeMap;

void init()
{
	codeMap['A'] =	".-";
	codeMap['B'] =	"-...";
	codeMap['C'] =	"-.-.";
	codeMap['D'] =	"-..";
	codeMap['E'] =	".";
	codeMap['F'] =	"..-.";
	codeMap['G'] =	"--.";
	codeMap['H'] =	"....";
	codeMap['I'] =	"..";
	codeMap['J'] =	".---";
	codeMap['K'] =	"-.-";
	codeMap['L'] =	".-..";
	codeMap['M'] =	"--";
	codeMap['N'] =	"-.";
	codeMap['O'] =	"---";
	codeMap['P'] =	".--.";
	codeMap['Q'] =	"--.-";
	codeMap['R'] =	".-.";
	codeMap['S'] =	"...";
	codeMap['T'] =	"-";
	codeMap['U'] =	"..-";
	codeMap['V'] =	"...-";
	codeMap['W'] =	".--";
	codeMap['X'] =	"-..-";
	codeMap['Y'] =	"-.--";
	codeMap['Z'] =	"--..";
	codeMap['_'] = "..--";
	codeMap['.'] = "---.";
	codeMap[','] = ".-.-";
	codeMap['?'] = "----";

	forn(i, 0, 127)
	{
		if(!codeMap[i].empty())
			decodeMap[codeMap[i]] = i;
	}
}

template<class T>
void reverse(T *s, int len)
{
	T*p = s+len-1;
	while(s < p)
	{
		swap(*s, *p);
		--p;
		++s;
	}
}
int caseIndex = 1;
bool testcase()
{
	int pos = 0;
	int nums[101];
	char s[101];

	cin >> s;
	string encode;
	int len = strlen(s);
	forn(i, 0,len)
	{
		encode += codeMap[s[i]];
		nums[i] = codeMap[s[i]].length();
	}
	string output;
	reverse(nums, len);
	forn(i, 0, len)
	{
		output.append(1, decodeMap[encode.substr(pos, nums[i])]);
		pos+= nums[i];
	}
	printf("%d: %s\n", caseIndex++, output.c_str());
	return true;
}

int main()
{
	init();
	ASSERT(freopen("in.txt", "r",stdin));
	int T;
	cin >> T;
	while(T--)
	{
		testcase();
	}
	return 0;
}
