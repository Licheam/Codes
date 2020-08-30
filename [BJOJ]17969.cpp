/*
    Coded with Leachim's ACM Template.
    No error. No warning~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAXN=2000005;

int tot,head[MAXN];
struct edge{
    int to,next,w;
}e[MAXN<<1];
void add(int x,int y,int z) {
    tot++;
    e[tot].next=head[x];
    e[tot].to=y;
    e[tot].w=z;
    head[x]=tot;
}

int dgr[MAXN];

LL sq[MAXN],sd[MAXN],sn[MAXN];
LL ans=0;

void dfs(int x,int f,int w) {
    if(dgr[x]==1) {
        sn[x]=1;
        sd[x]=w;
        sq[x]=w*w;
        return;
    }
    sd[x]=sq[x]=sn[x]=0;
    for(int p=head[x];p;p=e[p].next) {
        int u=e[p].to;
        if(u==f) continue;
        dfs(u,x,e[p].w);
        ans+=2*sd[x]*sd[u]+sn[u]*sq[x]+sn[x]*sq[u];
        sd[x]+=sd[u];
        sq[x]+=sq[u];
        sn[x]+=sn[u];
    }
    sq[x]+=sn[x]*w*w+2*w*sd[x];
    sd[x]+=sn[x]*w;
}

void solve() {
    int n;
    scanf("%d", &n);
    tot=0;
    memset(head+1,0,n*sizeof(head[0]));
    memset(dgr+1,0,n*sizeof(dgr[0]));
    for(int i=1;i<n;i++) {
        int f,g,w;
        scanf("%d %d %d", &f, &g, &w);
        add(f,g,w);
        add(g,f,w);
        dgr[g]++;
        dgr[f]++;
    }
    int rt=0;
    for(int i=1;i<=n;i++)
        if(dgr[i]>1) {rt=i;break;}
    ans=0;
    dfs(rt,rt,0);
    printf("%lld\n", ans);
}

int main() {
    int T=1,cas=1;(void)(cas);
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}