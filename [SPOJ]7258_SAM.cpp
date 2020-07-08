#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;

struct SAM {
    int len,link;
    int ch[26];
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
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
            sam[q].link=sam[cur].link=clone;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }

    last=cur;
}

LL dp[MAXN<<1];

LL dfs(int cur) {
    if(dp[cur]) return dp[cur];
    LL res=1;
    for(int i=0;i<26;i++)
        if(sam[cur].ch[i])
            res+=dfs(sam[cur].ch[i]);
    return dp[cur]=res;
}

char s[MAXN];

int tot;

void kth(int k) {
    int cur=0;
    while(k) {
        for(int i=0;i<26;i++) {
            if(!sam[cur].ch[i]) continue;
            if(k>dp[sam[cur].ch[i]]) k-=dp[sam[cur].ch[i]];
            else {
                k--;
                s[tot++]=i+'a';
                cur=sam[cur].ch[i];
                break;
            }
        }
    }
}

void solve() {
    scanf("%s", s);
    int len=strlen(s);
    sam_init();
    for(int i=0;i<len;i++)
        sam_extend(s[i]-'a');
    memset(dp,0,(sz+1)*sizeof(dp[0]));
    dfs(0);
    int q;
    scanf("%d", &q);
    for(int i=1;i<=q;i++) {
        int k;
        scanf("%d", &k);
        tot=0;
        kth(k);
        s[tot]=0;
        printf("%s\n", s);
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