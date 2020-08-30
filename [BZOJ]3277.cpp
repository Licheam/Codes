#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;

struct SAM {
    int len,link,times;
    int ch[26];
    int tag;
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
    sam[0].times=0;
    sam[0].tag=0;
    memset(sam[0].ch,0,sizeof(sam[0].ch));
    sz=0;
    last=0;
}

void sam_extend(int c,int stamp) {
    if(sam[last].ch[c] && sam[last].len+1==sam[sam[last].ch[c]].len) {
        last=sam[last].ch[c];
        for(int cur=last;cur && sam[cur].tag!=stamp;cur=sam[cur].link) {
            sam[cur].tag=stamp;
            sam[cur].times++;
        }
        return;
    }

    int cur=++sz;
    sam[cur].len=sam[last].len+1;
    memset(sam[cur].ch,0,sizeof(sam[cur].ch));
    sam[cur].times=0;
    sam[cur].tag=0;

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
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }

    last=cur;
    for(;cur && sam[cur].tag!=stamp;cur=sam[cur].link) {
        sam[cur].times++;
        sam[cur].tag=stamp;
    }
}

char s[MAXN];
int sp[MAXN];

int tax[MAXN<<1],per[MAXN<<1];

LL dp[MAXN<<1];

void solve() {
    int n,k;
    scanf("%d %d", &n, &k);
    sam_init();
    sp[1]=0;
    for(int i=1;i<=n;i++) {
        last=0;
        scanf("%s", s+sp[i]);
        int len=strlen(s+sp[i]);
        for(int j=0;j<len;j++)
            sam_extend(s[sp[i]+j]-'a',i);
        sp[i+1]=sp[i]+len;
    }

    memset(tax+1,0,sz*sizeof(tax[0]));
    for(int i=1;i<=sz;i++) tax[sam[i].len]++;
    for(int i=2;i<=sz;i++) tax[i]+=tax[i-1];
    for(int i=1;i<=sz;i++) per[tax[sam[i].len]--]=i;

    memset(dp,0,(sz+1)*sizeof(dp[0]));
    for(int i=1;i<=sz;i++) {
        if(sam[per[i]].link) {
            dp[per[i]]=dp[sam[per[i]].link];
            if(sam[sam[per[i]].link].times>=k)
                dp[per[i]]+=sam[sam[per[i]].link].len-sam[sam[sam[per[i]].link].link].len;
        }
    }
    for(int i=1;i<=n;i++) {
        LL ans=0;
        int cur=0,cnt=0;
        for(int j=sp[i];j<sp[i+1];j++) {
            if(sam[cur].ch[s[j]-'a']) cnt++;
            else {
                while(~cur && !sam[cur].ch[s[j]-'a']) cur=sam[cur].link;
                if(!~cur) cur=0,cnt=0;
                else cnt=sam[cur].len+1;
            }
            cur=sam[cur].ch[s[j]-'a'];
            ans+=dp[cur];
            if(cur && sam[cur].times>=k)
                ans+=cnt-sam[sam[cur].link].len;
        }
        printf("%lld ", ans);
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