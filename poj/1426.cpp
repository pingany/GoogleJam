#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#define INLINE inline
#ifdef _MSC_VER
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

int n;
int used[101];
struct Mod
{
	int digitpos;
	int mod;
};
Mod mods[101];

bool go(int sum, int k)
{
	
	if(sum >0 && sum % n == 0)
	{
		for(int i = k - 1; i >= 0; i--)
			cout << used[i];
		cout << "\n";
		return true;
	}
	if(k > 20)
		return false;
	used[k]=1;
	if(go(sum + mods[k].mod, k+1))
		return true;
	else
	{
		used[k]=0;
		return go(sum, k+1);
	}
}
void solve()
{
	mods[0].digitpos = 0;
	mods[0].mod = 1;
	for(int i =1 ;i < 100;i++)
	{
		mods[i].digitpos = i;
		mods[i].mod = (mods[i-1].mod * 10)%n;
		if(mods[i].mod == 0)
		{
			cout << '1';
			int j = i;
			while(j--)
				cout << '0';
			cout << '\n';
			return;
		}
	}

	memset(used, 0, sizeof(used));
	go(0, 0);
}
bool testcase()
{
	cin >> n;
	if(!n)
		return false;
	solve();
	return true;
}
int main()
{
	ASSERT(freopen("in.txt", "r", stdin));
	while(testcase());
	return 0;
}