#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
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
#define MAX_INT 0x7fffffff

string s;
struct Stuff
{
	char c;
	int offset;
	Stuff(char c, int offset): c(c), offset(offset){}
	Stuff():c(0), offset(0){}
};
bool cmp_stuff(const Stuff&s1, const Stuff&s2)
{
	return s1.offset < s2.offset;
}
std::vector<Stuff> v, result;
typedef vector<Stuff> Stuffs;
char opps[128], against[128];
#define opps(c) opps[c]
#define against(c) against[c]

#define TOP(s)  (*(s.end() - 1))
#define POP(s)	(void)s.erase(s.end() - 1)
#define PUSH(s, c) s.push_back(c)

int findLeft(Stuffs const& st, Stuffs::iterator it, char toSearch)
{
	Stuffs::iterator fromIt = it;
	for(; it >=st.begin(); --it)
	{
		if(it->c == toSearch)
			return fromIt - it;
		if(it == st.begin())
			break;
	}
	return MAX_INT;
}

int findRight(Stuffs const& st, Stuffs::iterator it, char toSearch)
{
	Stuffs::iterator fromIt = it;
	for(; it < st.end(); ++it)
		if(it->c == toSearch)
			return it - fromIt;
	return MAX_INT;
}


bool testcase()
{
	getline(cin, s);
	// if(!cin)
	// 	return false;

	int n = s.length();
	opps['('] = ')';
	opps[')'] = '(';
	opps['['] = ']';
	opps[']'] = '[';

	against['('] = ']';
	against[')'] = '[';
	against['['] = ')';
	against[']'] = '(';

	result.clear();

	v.clear();
	for(string::iterator it = s.begin(); it < s.end(); it++)
		v.push_back(Stuff(*it, it-s.begin()));

	vector<Stuff>::iterator it = v.begin();
	for(; it < v.end();)
	{
		char c = it->c;
		switch(c)
		{
		case ']':
		case ')':
			{
				char againstc = against(c);
				char oppc = opps(c);
				if(it > v.begin() && (it-1)->c == oppc)
					it = v.erase(it-1, it+1);
				else if(it <= v.begin())
				{
					result.push_back(Stuff(oppc, it->offset));
					it = v.erase(it);
				}
				else
				{
					ASSERT((it-1)->c == againstc);
					int left = findLeft(v, it-1, oppc);
					int right = findRight(v, it, opps(againstc));
					if(left < right)
					{
						//Add a charator for ']'(opps(againstc))
						result.push_back(Stuff(opps(againstc), (it-1)->offset));
						it = v.erase(it-1);
					}
					else
					{
						// for ')'
						result.push_back(Stuff(oppc, it->offset));
						it = v.erase(it);
					}
				}
				break;
			}
		default:
			++it;
			break;
		}
	}
	for(Stuffs::iterator it = v.begin(); it < v.end(); it++)
	{
		ASSERT(it->c == '[' || it->c == '(');
		result.push_back(Stuff(opps(it->c), it->offset));
	}
	sort(result.begin(), result.end(), cmp_stuff);
	int calcOffset =0 ;
	for(Stuffs::iterator it = result.begin(); it < result.end(); it++)
	{
		if(it->c == ']' || it->c == ')')
			s.insert(it->offset + calcOffset + 1, 1, it->c);
		else
			s.insert(it->offset + calcOffset, 1, it->c);
		calcOffset ++;
	}
	cout << s <<"\n";
	return false;
}

int main()
{
	ASSERT(freopen("in.txt", "r",stdin));
	while(testcase());
	return 0;
}
