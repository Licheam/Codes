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
const int MOD=998244353;
const int MAXN=2000005;
const int M=1e5;

int binpow(int x,LL y,int m){
    int r=1%m;
    while(y){
        if(y&1)
            r=1LL*r*x%m;
        x=1LL*x*x%m;
        y>>=1;
    }
    return r;
}

int p[MAXN],pm[MAXN];

int lightpow(LL y) {
    if(y<=M) return p[y];
    return 1LL*p[y%M]*pm[y/M]%MOD;
}

void solve() {
    int n;
    scanf("%d", &n);
    LL ans=0;
    for(int k=1;k<=n;k++) {
        LL sum=0;
        int inv=binpow((lightpow(k)-1+MOD)%MOD,MOD-2,MOD);
        for(int i=1;i<=n;i++) {
            int t=n/i,j=n/t;
            sum=(sum+1LL*t*lightpow(1LL*i*k)%MOD*(lightpow(1LL*k*(j-i+1))-1+MOD)%MOD)%MOD;
            i=j;
        }
        ans=(ans+1LL*n/k*sum%MOD*inv%MOD)%MOD;
    }
    printf("%lld\n", ans);
}

void init(int n) {
    p[0]=1;
    for(int i=1;i<=n;i++) p[i]=2LL*p[i-1]%MOD;
    pm[0]=1;
    for(int i=1;i<=n;i++) pm[i]=1LL*pm[i-1]*p[n]%MOD;
}

int main() {
    int T=1,cas=1;(void)(cas);
    scanf("%d", &T);
    init(M);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}