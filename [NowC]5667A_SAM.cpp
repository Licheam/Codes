/*
    Coded with Leachim's ACM Template.
    No error. No warning~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAXN=1000005;
const int MOD=998244353;

struct SAM {
    int len,link;
    int cnt,tag;
    int times;
    int next;
    int ch[26];
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
    sam[0].cnt=0;
    sam[0].tag=0;
    sam[0].next=-1;
    sam[0].times=0;
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
    sam[cur].cnt=0;
    sam[cur].tag=0;
    sam[cur].next=-1;
    sam[cur].times=0;

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
            sam[clone].times=0;
            sam[clone].tag=0;
            sam[q].link=clone;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }

    last=cur;
}

char s[MAXN<<1];
int sp[MAXN];
int tax[MAXN<<1],per[MAXN<<1];
int cnt[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    sp[1]=0;
    for(int i=1;i<=n;i++) {
        scanf("%s", s+sp[i]+1);
        sp[i+1]=sp[i]+1+(int)strlen(s+sp[i]+1);
    }

    sam_init();
    for(int i=1;i<=n;i++) {
        last=0;
        for(int j=sp[i]+1,k=-1;j<sp[i+1];j++) {
            sam_extend(s[j]-'a');
            while(~k && sam[sam[k].ch[s[j]-'a']].tag!=i)
                k=sam[k].next;
            if(!~k) k=0;
            else k=sam[k].ch[s[j]-'a'];
            sam[last].next=k;
            sam[last].tag=i;
        }
        sam[last].times++;
    }
    
    memset(tax+1,0,sz*sizeof(tax[0]));
    for(int i=1;i<=sz;i++) tax[sam[i].len]++;
    for(int i=2;i<=sz;i++) tax[i]+=tax[i-1];
    for(int i=1;i<=sz;i++) per[tax[sam[i].len]--]=i;
    for(int i=sz;i;i--) sam[sam[per[i]].link].times+=sam[per[i]].times;

    for(int i=1;i<=n;i++) {
        int cur=0;
        for(int j=sp[i]+1;j<sp[i+1];j++) {
            cur=sam[cur].ch[s[j]-'a'];
            sam[cur].cnt=(sam[cur].cnt+sam[cur].times)%MOD;
            if(sam[cur].next)
                sam[sam[cur].next].cnt=(sam[sam[cur].next].cnt-sam[cur].times+MOD)%MOD;
        }
    }

    LL ans=0;
    for(int i=1;i<=sz;i++){
        ans=(ans+1LL*sam[i].cnt*sam[i].len%MOD*sam[i].len%MOD)%MOD;;
    }
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