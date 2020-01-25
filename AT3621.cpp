#include <bits/stdc++.h>
#define MAXN 100005

const int inf=0x3f3f3f3f;

using namespace std;

struct edge{
	int next,to,v;
}e[MAXN<<1];

int n,tot,head[MAXN],dist[MAXN];
bool vis[MAXN];

void add(int x,int y,int z){
	tot++;
	e[tot].to=y;
	e[tot].v=z;
	e[tot].next=head[x];
	head[x]=tot;
}

void bfs(){
	memset(dist,inf,n*sizeof(dist[0]));
	memset(vis,0,n*sizeof(vis[0]));
	deque<int> q;
	dist[1]=1;
	q.push_back(1);
	while(!q.empty()){
		int u=q.front();q.pop_front();
		if(vis[u]) continue;
		vis[u]=1;
		for(int p=head[u];p;p=e[p].next){
			int v=e[p].to;
			if(dist[v]>dist[u]+e[p].v){
				dist[v]=dist[u]+e[p].v;
				if(e[p].v) q.push_back(v);
				else q.push_front(v);
			}
		}
	}
}

int main(){
	scanf("%d", &n);
	tot=0;
	memset(head,0,n*sizeof(head[0]));
	for(int i=1;i<=n-1;i++){
		add(i,(i+1)%n,1);
		add(i,i*10%n,0);
	}
	bfs();
	printf("%d\n",dist[0]);
	return 0;
}