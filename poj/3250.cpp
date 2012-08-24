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

template <typename T, unsigned int MAXN, typename _Compare=less<T> >
struct OrderQueue
{
	typedef void (*RemoveCallback)(const T&v, const T&newElement);
	
	T vs[MAXN];
	int m_front, m_back; 
	_Compare pred;
	RemoveCallback removeCallback;
	
	OrderQueue(): m_front(0), m_back(-1), removeCallback(NULL){}
	void clear() { m_front = 0; m_back = -1; }
	void setRemoveCallback(RemoveCallback callback) { removeCallback = callback; }
	void push_back(const T& value)
	{
		bool found = false;
		int origin_back = m_back;
		for(int x = m_back; x >=m_front; --x)
		{
			if(pred(vs[x], value))
			{
				found = true;
				m_back = x+1;
				break;
			}
		}
		if(!found)
		{
			m_back = m_front;
		}
		if(removeCallback)
			for(int x = m_back; x <= origin_back; ++x)
			{
				removeCallback(vs[x], value);
			}
		vs[m_back] = value;
	}
	int size() { return m_back-m_front+1; }
	T& front() { ASSERT(m_back>= m_front); return vs[m_front]; }
	// void pop_front() { ASSERT(back >= front); front++; }
};

struct Value
{
	int pos;
	int value;
};

Value makeValue(int pos, int v) 
{
	Value p = {pos, v};
	return p;
}
struct ValueCmp
{
	bool operator()(const Value&v1, const Value&v2)
	{
		return v1.value > v2.value;
	}
};

#define MAXN 80001
int n;
int a[MAXN];
OrderQueue<Value, MAXN, ValueCmp > q;
uint total;
void removeCallback(const Value&v, const Value&newElement)
{
	// printf("%d: %d\n", v.value, newElement.pos - v.pos -1);
	total += newElement.pos - v.pos -1;
}

bool testcase()
{
	if(1 != scanf("%d", &n))
		return false;
	forn(i, 0, n)
		scanf("%d",&a[i]);
	q.clear();
	total =0;
	forn(i, 0, n)
	{
		q.push_back(makeValue(i, a[i]));
	}
	q.push_back(makeValue(n, MAX_INT)); //force to remove all elements
	cout << total;
	return true;
}

int main()
{
	q.setRemoveCallback(removeCallback);
	ASSERT(freopen("in.txt", "r",stdin));
#ifdef LOCAL
	while(testcase())
		cout << "\n";
#else
	testcase();
#endif
	return 0;
}