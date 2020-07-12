#include <bits/stdc++.h>
#define MAXN 1100005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;

struct SAM {
    int len,link;
    int ch[2];
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
    if(sam[last].ch[c] && sam[sam[last].ch[c]].len==sam[last].len+1) {
        last=sam[last].ch[c];
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
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }

    last=cur;
}

char s[MAXN];
int tax[MAXN],per[MAXN<<1];
int sp[MAXN];
int dp[MAXN];

void solve() {
    int n,m;
    scanf("%d %d", &n, &m);
    sam_init();
    for(int i=1;i<=m;i++) {
        last=0;
        scanf("%s", s);
        int len=strlen(s);
        for(int i=0;i<len;i++)
            sam_extend(s[i]-'0');
    }

    for(int i=1;i<=n;i++) {
        scanf("%s", s+1);
        int len=strlen(s+1);
        int l=0,r=len;
        while(l<r) {
            deque<pair<int,int>> Q;
            int mid=(l+r+1)>>1;
            int cur=0,cnt=0;
            dp[0]=0;
            for(int i=1;i<=len;i++) {
                if(sam[cur].ch[s[i]-'0']) cnt++;
                else {
                    while(~cur && !sam[cur].ch[s[i]-'0']) cur=sam[cur].link;
                    if(!~cur) cur=cnt=0;
                    else cnt=sam[cur].len+1;
                }
                cur=sam[cur].ch[s[i]-'0'];

                while(!Q.empty() && Q.front().second<i-cnt) Q.pop_front();
                while(!Q.empty() && i>=mid && Q.back().first<dp[i-mid]-i+mid) Q.pop_back();
                if(i>=mid && i-mid>=i-cnt) Q.push_back(make_pair(dp[i-mid]-i+mid,i-mid));
                dp[i]=dp[i-1];
                if(!Q.empty()) dp[i]=max(dp[i],Q.front().first+i);
                // printf("%d ", dp[i]);
            }
            // printf("\n%d %d\n", mid,dp[len]);
            if(10*dp[len]>=9*len) l=mid;
            else r=mid-1;
        }
        printf("%d\n", l);
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