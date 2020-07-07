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

LL ans;

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
    
    ans+=sam[cur].len-sam[sam[cur].link].len;
}

char s[MAXN];
LL dp[MAXN<<1];

LL dfs(int cur) {
    if(dp[cur]) return dp[cur];
    LL res=1;
    for(int i=0;i<26;i++)
        if(sam[cur].ch[i])
            res+=dfs(sam[cur].ch[i]);
    return dp[cur]=res;
}

void solve() {
    scanf("%s", s);
    int len=strlen(s);
    sam_init();
    ans=0;
    for(int i=0;i<len;i++)
        sam_extend(s[i]-'a');
    // memset(dp,0,(sz+1)*sizeof(dp[0]));
    printf("%lld\n", ans);
}

int main() {
    srand(0);

    int T=1,cas=1;
    scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}