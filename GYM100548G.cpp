#include <bits/stdc++.h>
#define MAXN 200005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;

int r[MAXN<<1],mxp[MAXN];
char st[MAXN<<1];

void manacher(char *s){
    int len=strlen(s);
    for(int i=1;i<=len;i++) mxp[i]=1;
    st[0]='$';
    for(int i=0;i<len;i++){
        st[i<<1|1]='#';
        st[(i+1)<<1]=s[i];
    }
    len=len<<1|1;
    st[len]='#';
    st[len+1]='*';
    r[1]=1;
    for(int i=2,mid=1;i<=len;i++){
        r[i]=min(mid+r[mid]-i,r[2*mid-i]);
        for(;st[i-r[i]]==st[i+r[i]];r[i]++) {
            if((i+r[i])%2==0) mxp[(i+r[i])/2-1]=max(mxp[(i+r[i])/2-1],r[i]-1);
        }
        if(i+r[i]>mid+r[mid]) mid=i;
        mxp[(i+r[i])/2-1]=max(mxp[(i+r[i])/2-1],r[i]-1);
    }
}

struct SAM {
    int len,link;
    LL cnt;
    int ch[26];
}sam[MAXN<<1];

int sz,last;
int plen[MAXN<<1];

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
            sam[q].link=sam[cur].link=clone;
            sam[clone].cnt=0;
            if(plen[q]<=sam[clone].len) plen[clone]=plen[q],plen[q]=0;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }

    last=cur;
    sam[cur].cnt=1;
}

char s[MAXN];
int tax[MAXN],per[MAXN<<1];



void solve() {
    scanf("%s", s);
    manacher(s);
    int len=strlen(s);
    memset(plen,0,sizeof(plen));
    sam_init();
    for(int i=0;i<len;i++){
        sam_extend(s[i]-'a');
        if(mxp[i+1]>sam[sam[last].link].len){
            plen[last]=mxp[i+1];
        }
    }
    memset(tax+1,0,len*sizeof(tax[0]));
    for(int i=1;i<=sz;i++) tax[sam[i].len]++;
    for(int i=2;i<=len;i++) tax[i]+=tax[i-1];
    for(int i=1;i<=sz;i++) per[tax[sam[i].len]--]=i;
    for(int i=sz;i;i--)
        sam[sam[per[i]].link].cnt+=sam[per[i]].cnt;

    sam[0].cnt=0;
    for(int i=1;i<=sz;i++){
        sam[per[i]].cnt=sam[sam[per[i]].link].cnt+((plen[per[i]])?sam[per[i]].cnt:0);
    }

    LL ans=0;
    scanf("%s", s);
    len=strlen(s);
    int cur=0,cnt=0;
    for(int i=0;i<len;i++) {
        if(sam[cur].ch[s[i]-'a']) cnt++;
        else {
            while(~cur && !sam[cur].ch[s[i]-'a']) cur=sam[cur].link;
            if(!~cur) cur=cnt=0;
            else cnt=sam[cur].len+1;
        }
        cur=sam[cur].ch[s[i]-'a'];
        if(plen[cur] && cnt>=plen[cur]) ans+=sam[cur].cnt;
        else if(cur) ans+=sam[sam[cur].link].cnt;
    }
    printf("%lld\n", ans);
}

int main() {
    int T=1,cas=1;
    scanf("%d", &T);
    while(T--) {
        printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}