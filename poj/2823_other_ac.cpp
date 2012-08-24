#include <iostream>
#include <cstdio>
#include <algorithm>
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
#define M 1100010
using namespace std;
struct no{
	int left ,right,max1,min1;
}tree[M<<2];
int a[M];
void build (int l,int r,int i){
	tree[i].left=l;
	tree[i].right=r;
	if(l==r){
	  tree[i].min1=tree[i].max1=a[l];
      return;
	}
    int mid=(l+r)>>1;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
	tree[i].min1=min(tree[i<<1].min1,tree[i<<1|1].min1);
	tree[i].max1=max(tree[i<<1].max1,tree[i<<1|1].max1);
}
int mi,ma;
void  query(int l,int r,int i){
	if(tree[i].left>=l&&tree[i].right<=r){
		mi=min(mi,tree[i].min1);
		ma=max(ma,tree[i].max1);
		return;
	}
	if(tree[i].left==tree[i].right)  return;
	int mid=(tree[i].left+tree[i].right)>>1;
	if(r<=mid)     query(l,r,i<<1);
	else if(l>mid) query(l,r,i<<1|1);
	else query(l,mid,i<<1),query(mid+1,r,i<<1|1);
	
}
int ans[M];
int main(){
	int n,m;
	while(~scanf("%d%d",&n,&m)){
	
		for(int i=1;i<n+1;i++){
			scanf("%d",&a[i]);
		}
		build(1,n,1);
		if(m>=n){
		 mi=M*100,ma=-M*100;
		 query(1,n,1);
		 printf("%d\n%d\n",mi,ma);
		 continue;	
		}

		int j=0;
		for(int i=1;i<=n-m+1;i++){
		 mi=M*100,ma=-M*100;
		 query(i,m+i-1,1);
	 	 printf("%d ",mi);	
		 ans[j]=ma;
		 j++;
		}
		puts("");
		for(int i=0;i<j;i++){
			printf("%d ",ans[i]);
		}
		puts("");
		
	}
}