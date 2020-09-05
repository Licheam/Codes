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

const double PI=acos(-1);

struct Complex{
    double real,image;
    Complex operator+(Complex y)const{
        return {real+y.real,image+y.image};
    }
    Complex operator-(Complex y)const{
        return {real-y.real,image-y.image};
    }
    Complex operator*(Complex y)const{
        return {real*y.real-image*y.image,real*y.image+image*y.real};
    }
};

void FFT(int n,Complex* P,int f){
    for(int i=0,j=0;i<n;i++){
        if(i<j) swap(P[i],P[j]);
        for(int l=n>>1;(j^=l)<l;l>>=1);
    }

    for(int i=2,l;i<=n;i<<=1){
        l=i>>1;
        Complex wn={cos(2*PI/i),f*sin(2*PI/i)};
        for(int j=0;j<n;j+=i){
            Complex w={1,0};
            for(int k=0;k<l;k++,w=w*wn){
                Complex t=P[j+l+k]*w;
                P[j+l+k]=P[j+k]-t;
                P[j+k]=P[j+k]+t;
            }
        }
    }
}

int a[MAXN];
LL cnt[MAXN];
Complex A[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    int lim;
    for(lim=1;lim<=2e5;lim<<=1);
    memset(A,0,lim*sizeof(A[0]));
    for(int i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        A[a[i]].real++;
    }
    FFT(lim,A,1);
    for(int i=0;i<lim;i++) A[i]=A[i]*A[i];
    FFT(lim,A,-1);
    for(int i=0;i<lim;i++)
        cnt[i]=lround(A[i].real/lim);

    for(int i=1;i<=n;i++) cnt[2*a[i]]--;
    for(int i=0;i<lim;i++) cnt[i]/=2;
    for(int i=1;i<lim;i++) cnt[i]+=cnt[i-1];

    LL sum=0;
    for(int i=1;i<=n;i++) sum+=cnt[a[i]];

    printf("%.7lf\n", 1.0-(double)sum*6/n/(n-1)/(n-2));
}

int main() {
    int T=1,cas=1;(void)(cas);
    scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}