#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define MAXN 500005

using namespace std;

int n,k,tot,head[MAXN],girl[MAXN];
LL sum;

struct edge{
    int to,next;
}e[MAXN<<1];

struct node{
    int rt,lc,rc,v,dis;
}lt[MAXN];

void add(int x,int y){
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

int find(int x){
    if(lt[x].rt==x)
    	return x;
    return lt[x].rt=find(lt[x].rt);
}

int merge(int x,int y){
    if(!x || !y) return x+y;
    if(lt[x].v<lt[y].v ||(lt[x].v==lt[y].v && x>y)) swap(x,y);
    lt[x].rc=merge(lt[x].rc,y);
    lt[lt[x].rc].rt=x;
    if(lt[lt[x].lc].dis<lt[lt[x].rc].dis) swap(lt[x].lc,lt[x].rc);
    lt[x].dis=lt[lt[x].rc].dis+1;
    return x;
}

void pop(int x){
    lt[lt[x].lc].rt=lt[x].lc;
    lt[lt[x].rc].rt=lt[x].rc;
    lt[x].rt=merge(lt[x].lc,lt[x].rc);
}

void dfs(int u,int fr){
    lt[u].rt=u;
    lt[u].lc=lt[u].rc=0;
    lt[u].v=lt[fr].v+1;
    lt[u].dis=0;
    int rt=0;
    for(int p=head[u];p;p=e[p].next){
        int v=e[p].to;
        if(v==fr) continue;
        dfs(v,u);
        int rv=find(v);
        rt=merge(rt,rv);
    }
    if(girl[u]){
        merge(u,rt);
        sum+=lt[u].v;
    }
    else if(rt){
        sum+=lt[u].v-lt[rt].v;
        merge(rt,u);
        pop(rt);
    }
    else{
        lt[u].rt=0;
    }
}

int main(){
    scanf("%d %d", &n, &k);
    memset(head+1,0,n*sizeof(head[0]));
    tot=0;
    for(int i=1;i<=n-1;i++){
        int f,g;
        scanf("%d %d", &f, &g);
        add(f,g);
        add(g,f);
    }
    memset(girl+1,0,n*sizeof(girl[0]));
    for(int i=1;i<=k;i++){
        int f;
        scanf("%d", &f);
        girl[f]=1;
    }
    lt[0].rt=0;
    lt[0].dis=0;
    lt[1].v=-1;
    sum=0;
    dfs(1,1);
    printf("%lld\n", sum);
    return 0;
}