#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAXN 1000005
#define MAXL 2100005

using namespace std;

struct C{
    double real,image;
    C():real(0),image(0){}
    C(double r,double i):real(r),image(i){}
    C operator+(C y)const{
        C x=*this;
        return C(x.real+y.real,x.image+y.image);
    }
    C operator-(C y)const{
        C x=*this;
        return C(x.real-y.real,x.image-y.image);
    }
    C operator*(C y)const{
        C x=*this;
        return C(x.real*y.real-x.image*y.image,x.real*y.image+x.image*y.real);
    }
}omg[MAXL],iomg[MAXL];

void init(int n){
    double PI=acos(-1);
    for(int i=0;i<n;i++)
        omg[i]=C(cos(2.0*PI*i/n),sin(2.0*PI*i/n));
    iomg[0].real=1;
    for(int i=1;i<n;i++)
        iomg[i]=omg[n-i];
}

void FFT(int n,C* P,C* w){
    for(int i=0,j=0,l;i<n;i++){
        if(i<j) swap(P[i],P[j]);
        for(l=n>>1;(j^=l)<l;l>>=1);
    }
    C t;
    for(int i=2,j,k,l;i<=n;i<<=1){
        l=i>>1;
        for(j=0;j<n;j+=i){
            for(k=0;k<l;k++){
                t=P[j+l+k]*w[n/i*k];
                P[j+l+k]=P[j+k]-t;
                P[j+k]=P[j+k]+t;
            }
        }
    }
}

int n,m,lim,ans[MAXL]={0};
C A[MAXL],B[MAXL];
char s[MAXN];

int main(){
    scanf("%s",s);n=strlen(s);
    for(int i=0;i<n;i++)
        A[i]=C(s[n-i-1]-'0',0);
    scanf("%s",s);m=strlen(s);
    for(int i=0;i<m;i++)
        B[i]=C(s[m-i-1]-'0',0);
    for(lim=1;lim<=n+m-2;lim<<=1);
    init(lim);
    FFT(lim,A,omg);
    FFT(lim,B,omg);
    for(int i=0;i<lim;i++)
        A[i]=A[i]*B[i];
    FFT(lim,A,iomg);
    for(int i=0;i<=n+m-2;i++){
        ans[i]+=(int)(A[i].real/lim+0.5);
        if(ans[i]>=10){
            ans[i+1]+=ans[i]/10;
            ans[i]%=10;
        }
    }
    int cnt=n+m-2;
    for(int i=n+m-1;ans[i];i++){
        cnt++;
        ans[i+1]+=ans[i]/10;
        ans[i]%=10;
    }
    for(int i=cnt;i>=0;i--)
        printf("%d", ans[i]);
    return 0;
}