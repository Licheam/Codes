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

LL binpow(LL x,LL y,LL mod){
    LL r=1%mod;
    while(y){
        if(y&1) r=(r*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return r;
}

void NTT(int n,int* P,int f){
    for(int i=0,j=0;i<n;i++){
        if(i<j) swap(P[i],P[j]);
        for(int l=n>>1;(j^=l)<l;l>>=1);
    }
    
    for(int i=2,l;i<=n;i<<=1){
        l=i>>1;
        int wn=binpow(RT,(MOD-1)/i,MOD);
        if(f==-1) wn=binpow(wn,MOD-2,MOD);
        for(int j=0;j<n;j+=i){
            int w=1;
            for(int k=0;k<l;k++,w=1LL*w*wn%MOD){
                int t=1LL*P[j+l+k]*w%MOD;
                P[j+l+k]=1LL*(P[j+k]-t+MOD)%MOD;
                P[j+k]=1LL*(P[j+k]+t)%MOD;
            }
        }
    }
}

int A[MAXN],B[MAXN];

int inv[MAXN],f[MAXN],fi[MAXN];

void solve() {
    int n,m;
    while(~scanf("%d %d", &n, &m)) {
        int lim;
        for(lim=1;lim<=2*n;lim<<=1);
        memset(A,0,lim*sizeof(A[0]));
        memset(B,0,lim*sizeof(B[0]));
        for(int i=0;i<=n;i++) {
            A[i]=1LL*binpow(i,m,MOD)*fi[i]%MOD;
            B[i]=(1LL*((i&1)?-1:1)*fi[i]%MOD+MOD)%MOD;
        }

        NTT(lim,A,1);
        NTT(lim,B,1);
        for(int i=0;i<lim;i++) A[i]=1LL*A[i]*B[i]%MOD;
        NTT(lim,A,-1);
        int invn=binpow(lim,MOD-2,MOD);
        int invnm=binpow(inv[n],m,MOD);
        for(int i=1;i<=min(n,m);i++)
            printf("%lld%c", 1LL*f[n]*fi[n-i]%MOD*invnm%MOD*A[i]%MOD*invn%MOD, i==min(n,m)?'\n':' ');
    }
}

void pre_inv(int n,int p) {
    inv[1]=1;
    f[0]=fi[0]=f[1]=fi[1]=1;
    for(int i=2;i<=n;i++) {
        inv[i]=1LL*(p-p/i)*inv[p%i]%p;
        f[i]=1LL*f[i-1]*i%p;
        fi[i]=1LL*fi[i-1]*inv[i]%p;
    }
}

int main() {
    int T=1,cas=1;(void)(cas);
    // scanf("%d", &T);
    pre_inv(1e5,MOD);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}