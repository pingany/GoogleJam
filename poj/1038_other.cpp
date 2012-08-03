//Program, copied from http://poj.org/showmessage?message_id=143300
#include <stdio.h>
#include <string.h>

#define MAX 59049

short a[2][MAX];
bool CouldH[155][11], CouldV[155][11];
int n, m, nBad;
int power[11];

void Init()
{
    int i;
    power[0] = 1;
    for(i=1; i<=10; i++){
        power[i] = power[i-1]*3;
    }
}
void InitCase()
{
    memset(a, 0, sizeof(a));
    memset(CouldH, true, sizeof(CouldH));
    memset(CouldV, true, sizeof(CouldV));
    scanf("%d%d%d", &n, &m, &nBad);
    int i, j, x, y;
    while(nBad --){
        scanf("%d%d", &x, &y);
        for(i=-2; i<=0; i++)
            for(j=-1; j<=0; j++){
                if(x+i >= 0 && y+j > 0)
                    CouldH[x+i][y+j-1] = false;
                if(x+j >= 0 && y+i > 0)
                    CouldV[x+j][y+i-1] = false;
            }
    }
    for(i=0; i<=n; i++){
        CouldH[i][m-1] = false;
        CouldV[i][m-1]=CouldV[i][m-2] = false;
    }
    for(i=0; i<m; i++){
        CouldH[n][i] = CouldH[n-1][i] = false;
        CouldV[n][i] = false;
    }
}

int Code(int a[11]){
    int ret = 0, i;
    for(i=0; i<m; i++)
        ret += a[i]*power[i];
    return ret;
}

int CodeMinus(int a[11]){
    int ret = 0, i;
    for(i=0; i<m; i++)
        if(a[i] > 0)
            ret += (a[i]-1)*power[i];
    return ret;
}

void Decode(int k, int status[11])
{
    for(int i=0; i<m; i++){
        status[i] = k%3;
        k = k/3;
    }
}

void dfs(int i, int j, int status[11], int cnt)
{
    if(j >= m){
        int code = CodeMinus(status);
        if(a[i%2][code] < cnt)
            a[i%2][code] = cnt;
        return ;
    }
    if(CouldH[i][j] && status[j] == 0 && status[j+1] == 0){
        status[j] = status[j+1] = 3;
        dfs(i, j+2, status, cnt+1);
        status[j] = status[j+1] = 0;
    }
    if(CouldV[i][j] && status[j] == 0 && status[j+1] == 0 && status[j+2] == 0){
        status[j] = status[j+1] = status[j+2] = 2;
        dfs(i, j+3, status, cnt+1);
        status[j] = status[j+1] = status[j+2] = 0;
    }
    dfs(i, j+1, status, cnt);
}

void Solve()
{
    int now, i, j, status[11];
    memset(a[0], 0xff, sizeof(a[1]));
a[0][0] = 0;
    for(i=1; i<=n; i++){
        now = i%2;
        memset(a[now], 0xff, sizeof(a[now]));
        for(j=0; j< power[m]; j++){
            if(a[1-now][j] < 0)
                continue;
            Decode(j, status);
            dfs(i, 0, status, a[1-now][j]);
        }
        
    }
    int ans = 0;
    for(i=0; i < power[m]; i++){
        if(ans < a[n%2][i])
            ans = a[n%2][i];
    }
    printf("%d\n", ans);
}

int main()
{
    int nCase;
    scanf("%d", &nCase);
    Init();
    while(nCase--){
        InitCase();
        Solve();
    }
    return 0;
}