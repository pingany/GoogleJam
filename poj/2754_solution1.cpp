
struct XValue
{
	int x;
	XValue(): x(INVALID_VALUE){}
	// XValue(int xx): x(xx){}
	// bool operator<(const XValue o)const { return x < o.x;}
};
#ifdef SOLUTION1
// int f[MAXX+1][MAXN];
#define INVALID_VALUE MIN_INT
#define IMPOSSBILE  (MIN_INT+1)
#define MAXX (2*100000)
map<int, XValue> values[MAXN];
#ifdef LOCAL
char t[MAXX+1][MAXN];
#define t(X, i)  t[X+ 25*20*MAXN][i]
#endif
#define f(X, i)  (values[i][X].x)
int get(int X, int i)
{
	int &r = f(X, i);
	if(r != INVALID_VALUE)
		return r;
	if(i == n-1)
	{
		int y = X / multi[i];
		if(y >= low[i] && y <= up[i] &&  y * multi[i] == X)
		{
			r = pairs[i] * y;
#ifdef LOCAL
			t(X, i) = y;
#endif
		}
		else 
			r = IMPOSSBILE;
		return r;
	}
	int maxf = IMPOSSBILE;
	forn(k, low[i], up[i]+1)
	{
		int subx = get(X-multi[i]*k, i+1);
		if(subx != IMPOSSBILE)
		{
			subx += k*pairs[i];
			if(subx > maxf)
			{
#ifdef LOCAL
				t(X, i) = k;
#endif
				maxf = subx;
			}
		}
	}
	return r = maxf;
}
int solve()
{
	//memset(f, 0, sizeof(f));
	// int *p = (int*)(void*)f, *end = (int*)(void*)((char*)f+ sizeof(f));
	// while(p < end)
	// {
	// 	*p = INVALID_VALUE;
	// 	++p;
	// }
	forn(i, 0, n)
		values[i].clear();
	int x = get(0, 0);
#ifdef LOCAL
	cout << "Table:";
	int X = 0;
	forn(i, 0, n)
	{
		table[i] = t(X, i);
		cout << table[i] << " ";
		X -= table[i]*multi[i];
	}
	cout << "\n";
#endif
	return x;
}
#endif /* SOLUTION1 */