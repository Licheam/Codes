#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define MAXN 100005
#define MAXK 105
#define INF 1e18

using namespace std;

int T,n,k,tot,head[MAXN],siz[MAXN],dgr[MAXN];
LL dp[MAXN][MAXK];//dp：节点u子树内，选择k个的最佳方案

struct edge{
	int v,to,next;
}e[MAXN<<1];

void add(int x,int y,int z){
	tot++;
	e[tot].to=y;
	e[tot].v=z;
	e[tot].next=head[x];
	head[x]=tot;
}

void dfs(int x,int pre){
	dp[x][0]=0;
	for(int i=1;i<=k;i++)
		dp[x][i]=INF;//防止出现INF+INF爆范围
	if(siz[x])
		dp[x][1]=0;

	for(int q=head[x];q;q=e[q].next){
		int u=e[q].to,w=e[q].v;
		if(u==pre) continue;
		dfs(u,x);
		siz[x]+=siz[u];//x子树目前大小
		for(int i=min(k,siz[x]);i;i--){//在目前大小中，x总共要选取i个
			for(int j=min(i,siz[u]);j;j--){//其中有j个在u子树里面
				dp[x][i]=min(dp[x][i],dp[x][i-j]+dp[u][j]+1LL*w*j*(k-j));
			}
		}
	}
}

int main(){
	scanf("%d",&T);
	int cas=0;
	while(T--){
		scanf("%d %d",&n,&k);
		tot=0;
		memset(head+1,0,sizeof(head[0])*n);
		memset(dgr+1,0,sizeof(dgr[0])*n);
		for(int i=1;i<n;i++){
			int f,g,v;
			scanf("%d %d %d", &f, &g, &v);
			add(f,g,v);
			add(g,f,v);
			dgr[f]++;dgr[g]++;
		}
		memset(siz+1,0,sizeof(siz[0])*n);
		for(int i=1;i<=n;i++){
			if(dgr[i]==1)
				siz[i]=1;
		}
		dfs(1,0);
		printf("Case #%d: %lld\n",++cas,dp[1][k]);
	}
	return 0;
}