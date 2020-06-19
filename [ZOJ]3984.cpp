#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int inf=0x3f3f3f3f;
#define MAXN 100005

struct edge{
    int to,next;
}e[MAXN<<1];

int tot,head[MAXN],dgr[MAXN],fa[MAXN],siz[MAXN];
bool flag[MAXN];

void add(int x, int y) {
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

vector<int> va[MAXN];

int find(int x){
    if(fa[x]==x)return x;
    else return fa[x]=find(fa[x]);
}

void join(int x,int y){
    int rx=find(x),ry=find(y);
    if(rx!=ry) {
        fa[rx]=ry;
        siz[ry]+=siz[rx];
    }
    
}

set<int> s[MAXN];

void solve() {
    int n,m;
    scanf("%d %d", &n, &m);
    tot=0;
    memset(head+1,0,n*sizeof(head[0]));
    memset(dgr+1,0,n*sizeof(dgr[0]));
    for(int i=1;i<=n;i++) fa[i]=i, siz[i]=1;
    for(int i=1;i<=m;i++) {
        int f,g;
        scanf("%d %d", &f, &g);
        add(f,g);
        add(g,f);
        dgr[g]++;
        dgr[f]++;
    }
    vector<pair<int,int>> v;
    for(int i=1;i<=n;i++)
        v.push_back(make_pair(dgr[i],i));
    sort(v.begin(), v.end());
    for(int i=1;i<=n;i++) s[i].clear();
    vector<int> ans;
    memset(flag+1,0,n*sizeof(flag[0]));
    for(auto pr:v) {
        int u=pr.second;
        ans.push_back(u);
        flag[u]=1;
        int cnt=0;
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(flag[v] && dgr[v]<=dgr[u]){
                s[u].insert(find(v));
                cnt++;
            }
        }
        for(int x:s[u]) {
            cnt-=siz[x];
            join(x,u);
        }
        if(cnt){
            printf("No\n");
            return;
        }
    }

    printf("Yes\n");
    for(int x:ans){
        printf("%d %lu ", x,s[x].size());
        for(int y:s[x]){
            printf("%d ", y);
        }
        puts("");
    }
}

int main() {
    int T=1;
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}