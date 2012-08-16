#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
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

string tos(int a)
{
	char s[3];
	sprintf(s, "%d", a);
	return string(s);
}

#define equal(a, b) (fabs(a - b) < 1e-5)
const char* ops= "+-*/";
struct Result
{
	string s;
	float result;
	Result(){}
	Result(const string& s1, float f): s(s1), result(f){}
	bool operator==(float r)
	{
		return equal(result, r);
	}
};

float calc(float a, float b, char c)
{
	switch(c)
	{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
	}
	ASSERT(false);
	return 0;
}
void calc(int a[], int len, std::vector<Result>& results)
{
	bool ook = false;
	if(len == 1)
	{
		results.push_back(Result(tos(a[0]), a[0]));
		return;
	}
	forn(firstlen, 1, len)
	{
		
		std::vector<Result> first;
		std::vector<Result> second;
		calc(a, firstlen, first);
		calc(a+firstlen, len-firstlen, second);
		for (std::vector<Result>::iterator i = first.begin(); i != first.end(); ++i)
		{
			for (std::vector<Result>::iterator j = second.begin(); j != second.end(); ++j)
			{
				forn(opIndex, 0, 4)
				{	
					char op = ops[opIndex];
					string s = "(";
					s += i->s;
					s += string(1, op);
					s += j->s;
					s += ")";
					results.push_back(Result(s, calc(i->result, j->result, op)));
				}		
			}
		}
	}
}

bool testcase()
{
	int a[4];
	cin >> a[0] >> a[1] >> a[2] >> a[3];
	if(!cin)
		return false;
	std::vector<Result> results;
	calc(a, 4, results);
	std::vector<Result>::iterator it = find(results.begin(), results.end(), 24);
	ASSERT(it != results.end());
	char *s = (char*)(it->s.c_str());
	//remove outside "()"
	s[strlen(s)-1] = 0;
	cout << s+1;
	return true;
}

int main()
{
	
	ASSERT(freopen("in.txt", "r",stdin));
#ifdef LOCAL
	while(testcase())
		cout << "\n";
#else
	testcase();
#endif
	return 0;
}