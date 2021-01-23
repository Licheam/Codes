/*
    Coded with Leachim's ACM Template.
    No errors. No warnings. ~~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int RT=3;
const int MOD=1e9+7;
const int MAXN=2000005;

int cat[MAXN],inv[MAXN];
void catalan(int n){
    inv[1]=1;
    for(int i=2;i<=n+1;i++)
        inv[i]=1LL*(MOD-MOD/i)*inv[MOD%i]%MOD;
    cat[0]=1;
    for(int i=1;i<=n;i++)
        cat[i]=1LL*cat[i-1]*(4*i-2)%MOD*inv[i+1]%MOD;
}

int a[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    catalan(n);
    for(int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    a[n+1]=-1;
    LL ans=1;
    stack<int> Q;
    for(int i=1;i<=n+1;i++) {
        int cnt=0,x=inf;
        while(!Q.empty() && Q.top()>a[i]) {
            if(Q.top()<x) {
                ans=ans*cat[cnt]%MOD;
                x=Q.top();
                cnt=1;
            } else cnt++;
            Q.pop();
        }
        ans=ans*cat[cnt]%MOD;
        Q.push(a[i]);
    }
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