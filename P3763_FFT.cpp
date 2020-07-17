/*
Coded with Leachim's ACM Template.
No error, No warnings~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAXN=100005;

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

char s[MAXN],s0[MAXN];
int A[MAXN],B[MAXN];
int ans[MAXN];
Complex ta[MAXN<<2],tb[MAXN<<2];

int mp[4]={'A','G','T','C'};

void solve() {
    scanf("%s", s0+1);
    scanf("%s", s+1);
    int n=strlen(s0+1),m=strlen(s+1);
    int lim;
    for(lim=1;lim<=n+m;lim<<=1);
    memset(ans+1,0,(n+1)*sizeof(ans[0]));
    for(int k=0;k<4;k++) {
        memset(ta,0,lim*sizeof(ta[0]));
        memset(tb,0,lim*sizeof(tb[0]));
        for(int i=1;i<=n;i++) {
            A[i]=(s0[i]==mp[k]);
            ta[i]={1.0*A[i],0};
        }
        for(int i=1;i<=m;i++) {
            B[m-i+1]=(s[i]==mp[k]);
            tb[m-i+1]={1.0*B[m-i+1],0};
        }
        FFT(lim,ta,1);
        FFT(lim,tb,1);
        for(int i=0;i<lim;i++)
            ta[i]=ta[i]*tb[i];
        FFT(lim,ta,-1);
        for(int i=0;i<=n+1;i++)
            ans[i]+=(int)(ta[i].real/lim+0.5);
    }
    int cnt=0;
    for(int i=m+1;i<=n+1;i++)
        if(ans[i]+3>=m) cnt++;
    printf("%d\n", cnt);
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