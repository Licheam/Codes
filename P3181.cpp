#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;

struct SAM {
    int len,link,cnt[2];
    int ch[26];
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
    memset(sam[0].cnt,0,sizeof(sam[0].cnt));
    memset(sam[0].ch,0,sizeof(sam[0].ch));
    sz=0;
    last=0;
}

void sam_extend(int c,int id) {
    if(sam[last].ch[c] && sam[last].len+1==sam[sam[last].ch[c]].len) {
        last=sam[last].ch[c];
        sam[last].cnt[id]++;
        return;
    }

    int cur=++sz;
    sam[cur].len=sam[last].len+1;
    memset(sam[cur].ch,0,sizeof(sam[cur].ch));
    memset(sam[cur].cnt,0,sizeof(sam[cur].cnt));
    sam[cur].cnt[id]=1;

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
            memset(sam[clone].cnt,0,sizeof(sam[clone].cnt));
            if(p==last) sam[clone].cnt[id]=1;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }

    last=cur;
}

char s[MAXN];

int tax[MAXN],per[MAXN<<1];

void solve() {
    sam_init();
    scanf("%s", s);
    int len1=strlen(s);
    for(int i=0;i<len1;i++)
        sam_extend(s[i]-'a',0);
    scanf("%s", s);
    int len2=strlen(s);
    last=0;
    for(int i=0;i<len2;i++)
        sam_extend(s[i]-'a',1);

    memset(tax+1,0,max(len1,len2)*sizeof(tax[0]));
    for(int i=1;i<=sz;i++) tax[sam[i].len]++;
    for(int i=2;i<=max(len1,len2);i++) tax[i]+=tax[i-1];
    for(int i=1;i<=sz;i++) per[tax[sam[i].len]--]=i;

    LL ans=0;
    for(int i=sz;i;i--) {
        sam[sam[per[i]].link].cnt[0]+=sam[per[i]].cnt[0];
        sam[sam[per[i]].link].cnt[1]+=sam[per[i]].cnt[1];
        ans+=1LL*sam[per[i]].cnt[0]*sam[per[i]].cnt[1]*(sam[per[i]].len-sam[sam[per[i]].link].len);
    }
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