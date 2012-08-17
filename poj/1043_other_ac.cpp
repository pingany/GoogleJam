#include <cstdio>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
const int NMax=30;
int N,L1,L2,connect[NMax];
bool ok[NMax],sta[NMax];
map<string,int> ID1,ID2;
map<int,string> rev1,rev2;
map<int,bool> State;
bool G[NMax][NMax];
bool DFS(int a) {
    sta[a]=1;
    for(int j=1;j<=N;j++) if(G[a][j]){
        if(!connect[j]) {
            connect[j]=a;
            ok[a]=1;
            return 1;
        }else if(!sta[connect[j]] && DFS(connect[j])) {
            ok[a]=1;
            connect[j]=a;
            return 1;
        }
    }
    return 0;
}
int sth() {
    int ret=0;
    for(int i=1;i<=N;i++) connect[i]=0;
    for(int i=1;i<=N;i++) ok[i]=0;
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) if(G[i][j]){
            if(!connect[j]) {
                connect[j]=i;
                ok[i]=1;
                ret++;
                break;
            }
        }
    }
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) sta[j]=0;
        if(!ok[i] && DFS(i)) ret++;
    }
    return ret;
}
bool cmp(int a,int b) {
    return rev1[a]<rev1[b];
}
int main()
{
    string tmp;
    char buf[NMax],buf2[NMax];
    scanf("%d",&N);
    for(int i=1;i<=N;i++) {
        scanf("%s",buf);
        int len=strlen(buf);tmp.clear();
        for(int j=0;j<len;j++) tmp.push_back(buf[j]);
        ID2[tmp]=++L2;rev2[L2]=tmp;    
    }
    for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) G[i][j]=1;
    while(scanf("%s",buf),(buf[0]!='Q')) {
        scanf("%s",buf2);
        int len=strlen(buf2);tmp.clear();
        for(int i=0;i<len;i++) tmp.push_back(buf2[i]);
        if(buf[0]=='M') {
            int ID=ID2[tmp];
            //printf("%d\n",ID);
            for(int i=1;i<=N;i++) if(!State[i])
                G[i][ID]=0;
            continue;
        }
        if(ID1[tmp]==0) {ID1[tmp]=++L1;rev1[L1]=tmp;}
        int ID=ID1[tmp];
        if(buf[0]=='E') State[ID]=1;
        else if(buf[0]=='L') State[ID]=0;
    }
    //if(-1) puts("YA"); 
    //for(int i=1;i<=N;i++)
    //    for(int j=1;j<=N;j++) if(G[i][j]) 
    //        cout <<rev1[i]<<' '<<rev2[j]<<endl;
    int R[NMax];
    for(int i=1;i<=N;i++) {
        R[i]=-1;
        for(int j=1;j<=N;j++) if(G[i][j]){
            G[i][j]=0;
            int tmp;
            if((tmp=sth())<N) {
                //printf("%d\n",tmp);
                R[i]=j;
                G[i][j]=1;
                break;
            }
            G[i][j]=1;
        }
    }
    int res[NMax];
    for(int i=1;i<=N;i++) res[i]=i;
    sort(res+1,res+N+1,cmp);
    //puts("");
    for(int i=1;i<=N;i++) {
        if(R[res[i]]!=-1) cout <<rev1[res[i]]<<':'<<rev2[R[res[i]]]<<endl;
        else cout <<rev1[res[i]]<<':'<<"???"<<endl;
    }
    getchar(); getchar();
    return 0;
}