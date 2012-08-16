#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 510;
const int INF = 0x7FFFFFFF;

int n, m, pre[N], dist[N], map[N][N];
bool visit[N];

int abs(int x)
{
    if(x < 0)  return -x;
    else  return x;
}

void dijkstra()
{
    int i, j, k, Min;
    for(i = 1; i <= n; i++)
    {
        dist[i] = map[1][i];
        pre[i] = 1;
    }
    memset(visit, false, sizeof(visit));
    visit[1] = true;
    for(k = 1; k < n; k++)
    {
        j = 0;
        Min = INF;
        for(i = 1; i <= n; i++)
            if(!visit[i] && dist[i]!=-1 && dist[i]<Min)
            {
                Min = dist[i];
                j = i;
            }
        visit[j] = true;
        for(i = 1; i <= n; i++)
            if(!visit[i] && map[j][i]!=-1 && (dist[i]==-1 || dist[i]>dist[j]+map[j][i]))
            {
                dist[i] = dist[j] + map[j][i];
                pre[i] = j;
            }
    }
}

int main()
{
    int a, b, l, i, j, Case = 0, flag, v, tmp, tv, ans;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n==0 && m==0)  break;
        memset(map, -1, sizeof(map));
        for(i = 1; i <= n; i++)  map[i][i] = 0;
        for(i = 0; i < m; i++)
        {
            scanf("%d%d%d", &a, &b, &l);
            if(map[a][b]==-1 || map[a][b]>l)
                map[a][b] = map[b][a] = l;
        }
        dijkstra();
        ans = flag = 0;
        v = 1;
        for(i = 1; i <= n; i++)
        {
            if(dist[i] > ans)
            {
                ans = dist[i];
                v = i;
            }
        }
        for(i = 1; i <= n; i++)
            for(j = i+1; j <= n; j++)
                if(pre[i]!=j && pre[j]!=i && map[i][j]!=-1)
                {
                    tmp = abs(dist[i]-dist[j]);
                    if(tmp == map[i][j])  continue;
                    if(max(dist[i], dist[j])+(map[i][j]-tmp-1)/2 >= ans)
                    {
                        ans = max(dist[i], dist[j])+(map[i][j]-tmp-1)/2;
                        flag = 1;
                        v = i;
                        tv = j;
                    }
                }
        printf("System #%d\n", ++Case);
        if(n == 1)
        {
            printf("The last domino falls after 0.0 seconds, at key domino 1.\n\n");
            continue;
        }
        if(flag == 0)  printf("The last domino falls after %d.0 seconds, at key domino %d.\n", ans, v);
        else  printf("The last domino falls after %d.5 seconds, between key dominoes %d and %d.\n", ans, v, tv);
        printf("\n");
    }
    return 0;
}