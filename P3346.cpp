#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;

struct SAM {
    int len,link,cnt;
    int ch[10];
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
    sam[0].cnt;
    memset(sam[0].ch,0,sizeof(sam[0].ch));
    sz=0;
    last=0;
}

void sam_extend(int c) {
    if(sam[last].ch[c] && sam[last].len+1==sam[sam[last].ch[c]].len) {
        last=sam[last].ch[c];
        return;
    }

    int cur=++sz;
    sam[cur].len=sam[last].len+1;
    memset(sam[cur].ch,0,sizeof(sam[cur].ch));
    sam[cur].cnt=1;

    int p=last;
    for(;~p && !sam[p].ch[c];p=sam[p].link)
        sam[p].ch[c]=cur;

    if(!~p) {
        sam[cur].link=0;
    } else {
        int q=sam[p].ch[c];
        if(sam[p].len+1==sam[q].len) {
            sam[cur].link=q;
        } else {
            int clone;
            if(p==last) {
                clone=cur;
            } else {
                clone=++sz;
                sam[cur].link=clone;
            }
            sam[clone]=sam[q];
            sam[clone].len=sam[p].len+1;
            sam[q].link=clone;
            sam[clone].cnt=0;
            if(p==last) sam[clone].cnt=1;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }

    last=cur;
}

int color[MAXN];

struct edge{
    int to,next;
}e[MAXN<<1];

int tot,head[MAXN];

void add(int x,int y) {
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

int dgr[MAXN];

void dfs(int x,int f) {
    int cur=last;
    sam_extend(color[x]);
    for(int p=head[x];p;p=e[p].next) {
        int u=e[p].to;
        if(u==f) continue;
        dfs(u,x);
    }
    last=cur;
}

void solve() {
    int n,c;
    scanf("%d %d", &n, &c);
    for(int i=1;i<=n;i++) scanf("%d", &color[i]);
    tot=0;
    memset(head+1,0,n*sizeof(head[0]));
    memset(dgr+1,0,n*sizeof(dgr[0]));
    for(int i=1;i<n;i++) {
        int f,g;
        scanf("%d %d", &f, &g);
        add(f,g);
        add(g,f);
        dgr[f]++;
        dgr[g]++;
    }
    sam_init();
    for(int i=1;i<=n;i++)
        if(dgr[i]==1) dfs(i,i);
    LL ans=0;
    for(int i=1;i<=sz;i++)
        ans+=sam[i].len-sam[sam[i].link].len;
    printf("%lld\n", ans);
}

int main() {
    int T=1,cas=1;
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}