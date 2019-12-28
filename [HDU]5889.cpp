#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <utility>
#define MAXN 1005
#define MAXM 10005

const int inf=0x3f3f3f3f;

using namespace std;

int T,n,m,s,t,lb[MAXN];
int dis[MAXN],vis[MAXN];
int f[MAXM],g[MAXM],w[MAXM];
int tot,head[MAXN],cur[MAXN];
vector<int> vt[MAXN];

struct edge{
    int to,next,cf;
}e[MAXM<<1];

void add(int x,int y,int z){
    tot++;
    e[tot].to=y;
    e[tot].cf=z;
    e[tot].next=head[x];
    head[x]=tot;
}

void djikstra(){
    memset(dis+1,inf,n*sizeof(dis[0]));
    memset(vis+1,0,n*sizeof(vis[0]));
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    dis[s]=0;
    q.push(make_pair(dis[s],s));
    while(!q.empty()){
        int u=q.top().second;q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int v:vt[u]){
            if(dis[v]>dis[u]+1){
                dis[v]=dis[u]+1;
                q.push(make_pair(dis[v],v));
            }
        }
    }
}

bool bfs(){
    memset(lb+1,0,n*sizeof(lb[0]));
    queue<int> q;
    lb[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(!lb[v] && e[p].cf){
                lb[v]=lb[u]+1;
                q.push(v);
                if(v==t) return true;
            }
        }
    }
    return false;
}

int dfs(int u,int lim){
    if(u==t || lim==0) return lim;
    int used=0;
    for(int& p=cur[u];p;p=e[p].next){
        int v=e[p].to;
        if(lb[v]==lb[u]+1 && e[p].cf){
            int rest=dfs(v,min(lim-used,e[p].cf));
            used+=rest;
            e[p].cf-=rest;
            e[p^1].cf+=rest;
            if(used==lim) break;
        }
    }
    return used;
}

int dinic(){
    int flow=0;
    while(bfs()){
        for(int i=1;i<=n;i++) cur[i]=head[i];
        flow+=dfs(s,inf);
    }
    return flow;
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &n, &m);
        for(int i=1;i<=n;i++) vt[i].clear();
        for(int i=1;i<=m;i++){
            scanf("%d %d %d", &f[i], &g[i], &w[i]);
            vt[f[i]].push_back(g[i]);
            vt[g[i]].push_back(f[i]);
        }
        s=1;t=n;
        djikstra();
        tot=1;
        memset(head+1,0,n*sizeof(head[0]));
        for(int i=1;i<=m;i++){
            if(dis[f[i]]+1==dis[g[i]]){
                add(f[i],g[i],w[i]);
                add(g[i],f[i],0);
            }
            else if(dis[g[i]]+1==dis[f[i]]){
                add(g[i],f[i],w[i]);
                add(f[i],g[i],0);
            }
        }
        printf("%d\n", dinic());
    }
    return 0;
}