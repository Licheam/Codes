#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;

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

    sam[cur].cnt=1;
    last=cur;
}

LL dp[MAXN<<1];

LL dfs(int cur) {
    if(dp[cur]) return dp[cur];
    LL res=sam[cur].cnt;
    for(int i=0;i<26;i++)
        if(sam[cur].ch[i])
            res+=dfs(sam[cur].ch[i]);
    return dp[cur]=res;
}

char s[MAXN];

int slen;

void kth(int k) {
    int cur=0;
    if(k>dp[0]) return;
    while(k) {
        for(int i=0;i<26;i++) {
            if(!sam[cur].ch[i]) continue;
            if(k>dp[sam[cur].ch[i]])
                k-=dp[sam[cur].ch[i]];
            else{
                k=max(0,k-sam[sam[cur].ch[i]].cnt);
                s[slen++]=i+'a';
                cur=sam[cur].ch[i];
                break;
            }
        }
    }
}

int tax[MAXN],per[MAXN<<1];

void solve() {
    scanf("%s", s);
    int len=strlen(s);
    sam_init();
    for(int i=0;i<len;i++)
        sam_extend(s[i]-'a');
    int t,k;
    scanf("%d %d", &t, &k);
    if(t) {
        memset(tax+1,0,len*sizeof(tax[0]));
        for(int i=1;i<=sz;i++) tax[sam[i].len]++;
        for(int i=2;i<=len;i++) tax[i]+=tax[i-1];
        for(int i=1;i<=sz;i++) per[tax[sam[i].len]--]=i;
        for(int i=sz;i>=1;i--)
            sam[sam[per[i]].link].cnt+=sam[per[i]].cnt;
        sam[0].cnt=0;
    } else {
        for(int i=1;i<=sz;i++)
            sam[i].cnt=1;
    }
    memset(dp,0,(sz+1)*sizeof(dp[0]));
    dfs(0);
    slen=0;
    kth(k);n
    s[slen]=0;
    if(!slen) printf("-1\n");
    else printf("%s\n", s);
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