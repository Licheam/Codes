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

int a[MAXN],b[MAXN];
int pa[MAXN],pb[MAXN];
bool flag[MAXN];
int n;

int nxt(int x) {return x==n?1:x+1;}
int lst(int x) {return x==1?n:x-1;}

void solve() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        pa[a[i]]=i;
    }
    for(int i=1;i<=n;i++) {
        scanf("%d", &b[i]);
        pb[b[i]]=i;
    }
    memset(flag+1,0,n*sizeof(flag[0]));
    vector<int> ans;
    for(int i=1;i<=n;i++) {
        if(flag[i]) continue;
        int la=i,ra=i,lb=pb[a[i]],rb=pb[a[i]];
        ans.clear();
        ans.push_back(a[i]);
        while(ans.size()<n && (a[lst(la)]==b[lst(lb)] || a[lst(la)]==b[nxt(rb)]
                || a[nxt(ra)]==b[lst(lb)] || a[nxt(ra)]==b[nxt(rb)])) {
            if(a[lst(la)]==b[lst(lb)]) la=lst(la),lb=lst(lb),ans.push_back(a[la]);
            else if(a[lst(la)]==b[nxt(rb)]) la=lst(la),rb=nxt(rb),ans.push_back(a[la]);
            else if(a[nxt(ra)]==b[lst(lb)]) ra=nxt(ra),lb=lst(lb),ans.push_back(a[ra]);
            else if(a[nxt(ra)]==b[nxt(rb)]) ra=nxt(ra),rb=nxt(rb),ans.push_back(a[ra]);
            flag[la]=flag[ra]=1;
        }
        if(ans.size()==n) break;
    }
    if(ans.size()==n) {
        for(int x:ans)
            printf("%d ", x);
        puts("");
    } else printf("-1\n");
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