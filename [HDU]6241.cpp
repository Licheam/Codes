#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define MAXN 100005

struct edge {
    int to,next;
}e[MAXN<<1];

int tot,head[MAXN];

void add(int x,int y) {
    tot++;
    e[tot].next=head[x];
    e[tot].to=y;
    head[x]=tot;
}

int a[MAXN],b[MAXN],le[MAXN],ri[MAXN];

bool dfs(int cur,int fr,int x) {
    int l=0,r=1;
    for(int p=head[cur];p;p=e[p].next) {
        int u=e[p].to;
        if(u==fr) continue;
        if(!dfs(u,cur,x)) return false;
        l+=le[u];
        r+=ri[u];
    }
    if(~a[cur]) l=max(l,a[cur]);
    if(~b[cur]) r=min(r,x-b[cur]);
    le[cur]=l;
    ri[cur]=r;
    return l<=r;
}

bool check(int x) {
    if(!dfs(1,1,x)) return false;
    return (le[1]<=x && x<=ri[1]);
}

void solve() {
    int n;
    scanf("%d", &n);
    tot=0;
    memset(head+1,0,n*sizeof(head[0]));
    for(int i=1;i<n;i++) {
        int f,g;
        scanf("%d %d", &f, &g);
        add(f,g);
        add(g,f);
    }
    memset(a+1,-1,n*sizeof(a[0]));
    memset(b+1,-1,n*sizeof(b[0]));
    int A,B;
    scanf("%d", &A);
    for(int i=1;i<=A;i++){
        int x,y;
        scanf("%d %d", &x, &y);
        a[x]=max(a[x],y);
    }
    scanf("%d", &B);
    for(int i=1;i<=B;i++){
        int x,y;
        scanf("%d %d", &x, &y);
        b[x]=max(b[x],y);
    }
    int l=0,r=n;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    if(check(l)) printf("%d\n", l);
    else printf("%d\n", -1);
}

int main() {
    int T=1;
    scanf("%d", &T);
    while(T--){
        solve();
    }
    return 0;
}