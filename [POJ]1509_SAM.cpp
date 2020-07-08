// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
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

char s[MAXN];

void solve() {
    scanf("%s", s);
    int len=strlen(s);
    sam_init();
    for(int i=0;i<len;i++)
        sam_extend(s[i]-'a');
    for(int i=0;i<len;i++)
        sam_extend(s[i]-'a');
    int cur=0;
    for(int i=0;i<len;i++) {
        for(int j=0;j<26;j++) {
            if(sam[cur].ch[j]) {
                cur=sam[cur].ch[j];
                break;
            }
        }
    }
    printf("%d\n", sam[cur].len-len+1);
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