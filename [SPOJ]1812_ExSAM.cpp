#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;

struct SAM {
    int len,link;
    int cnt;
    int tag;
    int ch[26];
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
    sam[0].cnt=0;
    sam[0].tag=0;
    memset(sam[0].ch,0,sizeof(sam[0].ch));
    sz=0;
    last=0;
}

void sam_extend(int c,int stamp) {
    if(sam[last].ch[c] && sam[sam[last].ch[c]].len==sam[last].len+1) {
        last=sam[last].ch[c];
        for(int cur=last;cur && sam[cur].tag!=stamp;cur=sam[cur].link){
            sam[cur].tag=stamp;
            sam[cur].cnt++;
        }
        return;
    }

    int cur=++sz;
    sam[cur].len=sam[last].len+1;
    memset(sam[cur].ch,0,sizeof(sam[cur].ch));
    sam[cur].cnt=0;
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
        sam[cur].cnt++;
        sam[cur].tag=stamp;
    }
}

char s[MAXN];
int tax[MAXN],per[MAXN<<1];

void solve() {
    sam_init();
    int id=0;
    while(~scanf("%s", s)) {
        id++;
        last=0;
        int len=strlen(s);
        for(int i=0;i<len;i++) {
            sam_extend(s[i]-'a', id);
        }
    }

    int ans=0;
    for(int i=1;i<=sz;i++)
        if(sam[i].cnt==id)
            ans=max(ans,sam[i].len);
    printf("%d\n", ans);

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