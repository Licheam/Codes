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
const int MOD=998244353;
const int MAXN=2000005;

int inv[MAXN];
int f[MAXN],fi[MAXN];

int C(int x,int y) {
    if(x<y) return 0;
    return 1LL*f[x]*fi[y]%MOD*fi[x-y]%MOD;
}

void solve() {
    int n,m,k;
    scanf("%d %d %d", &n, &m, &k);
    LL ans=0;
    for(int i=0;i<=min(n-k,m-k);i++)
        ans=(ans+1LL*C(i+k-1,k-1)*C(n-i-1,k-1)%MOD*C(m-i-1,k-1)%MOD)%MOD;
    printf("%lld\n", ans);
}

void init(int n) {
    inv[1]=1;
    f[0]=fi[0]=f[1]=fi[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=1LL*(MOD-MOD/i)*inv[MOD%i]%MOD;
        f[i]=1LL*f[i-1]*i%MOD;
        fi[i]=1LL*fi[i-1]*inv[i]%MOD;
    }
}

int main() {
    int T=1,cas=1;(void)(cas);
    scanf("%d", &T);
    init(1e6);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}