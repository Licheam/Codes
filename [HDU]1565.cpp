#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 3025
#define MAXM 20005

const int inf=0x3f3f3f3f;

using namespace std;

struct edge{
    int to,cf,next;
}e[MAXM<<1];

const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
int n,s,t,tot,head[MAXN],lb[MAXN],cur[MAXN],sum;

void add(int x,int y,int z){
    tot++;
    e[tot].cf=z;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

bool label_vertex(){//BFS
    memset(lb+1,0,(n*n+2)*sizeof(lb[0]));
    queue<int> q;
    lb[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(e[p].cf && !lb[v]){
                lb[v]=lb[u]+1;
                q.push(v);
                if(v==t) return true;
            }
        }
    }
    return false;
}

int multi_augment(int u,int lim){
    if(u==t) return lim;
    int used=0;
    for(int& p=cur[u];p;p=e[p].next){
        int v=e[p].to;
        if(e[p].cf && lb[v]==lb[u]+1){
            int rest=multi_augment(v,min(lim-used,e[p].cf));
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
    while(label_vertex()){
        for(int i=1;i<=(n*n+2);i++) cur[i]=head[i];
        flow+=multi_augment(s,inf);
    }
    return flow;
}

int main(){
    while(~scanf("%d", &n)){
        tot=1;
        memset(head+1,0,(n*n+2)*sizeof(head[0]));
        s=n*n+1;t=n*n+2;
        sum=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int w;
                scanf("%d", &w);
                sum+=w;
                if((i&1)^(j&1)){
                    add((i-1)*n+j,t,w);
                    add(t,(i-1)*n+j,0);
                }
                else{
                    add(s,(i-1)*n+j,w);
                    add((i-1)*n+j,s,0);
                    for(int k=0;k<4;k++){
                        int x=i+dx[k],y=j+dy[k];
                        if(1<=x && x<=n && 1<=y && y<=n){
                            add((i-1)*n+j,(x-1)*n+y,inf);
                            add((x-1)*n+y,(i-1)*n+j,0);
                        }
                    }
                }
            }
        }
        printf("%d\n", sum-dinic());
    }
    return 0;
}