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
#define MAXN 30
typedef unsigned short Matrix [MAXN][MAXN];
Matrix E;	// as known as I (unit matrix)
int n, k, m;

int add(int i, int j)
{
	return (i+j)%m;
}

int mod(int x, int y)
{
	ASSERT(y > 0);
	//consider nagetive x
	int z = (y-1)%y;
	return x >= 0 ? (x%y) : ((abs(x)*z)%y);
}

int sub(int i, int j)
{
	return (i - j + m ) % m;
}

template<typename T>
void mul(T& m, int row, int col, const T&m2, int col2)
{
	T result = {0};
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

void sub(Matrix&A, const Matrix& E)
{
	forn(i, 0, n)
			forn(j, 0, n)
				A[i][j] = sub(A[i][j],E[i][j]);
}

// return m ^ t
template<typename T>
void pow(T&m, int n, int t)
{
	T result = {0};
	// construct a E with size n
	forn(i, 0, n)
		result[i][i] = 1;
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

void pow(Matrix&m, int t)
{
	pow(m, n, t);
}

// return a^1 + a^2 + ... + a^k
void solveSimple(Matrix& a, int k)
{
	Matrix result = {0};
	Matrix origin;
	memcpy(origin, a, sizeof(a));
	while(k--)
	{
		add(result, a);
		mul(a, n, n, origin, n);
	}
	memcpy(a, result, sizeof(a));
}

// return a^1 + a^2 + ... + a^k
void solveByHalf(Matrix&a, int k)
{
	if(k <= 10)
	{
		solveSimple(a, k);
		return;
	}
	Matrix origin;
	memcpy(origin, a, sizeof(origin));
	int t = k/2;
	solveByHalf(a, t);
	// a = origin^1 + ... + origin^t

	Matrix b;
	memcpy(b, origin, sizeof(origin));
	pow(b, t);
	add(b, E);
	// b = origin^t +1

	mul(a, n, n, b, n);
	if(k & 1)
	{
		memcpy(b, origin, sizeof(origin));
		pow(b, k);
		add(a, b);
		// a  = a + origin^k
	}
}

/*
solveQuick, thanks http://poj.org/showmessage?message_id=138991
Let B=   A I  
         0 I   

B^(k+1) =    A^k   I+A+...+A^k 
             0     I
*/
typedef unsigned short BigMatrix[MAXN*2][MAXN*2];

void setSubMatrix(BigMatrix&a, int row, int col, const Matrix& b)
{
	forn(i, 0, n)
		forn(j, 0, n)
			a[i+row][j+col] = b[i][j];
}

void getSubMatrix(const BigMatrix&a, int row, int col, Matrix& b)
{
	forn(i, 0, n)
		forn(j, 0, n)
			b[i][j] = a[i+row][j+col];
}

void solveQuick(Matrix&a, int k)
{
	BigMatrix big = {0};
	setSubMatrix(big, 0, 0, a);
	setSubMatrix(big, 0, n, E);
	setSubMatrix(big, n, n, E);
	pow(big, n*2, k+1);
	getSubMatrix(big, 0, n, a);
	sub(a, E);
}

void solve()
{
	Matrix a;
	memset(E, 0, sizeof(E));
	forn(i, 0, n)
		E[i][i] = 1;
	forn(i, 0, n)
		forn(j, 0, n)
		{
			int t;
			cin >> t;
			a[i][j] = t % m;
		}
	solveQuick(a, k);
	forn(i, 0, n)
	{
		cout << a[i][0];
		forn(j, 1, n)
			cout << " " << a[i][j];
		cout << "\n";
	}
}

bool testcase()
{
	cin >> n >> k >> m;
	if(!cin)
		return false;
	solve();
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