#include <bits/stdc++.h>
#define MAXN 100005
#define MAXLN 20
using namespace std;

struct edge{
	int to,next;
}e[MAXN<<1];

int tot,head[MAXN];

void add(int x,int y){
	tot++;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

int dep[MAXN],lgd[MAXN],st[MAXN][MAXLN];

void dfs(int cur,int fa){
	dep[cur]=dep[fa]+1;
	st[cur][0]=fa;
	for(lgd[cur]=1;(1<<lgd[cur])<=dep[cur];lgd[cur]++)
		st[cur][lgd[cur]]=st[st[cur][lgd[cur]-1]][lgd[cur]-1];

	for(int p=head[cur];p;p=e[p].next){
		if(e[p].to==fa) continue;
		dfs(e[p].to,cur);
	}
}

int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=0;dep[x]-dep[y];i++)
		if((dep[x]-dep[y])&(1<<i)) x=st[x][i];
	if(x==y) return x;

	for(int i=lgd[x];i>=0;i--)
		if(st[x][i]!=st[y][i])
			x=st[x][i], y=st[y][i];
	return st[x][0];
}

void solve(){
	int n,q;
	scanf("%d", &n);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<n;i++){
		int f,g;
		scanf("%d %d", &f, &g);
		add(f,g);
		add(g,f);
	}
	dep[0]=0;
	dfs(1,0);
	scanf("%d", &q);
	for(int i=1;i<=q;i++){
		int x,y,a,b,k,ax,ay,ab,bx,by;
		scanf("%d %d %d %d %d", &x, &y, &a, &b, &k);
		ab=dep[a]+dep[b]-2*dep[lca(a,b)];
		if(ab<=k && ((ab-k)&1)==0){
			printf("YES\n");
			continue;
		}
		ax=dep[a]+dep[x]-2*dep[lca(a,x)];
		by=dep[b]+dep[y]-2*dep[lca(b,y)];
		if(ax+by+1<=k && ((ax+by+1-k)&1)==0){
			printf("YES\n");
			continue;
		}
		ay=dep[a]+dep[y]-2*dep[lca(a,y)];
		bx=dep[b]+dep[x]-2*dep[lca(b,x)];
		if(ay+bx+1<=k && ((ay+bx+1-k)&1)==0){
			printf("YES\n");
			continue;
		}
		printf("NO\n");
	}
}

int main(){
	int T=1;
	// scanf("%d", &T);
	while(T--){
		solve();
	}
	return 0;
}