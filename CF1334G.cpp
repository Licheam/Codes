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


int p[27];
char s[MAXN],t[MAXN];
Complex A[MAXN],B[MAXN],ans[MAXN];
int ss[MAXN],sp[MAXN],st[MAXN];
LL sums,sumt[MAXN];

void solve() {
    for(int i=1;i<=26;i++)
        scanf("%d", &p[i]);
    scanf("%s", s);
    scanf("%s", t);
    int m=strlen(s);
    sums=0;
    for(int i=0;i<m;i++) {
        ss[m-i-1]=s[i]-'a'+1;
        sp[m-i-1]=p[s[i]-'a'+1];
        sums+=ss[m-i-1]*ss[m-i-1]*sp[m-i-1]*sp[m-i-1];
    }
    int n=strlen(t);
    sumt[0]=0;
    for(int i=0;i<n;i++) {
        st[i]=t[i]-'a'+1;
        sumt[i]+=st[i]*st[i]*st[i]*st[i];
        sumt[i+1]=sumt[i];
    }
    int lim;
    for(lim=1;lim<n;lim<<=1);
    memset(ans,0,lim*sizeof(ans[0]));
    
    memset(A,0,lim*sizeof(A[0]));
    memset(B,0,lim*sizeof(B[0]));
    for(int i=0;i<m;i++) A[i]={1.0*ss[i]*ss[i]+sp[i]*sp[i]+4*ss[i]*sp[i],0};
    for(int i=0;i<n;i++) B[i]={1.0*st[i]*st[i],0};
    FFT(lim,A,1);
    FFT(lim,B,1);
    for(int i=0;i<lim;i++) ans[i]=ans[i]+A[i]*B[i];

    memset(A,0,lim*sizeof(A[0]));
    memset(B,0,lim*sizeof(B[0]));
    for(int i=0;i<m;i++) A[i]={1.0*ss[i]+sp[i],0};
    for(int i=0;i<n;i++) B[i]={1.0*st[i]*st[i]*st[i],0};
    FFT(lim,A,1);
    FFT(lim,B,1);
    for(int i=0;i<lim;i++) ans[i]=ans[i]-Complex{2,0}*A[i]*B[i];

    memset(A,0,lim*sizeof(A[0]));
    memset(B,0,lim*sizeof(B[0]));
    for(int i=0;i<m;i++) A[i]={1.0*ss[i]*ss[i]*sp[i]+sp[i]*sp[i]*ss[i],0};
    for(int i=0;i<n;i++) B[i]={1.0*st[i],0};
    FFT(lim,A,1);
    FFT(lim,B,1);
    for(int i=0;i<lim;i++) ans[i]=ans[i]-Complex{2,0}*A[i]*B[i];
    FFT(lim,ans,-1);
    for(int i=m-1;i<=n-1;i++) {
        if((LL)round(ans[i].real/lim)+sums+sumt[i]-(i-m<0?0:sumt[i-m])==0)
            printf("1");
        else printf("0");
    }
    puts("");
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