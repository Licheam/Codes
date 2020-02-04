#include <cstdio>
#include <cmath>
#include <algorithm>
#include <complex>
#define LL long long
#define MAXN 270005

const double PI=acos(-1);

using namespace std;

complex<double> omg[MAXN],iomg[MAXN];

void init(int n){
	for(int i=0;i<n;i++){
		omg[i]=polar(1.0,2.0*PI*i/n);
		iomg[i]=conj(omg[i]);
	}
}

void FFT(int n,complex<double>* P,complex<double>* w){
	for(int i=0,j=0;i<n;i++){
		if(i<j) swap(P[i],P[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}

	for(int i=2,l;i<=n;i<<=1){
		l=i>>1;
		complex<double> t;
		for(int j=0;j<n;j+=i){
			for(int k=0;k<l;k++){
				t=P[j+l+k]*w[n/i*k];
				P[j+l+k]=P[j+k]-t;
				P[j+k]=P[j+k]+t;
			}
		}
	}
}

int n,m,lim;
LL sumx,sumy,sumx2,sumy2;
complex<double> x[MAXN],y[MAXN];

int main(){
	scanf("%d %d", &n, &m);
	sumx=sumx2=0;
	for(int i=0;i<n;i++){
		int t;scanf("%d", &t);
		x[n-i-1]=t;
		sumx+=t;sumx2+=t*t;
	}
	for(int i=0;i<n;i++){
		int t;scanf("%d", &t);
		y[i+n]=y[i]=t;
		sumy+=t;sumy2+=t*t;
	}
	for(lim=1;lim<2*n-1;lim<<=1);
	fill(x+n,x+lim,complex<double>(0.0,0.0));
	fill(y+2*n,y+lim,complex<double>(0.0,0.0));
	init(lim);
	FFT(lim,x,omg);
	FFT(lim,y,omg);
	for(int i=0;i<lim;i++) x[i]*=y[i];
	FFT(lim,x,iomg);
	LL mx=round(x[n-1].real()/lim);
	for(int i=n;i<=2*n-2;i++)
		mx=max(mx,(LL)round(x[i].real()/lim));
	LL del=round((double)(sumy-sumx)/n);
	printf("%lld\n", n*del*del+sumx2+sumy2-2*mx+2*del*(sumx-sumy));
	return 0;
}