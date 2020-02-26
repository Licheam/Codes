#include <bits/stdc++.h>
#define MAXN 55
#define MAXM 20005
using namespace std;

struct node{
	int le,ri;
	int mx,tag;
}sgt[MAXM<<2];

int n,m,k;
int a[MAXN][MAXM],sum[MAXN][MAXM],dp[MAXN][MAXM];

void build(int cur,int l,int r,int x){
	sgt[cur].le=l, sgt[cur].ri=r;
	sgt[cur].tag=0;
	if(l==r-1){
		sgt[cur].mx=dp[x-1][l]+sum[x][l+k-1]-sum[x][max(k-1,l-1)];
	}
	else{
		int le=cur<<1,ri=le+1;
		build(le,l,(l+r)>>1,x);
		build(ri,(l+r)>>1,r,x);
		sgt[cur].mx=max(sgt[le].mx,sgt[ri].mx);
	}
}

void update(int cur){
	int le=cur<<1,ri=le+1;
	sgt[le].mx+=sgt[cur].tag;
	sgt[ri].mx+=sgt[cur].tag;
	sgt[le].tag+=sgt[cur].tag;
	sgt[ri].tag+=sgt[cur].tag;
	sgt[cur].tag=0;
}

void modify(int cur,int l,int r,int del){
	if(l<=sgt[cur].le && sgt[cur].ri<=r){
		sgt[cur].mx+=del;
		sgt[cur].tag+=del;
	}
	else{
		if(sgt[cur].tag) update(cur);
		int le=cur<<1,ri=le+1;
		int mid=(sgt[cur].le+sgt[cur].ri)>>1;
		if(l<mid) modify(le,l,r,del);
		if(r>mid) modify(ri,l,r,del);
		sgt[cur].mx=max(sgt[le].mx,sgt[ri].mx);
	}
}

void solve(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i=1;i<=n;i++){
		sum[i][0]=0;
		for(int j=1;j<=m;j++){
			scanf("%d", &a[i][j]);
			sum[i][j]=sum[i][j-1]+a[i][j];
		}
	}
	for(int j=1;j<=m-k+1;j++)
		dp[1][j]=sum[1][j+k-1]-sum[1][j-1];
	for(int i=2;i<=n;i++){
		build(1,1,m-k+2,i);
		for(int j=1;j<=m-k+1;j++){
			modify(1,j,j+k,-a[i][j+k-1]);
			dp[i][j]=sgt[1].mx+sum[i][j+k-1]-sum[i][j-1];
			modify(1,max(j-k+1,1),j+1,a[i][j]);
		}
	}
	int ans=dp[n][1];
	for(int j=2;j<=m;j++)
		ans=max(ans,dp[n][j]);
	printf("%d\n", ans);
}

int main(){
	int T=1;
	// scanf("%d", &T);
	while(T--){
		solve();
	}
	return 0;
}