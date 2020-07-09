#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;

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
}

int tax[MAXN],per[MAXN<<1];
char s[MAXN];
int lcs[MAXN<<1];

void solve() {
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    int len=strlen(s);
    sam_init();
    for(int i=0;i<len;i++) {
        sam_extend(s[i]-'a');
    }

    memset(tax+1,0,len*sizeof(tax[0]));
    for(int i=1;i<=sz;i++) tax[sam[i].len]++;
    for(int i=2;i<=len;i++) tax[i]+=tax[i-1];
    for(int i=1;i<=sz;i++) per[tax[sam[i].len]--]=i;

    memset(lcs,0,(sz+1)*sizeof(lcs[0]));
    for(int i=1;i<=n;i++) {
        scanf("%s", s);
        int len=strlen(s);
        int cur=0,cnt=0;
        for(int j=0;j<len;j++) {
            if(sam[cur].ch[s[j]-'a']) cnt++;
            else {
                while(~cur && !sam[cur].ch[s[j]-'a']) cur=sam[cur].link;
                if(!~cur) cur=0,cnt=0;
                else cnt=sam[cur].len+1;
            }
            cur=sam[cur].ch[s[j]-'a'];
            lcs[cur]=max(lcs[cur],cnt);
        }
    }
    LL ans=0;
    for(int i=sz;i;i--) {
        lcs[per[i]]=min(sam[per[i]].len,lcs[per[i]]);
        lcs[sam[per[i]].link]=max(lcs[sam[per[i]].link],lcs[per[i]]);
        ans+=sam[per[i]].len-max(lcs[per[i]],sam[sam[per[i]].link].len);
    }
    printf("%lld\n", ans);
}

int main() {
    int T=1,cas=1;
    scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}