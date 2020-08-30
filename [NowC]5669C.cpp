/*
    Coded with Leachim's ACM Template.
    No error. No warning~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAXN=2000005;
 
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
    if(sam[last].ch[c] && sam[last].len+1==sam[sam[last].ch[c]].len) {
        last=sam[last].ch[c];
        sam[last].cnt++;
        return;
    }
 
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
            sam[clone].cnt=0;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }
 
    last=cur;
    sam[cur].cnt=1;
}
 
char s[MAXN];
int lp[10];
 
void solve() {
    scanf("%s", s);
    int len=strlen(s);

    memset(lp,0,sizeof(lp));
    sam_init();
    for(int i=len-1;i>=0;i--) {
        int mx=0,mi=0;
        for(int k=s[i]-'a';k<10;k++)
            if(sam[lp[k]].len>=mx) mx=sam[lp[k]].len,mi=k;
        last=lp[mi];
        for(int j=mx+1;j<=len-i;j++)
            sam_extend(s[i]-'a');
        lp[s[i]-'a']=last;
    }
 
    LL ans=0;
    for(int i=1;i<=sz;i++)
        ans+=sam[i].len-sam[sam[i].link].len;
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