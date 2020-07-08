#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;

struct SAM {
    int len,link,cnt;
    int ch[26];
}sam[MAXN<<2];

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

char s[MAXN];

int tax[MAXN],per[MAXN<<1];
int ans[MAXN];

void solve() {
    scanf("%s", s);
    int len=strlen(s);
    sam_init();
    for(int i=0;i<len;i++)
        sam_extend(s[i]-'a');

    memset(tax+1,0,len*sizeof(tax[0]));
    for(int i=1;i<=sz;i++) tax[sam[i].len]++;
    for(int i=2;i<=len;i++) tax[i]+=tax[i-1];
    for(int i=1;i<=sz;i++) per[tax[sam[i].len]--]=i;
    for(int i=sz;i;i--)
        sam[sam[per[i]].link].cnt+=sam[per[i]].cnt;
    sam[0].cnt=0;

    memset(ans+1,0,len*sizeof(ans[0]));
    for(int i=1;i<=sz;i++) {
        ans[sam[i].len]=max(sam[i].cnt,ans[sam[i].len]);
    }
    for(int i=len-1;i;i--) {
        ans[i]=max(ans[i+1],ans[i]);
    }
    for(int i=1;i<=len;i++) {
        printf("%d\n", ans[i]);
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