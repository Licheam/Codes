#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define MAXN 100005

struct SAM {
    int len,link,cnt;
    int ch[26];
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
    sam[0].cnt=0;
    memset(sam[0].ch,0,sizeof(sam[0].ch));
    sz=0;
    last=0;
}

void sam_extend(int c) {
    int cur=++sz;
    sam[cur].len=sam[last].len+1;
    memset(sam[cur].ch,0,sizeof(sam[cur].ch));

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
            sam[clone].cnt=0;
            sam[q].link=sam[cur].link=clone;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }
    
    last=cur;
    sam[cur].cnt=1;
}

int len,len0;
char s[MAXN],s0[MAXN];
int tax[MAXN],per[MAXN<<1];
int ans;

void dfs(int cur,int l,int md) {
    if(l==len) {
        ans+=sam[cur].cnt;
        return;
    }

    for(int i=0;i<26;i++) {
        if(sam[cur].ch[i]) {
            if(s[l]==i+'A') dfs(sam[cur].ch[i],l+1,md);
            else if(md<3) dfs(sam[cur].ch[i],l+1,md+1);
        }
    }
}

void solve() {
    scanf("%s", s0);
    scanf("%s", s);
    len=strlen(s);
    len0=strlen(s0);
    sam_init();
    for(int i=0;i<len0;i++)
        sam_extend(s0[i]-'A');
    memset(tax+1,0,len0*sizeof(tax[0]));
    for(int i=1;i<=sz;i++) tax[sam[i].len]++;
    for(int i=2;i<=len0;i++) tax[i]+=tax[i-1];
    for(int i=1;i<=sz;i++) per[tax[sam[i].len]--]=i;
    for(int i=sz;i;i--) sam[sam[per[i]].link].cnt+=sam[per[i]].cnt;
    ans=0;
    dfs(0,0,0);
    printf("%d\n", ans);
}

int main() {
    int T=1;
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}