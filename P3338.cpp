#include <cstdio>
#include <algorithm>
#include <complex>
#define MAXN 270005

using namespace std;
const double PI=acos(-1);

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

complex<double> q[MAXN],iq[MAXN];

int main(){
	int n,lim;
	scanf("%d", &n);
	for(lim=1;lim<2*n-1;lim<<=1);
	for(int i=0;i<n;i++){
		double t;
		scanf("%lf", &t);
		q[i]=t;
	}
	iq[n-1]=0;
	for(int i=1;i<n;i++)
		iq[n-1-i]=-(iq[n-1+i]=1.0/i/i);
	fill(q+n,q+lim,complex<double>(0.0,0.0));
	init(lim);
	FFT(lim,q,omg);
	FFT(lim,iq,omg);
	for(int i=0;i<lim;i++)
		q[i]=q[i]*iq[i];
	FFT(lim,q,iomg);
	for(int i=n-1;i<=2*n-2;i++)
		printf("%.3lf\n", q[i].real()/lim);
	return 0;
}