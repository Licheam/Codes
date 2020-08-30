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

void FWTxor(int n,int* P,int f) {
    for (int l=1;(l<<1)<=n;l<<=1)
        for(int i=0;i<n;i+=(l<<1))
            for(int j=0;j<l;j++) {
                int t=P[i+j];
                P[i+j]=(t+P[i+j+l])/f;
                P[i+j+l]=(t-P[i+j+l])/f;
            }
}

int A[MAXN],B[MAXN];
int dp[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    memset(A,0,(1<<18)*sizeof(A[0]));
    memset(B,0,(1<<18)*sizeof(B[0]));
    for(int i=1;i<=n;i++) {
        int x;scanf("%d", &x);
        B[x]=A[x]=1;
    }
    FWTxor(1<<18,A,1);
    for(int i=1;i<=min(19,n);i++) {
        for(int j=(1<<18)-1;j>=0;j--)
            if(B[j]) {dp[i]=j;break;}
        printf("%d ", dp[i]);

        FWTxor(1<<18,B,1);
        for(int j=0;j<(1<<18);j++) B[j]*=A[j];
        FWTxor(1<<18,B,2);
        for(int j=0;j<(1<<18);j++)
            if(B[j]) B[j]=1;
    }
    for(int i=20;i<=n;i++){
        dp[i]=dp[i-2];
        printf("%d ", dp[i]);
    }

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