#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;

struct SAM {
    int len,link;
    map<int,int> ch;
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
    sam[0].ch.clear();
    sz=0;
    last=0;
}

LL ans;

void sam_extend(int c) {
    int cur=++sz;
    sam[cur].len=sam[last].len+1;
    sam[cur].ch.clear();

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
            int clone=++sz;
            sam[clone]=sam[q];
            sam[clone].len=sam[p].len+1;
            sam[q].link=sam[cur].link=clone;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }

    last=cur;

    ans+=sam[cur].len-sam[sam[cur].link].len;
}

int a[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    sam_init();
    ans=0;
    for(int i=1;i<=n;i++){
        sam_extend(a[i]);
        printf("%lld\n", ans);
    }
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