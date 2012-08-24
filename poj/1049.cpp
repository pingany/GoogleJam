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
char s[257];

int loadAddress(int i)
{
	int a;
	char address[3] = {0};
	memcpy(address, s+i, 2);
	sscanf(address, "%x", &a);
	return a;
}

const char* hexs= "0123456789ABCDEF";
char nums[127];
// #define toNum(c) nums[c]
void init()
{
	memset(nums, 0xff, sizeof(nums));
	forn(i, 0, 16)
		nums[hexs[i]] = i;
}
inline int toNum(char c)
{
	ASSERT(nums[c] != -1);
	return nums[c];
}
inline char toHex(int x)
{
	ASSERT(  x >= 0 && x < 0x10);
	return hexs[x];
}
bool testcase()
{
	int A =0 , B = 0;
	int i = 0;
	int address;
	cin >> s;
	if(s[0] == '8')
		return false;
	for(;;)
	switch(s[i])
	{
		case '0':
		{
			address = loadAddress(i+1);
			A = toNum(s[address]);
			i += 3;
			break;
		}
		case '1':
		{
			address = loadAddress(i+1);
			s[address] = toHex(A);
			i += 3;
			break;
		}
		case '2':
		{
			swap(A, B);
			i+=1;
			break;
		}
		case '3':
		{
			unsigned int x = A + B;
			A = x & 0xf;
			B = x >> 4;
			i+=1;
			break;
		}
		case '4':
		{
			A = (A+1) & 0xf;
			i+= 1;
			break;
		}
		case '5':
		{
			A = (A + 0x10 - 1) & 0xf;
			i+=1;
			break;
		}
		case '6':
		{
			if(!A)
			{
				int address = loadAddress(i+1);
				i = address;
			}
			else
				i+=3;
			break;
		}
		case '7':
		{
			i = loadAddress(i+1);
			break;
		}
		case '8':
		{
			goto stop;
		}
		default:
			ASSERT(false);
	}
stop:
	cout << s;
	//todo, output
	return true;
}

int main()
{
	init();
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase())
		cout << "\n";
	return 0;
}