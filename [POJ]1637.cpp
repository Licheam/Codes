#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>
#define MAXN 205
#define MAXM 1205

const int inf=1e9;

using namespace std;

struct edge{
    int to,next,cf;
}e[MAXM<<1];

int T,n,m,s,t,tot,head[MAXN],cur[MAXN],lb[MAXN],dgr[MAXN],fa[MAXN];//出-入

void add(int x,int y,int z){
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    e[tot].cf=z;
    head[x]=tot;
}

int find(int x){
    if(fa[x]==x)
        return x;
    return fa[x]=find(fa[x]);
}

void join(int x,int y){
    fa[find(x)]=find(y);
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
    if(u==t) return lim;
    int used=0;
    for(int &p=cur[u];p;p=e[p].next){
        int v=e[p].to;
        if(e[p].cf && lb[v]==lb[u]+1){
            int rest=dfs(v,min(e[p].cf,lim-used));
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
        scanf("%d %d",&n,&m);
        memset(dgr+1,0,n*sizeof(dgr[0]));
        memset(head+1,0,(n+2)*sizeof(head[0]));
        tot=1;
        for(int i=1;i<=n;i++) fa[i]=i;
        for(int i=1;i<=m;i++){
            int f,g,d;
            scanf("%d %d %d", &f, &g, &d);
            join(f,g);
            dgr[f]++,dgr[g]--;
            if(!d){
                add(f,g,1);
                add(g,f,0);
            }
        }
        s=n+1,t=n+2;
        bool imp=false;
        int rt=find(1),mxf=0;
        for(int i=1;i<=n;i++){
            if(find(i)!=rt || dgr[i]&1){
                imp=true;
                break;
            }
            mxf+=abs(dgr[i])>>1;
            if(dgr[i]>0){
                add(s,i,dgr[i]>>1);
                add(i,s,0);
            }
            else if(dgr[i]<0){
                add(i,t,(-dgr[i])>>1);
                add(t,i,0);
            }
        }
        n+=2,mxf>>=1;
        if(imp || dinic()!=mxf)
            printf("impossible\n");
        else
            printf("possible\n");
    }
    return 0;
}