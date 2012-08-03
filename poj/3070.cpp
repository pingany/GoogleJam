#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define INLINE inline
#ifdef _MSC_VER
#define ASSERT(x)	do{if(!(x)) __asm{int 3};}while(0)
#else
#define ASSERT(x)
#endif

#define MAX_INT 0x7fffffffL
#define forn(i, a, b) for(int i = (a); i < (b); i++)
#define uint unsigned int
#define MAXN 2
typedef int Matrix [MAXN][MAXN];
const Matrix E = {{1, 0}, {0, 1}};
const int n = 2;
#define P 10000

int add(int i, int j)
{
	return (i+j)%P;
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

int N;
void solve()
{
	Matrix a = {{1, 1}, {1, 0}};
	pow(a, N);
	cout << (int)a[1][0];
}

bool testcase()
{
	cin >> N;
	if(N < 0)
		return false;
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