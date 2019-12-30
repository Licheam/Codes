#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 6005
#define MAXM 9000005

const int inf=0x3f3f3f3f;

using namespace std;

int T,ti,n1,n2,n,s,t,gx[MAXN],gy[MAXN],gs[MAXN];
int tot,head[MAXN];
int lb[MAXN],mat[MAXN],dfn[MAXN];

struct edge{
    int to,next;
}e[MAXM];

void add(int x,int y){
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

bool bfs(){
    memset(lb+1,0,n*sizeof(lb[0]));
    queue<int> q;
    for(int i=1;i<=n1;i++){
        if(!mat[i]){
            lb[i]=1;
            q.push(i);
        }
    }
    int dis=inf;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(!lb[v]){
                lb[v]=lb[u]+1;
                if(!mat[v]) dis=lb[v];
                else if(lb[v]<dis){
                    lb[mat[v]]=lb[v]+1;
                    q.push(mat[v]);
                }
            }
        }
    }
    return dis!=inf;
}

bool dfs(int u,int stamp){
    for(int p=head[u];p;p=e[p].next){
        int v=e[p].to;
        if(dfn[v]!=stamp && lb[v]==lb[u]+1){
            dfn[v]=stamp;
            if(!mat[v] || (lb[mat[v]]==lb[v]+1 && dfs(mat[v],stamp))){
                mat[v]=u;
                mat[u]=v;
                return true;
            }
        }
    }
    return false;
}

int hk(){
    int cnt=0,stamp=0;
    memset(mat+1,0,n*sizeof(mat[0]));
    memset(dfn+1,0,n*sizeof(dfn[0]));
    while(bfs()){
        stamp++;
        for(int i=1;i<=n1;i++){
            if(!mat[i] && dfs(i,stamp)){
                cnt++;
            }
        }
    }
    return cnt;
}

int main(){
    scanf("%d", &T);
    int cas=0;
    while(T--){
        scanf("%d", &ti);
        scanf("%d", &n1);
        for(int i=1;i<=n1;i++){
            scanf("%d %d %d",&gx[i],&gy[i],&gs[i]);
        }
        scanf("%d",&n2);
        n=n1+n2;
        tot=0;
        memset(head+1,0,n*sizeof(head[0]));
        for(int i=1;i<=n2;i++){
            int x,y;
            scanf("%d %d", &x,&y);
            for(int j=1;j<=n1;j++){
                if((gx[j]-x)*(gx[j]-x)+(gy[j]-y)*(gy[j]-y)<=ti*ti*gs[j]*gs[j]){
                    add(j,i+n1);
                }
            }
        }
        printf("Scenario #%d:\n%d\n\n",++cas,hk());
    }
    return 0;
}