#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <utility>
#define MAXN 105
#define MAXND 3005
#define MAXM 4005

const int inf=1e9;

using namespace std;

int n,m,cnt,fst[MAXN];
int tot,head[MAXND],cur[MAXND],lb[MAXND];
int s,t;
map<int,int> mp[MAXN];

struct edge{
    int to,next,cf;
}e[MAXM<<1];

void add(int x,int y,int z){
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    e[tot].cf=z;
    head[x]=tot;
}

bool bfs(){
    memset(lb+1,0,cnt*sizeof(lb[0]));
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
        for(int i=1;i<=cnt;i++) cur[i]=head[i];
        flow+=dfs(s,inf);
    }
    return flow;
}

int main(){
    scanf("%d %d", &n, &m);
    cnt=0;
    for(int i=1;i<=n;i++){
        int t;
        scanf("%d", &t);
        fst[i]=cnt;
        for(int j=2;j<=sqrt(t+0.5);j++){
            if(!(t%j)){
                mp[i].insert(make_pair(j,1));
                for(t/=j;!(t%j);t/=j){
                    mp[i][j]++;
                }
            }
        }
        if(t>1) mp[i].insert(make_pair(t,1));
        cnt+=mp[i].size();
    }
    s=cnt+1,t=cnt+2;
    cnt+=2;
    tot=1;
    memset(head+1,0,cnt*sizeof(head[0]));
    for(int i=1;i<=n;i++){
        auto it=mp[i].begin();
        for(int j=1;it!=mp[i].end();j++,it++){
            if(i&1){
                add(s,fst[i]+j,it->second);
                add(fst[i]+j,s,0);
            }
            else{
                add(fst[i]+j,t,it->second);
                add(t,fst[i]+j,0);
            }
        }
    }
    for(int i=1;i<=m;i++){
        int f,g;
        scanf("%d %d", &f, &g);
        if(g&1) swap(f,g);
        auto fi=mp[f].begin(),gi=mp[g].begin();
        for(int fj=1,gj=1;fi!=mp[f].end() && gi!=mp[g].end();fi++,fj++){
            while(gi!=mp[g].end() && fi->first>gi->first)
                gi++,gj++;
            if(fi->first==gi->first){
                add(fst[f]+fj,fst[g]+gj,min(fi->second,gi->second));
                add(fst[g]+gj,fst[f]+fj,0);
            }
        }
    }
    printf("%d\n", dinic());
    return 0;
}