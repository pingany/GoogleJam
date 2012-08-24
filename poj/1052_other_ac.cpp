#include <cstdio>
using namespace std;
const int NMax=25;
int N;
char A[3][8][NMax][NMax];
bool cube[NMax][NMax][NMax],fw[NMax][NMax][NMax];
void DFS(int x,int y,int z)
{
    fw[x][y][z]=1;
    if(x+1<N && !fw[x+1][y][z] && cube[x+1][y][z]) DFS(x+1,y,z);
    if(x>0 && !fw[x-1][y][z] && cube[x-1][y][z]) DFS(x-1,y,z);
    if(y+1<N && !fw[x][y+1][z] && cube[x][y+1][z]) DFS(x,y+1,z);
    if(y>0 && !fw[x][y-1][z] && cube[x][y-1][z]) DFS(x,y-1,z);
    if(z+1<N && !fw[x][y][z+1] && cube[x][y][z+1]) DFS(x,y,z+1);
    if(z>0 && !fw[x][y][z-1] && cube[x][y][z-1]) DFS(x,y,z-1);
}
bool con()
{
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) for(int k=0;k<N;k++)
        fw[i][j][k]=0;
    for(int i=0;i<N;i++) for(int j=0;j<N;j++)
        if(!fw[0][i][j] && cube[0][i][j])
            DFS(0,i,j);
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) for(int k=0;k<N;k++)
        if(!fw[i][j][k] && cube[i][j][k]) 
			return 0;
    //puts("Connect OK");
    return 1;
}
bool ThreeV(int i,int j,int k)
{
    for(int x=0;x<N;x++) for(int y=0;y<N;y++)
        if(A[0][i][x][y]=='X')
        {
            bool flag2=0;
            for(int f=0;f<N;f++) if(cube[x][y][f]==1) {
                flag2=1;
                break;
            }
            if(flag2==0) return 0;
        }
    for(int x=0;x<N;x++) for(int y=0;y<N;y++)
        if(A[1][j][x][y]=='X')
        {
            bool flag2=0;
            for(int f=0;f<N;f++) if(cube[f][x][y]==1) {
                flag2=1;
                break;
            }
            if(flag2==0) return 0;
        }
    for(int x=0;x<N;x++) for(int y=0;y<N;y++)
        if(A[2][k][x][y]=='X')
        {
            bool flag2=0;
            for(int f=0;f<N;f++) if(cube[x][f][y]==1) {
                flag2=1;
                break;
            }
            if(flag2==0) return 0;
        }
    //puts("Three View OK");
    return 1;
}
int main()
{
    //FILE *fout=fopen("a.txt","w");
    int T=0;
    while(scanf("%d",&N),N) {
        T++;
        for(int I=0;I<3;I++)
            for(int i=0;i<N;i++)
                scanf("%s",A[I][0][i]);
        //for(int I=0;I<3;I++)
        //    for(int i=0;i<N;i++)
        //        printf("%s\n",A[I][0][i]);
        for(int I=0;I<3;I++) {
            for(int i=1;i<4;i++)
                for(int x=0;x<N;x++)
                    for(int y=0;y<N;y++)
                        A[I][i][x][y]=A[I][i-1][N-y-1][x];
            //puts("Here");
            for(int i=4;i<8;i++)
                for(int x=0;x<N;x++)
                    for(int y=0;y<N;y++)
                        A[I][i][x][y]=A[I][i-4][x][N-y-1];
            //for(int i=0;i<8;i++) {
            //    for(int x=0;x<N;x++) {
            //        printf("%s",A[I][i][x]);
            //        puts("");
            //    }
            //}
        }
        bool flag=0;
        for(int i=0;i<8 && !flag;i++) for(int j=0;j<8 && !flag;j++) for(int k=0;k<8 && !flag;k++)
        {
            for(int i1=0;i1<N;i1++) for(int j1=0;j1<N;j1++) for(int k1=0;k1<N;k1++)
                cube[i1][j1][k1]=1;
            for(int x=0;x<N;x++) for(int y=0;y<N;y++)
                if(A[0][i][x][y]=='-')
                    for(int f=0;f<N;f++)
                        cube[x][y][f]=0;
            for(int x=0;x<N;x++) for(int y=0;y<N;y++)
                if(A[1][j][x][y]=='-')
                    for(int f=0;f<N;f++)
                        cube[f][x][y]=0;
            for(int x=0;x<N;x++) for(int y=0;y<N;y++)
                if(A[2][k][x][y]=='-')
                    for(int f=0;f<N;f++)
                        cube[x][f][y]=0;
            //for(int i1=0;i1<N;i1++) {
            //    for(int j1=0;j1<N;j1++) {
            //        for(int k1=0;k1<N;k1++)
            //            printf("%d",cube[i1][j1][k1]);
            //        puts("");
            //    }
            //    puts("");
            //}
            //while(1);
            if(con() && ThreeV(i,j,k)) {
                flag=1;
                //for(int i1=0;i1<N;i1++) {
                //    for(int j1=0;j1<N;j1++) {
                //        for(int k1=0;k1<N;k1++)
                //            printf("%d",cube[i1][j1][k1]);
                //        puts("");
                //    }
                //    puts("");
                //}
                break;
            }
        }
        printf("Data set %d: ",T);
        if(flag) puts("Valid set of patterns");
        else puts("Impossible combination");
    }
    getchar();getchar();getchar();getchar();getchar();getchar();
    return 0;
}