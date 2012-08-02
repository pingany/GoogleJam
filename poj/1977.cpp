#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <queue>
#include <algorithm>  
#include <map>
#include <sstream>
using namespace std;  
 
#define INLINE inline
#ifdef LOCAL
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif
#define forn(i, a, b)  for(int i = (a); i < (b); i++)
#ifdef LOCAL
#define MAXN 3
#else
#define MAXN 100
#endif
int n, t;
char linebuffers[MAXN][30 * MAXN];

map<string, int> names;

char A[MAXN][MAXN], E[MAXN][MAXN];
typedef char Matrix [MAXN][MAXN];
Matrix init;

int add(int i, int j)
{
	return (i+j)%2;
}
void mul(Matrix& m, int row, int col, const Matrix&m2, int col2)
{
	Matrix result = {0};
	forn(i, 0, row)
		forn(j, 0, col2)
			forn(k, 0, col)
				result[i][j] = add(result[i][j], m[i][k]*m2[k][j]);
	memcpy(m, result, sizeof(result));
}

void add(Matrix&A, const Matrix& E)
{
	forn(i, 0, n)
			forn(j, 0, n)
				A[i][j] = add(A[i][j],E[i][j]);
}
void pow(Matrix&m, int t)
{
	Matrix result;
	memcpy(result, E, sizeof(E));
	while(t)
	{
		int x = t % 2;
		if(x)
			mul(result, n, n, m, n);
		mul(m, n, n, m, n);
		t /= 2;
	}
	memcpy(m, result, sizeof(m));
}

void solve()
{
	if(t > 0)
	{
		pow(A, t);
		mul(init, 1, n, A, n);
	}
	int sum = 0;
	forn(i, 0 , n)
		sum += init[0][i];
	cout << sum <<"\n";
}	

int main()
{

	ASSERT(freopen("in.txt", "r", stdin));
	

	int T;
	cin >> T;
	while (T--)
	{
		cin >> n >> t;
		t--;
		memset(E, 0, sizeof(E));
		forn(i, 0, MAXN)
			E[i][i] = 1;

		names.clear();
		memset(init, 0, sizeof(0));
		memset(A, 0, sizeof(A));
		string name;
		forn(i, 0, n)
		{
			int x;
			cin >> name;
			cin >> x;
			names[name] = i;
			x = x % 2;
			init[0][i] = x;
			cin.getline(linebuffers[i], sizeof(linebuffers[i]));
		}
		forn(i, 0, n)
		{
			stringstream ss(linebuffers[i]);
			int k;
			string name;
			ss >> k;
			while(k--)
			{
				ss >> name;
				A[i][names[name]] = 1;
			}
		}
		add(A, E);
		
		solve();
	}
}