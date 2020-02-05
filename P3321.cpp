#include <cstdio>
#include <cstring>
#include <vector>
#define LL long long
#define MAXM 8005
#define MAXL 17005
#define MOD 1004535809
#define RT 3

using namespace std;

int binpow(int x,int y,int mod){
	int r=1%mod;
	while(y){
		if(y&1) r=(1LL*r*x)%mod;
		x=(1LL*x*x)%mod;
		y>>=1;
	}
	return r;
}

int getroot(int x){
	vector<int> v;
	int p=x-1;
	for(int i=2;i*i<=p;i++){
		if(p%i==0){
			v.push_back(i);
			while(p%i==0) p/=i;
		}
	}
	if(p>1) v.push_back(p);
	for(int g=2;;g++){
		bool isg=true;
		for(int i=0;i<v.size();i++){
			if(binpow(g,(x-1)/v[i],x)==1){
				isg=false;
				break;
			}
		}
		if(isg) return g;
	}
	return 0;
}

LL omg[MAXL],iomg[MAXL];

void init(int n){
	omg[0]=iomg[0]=1;
	omg[1]=binpow(RT,(MOD-1)/n,MOD);
	iomg[1]=binpow(omg[1],MOD-2,MOD);
	for(int i=2;i<n;i++){
		omg[i]=omg[i-1]*omg[1]%MOD;
		iomg[i]=iomg[i-1]*iomg[1]%MOD;
	}
}

void NTT(int n,LL* P,LL* w){
	for(int i=0,j=0;i<n;i++){
		if(i<j) swap(P[i],P[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
	
	for(int i=2,l;i<=n;i<<=1){
		l=i>>1;
		for(int j=0;j<n;j+=i){
			for(int k=0;k<l;k++){
				LL t=P[j+l+k]*w[n/i*k]%MOD;
				P[j+l+k]=(P[j+k]-t+MOD)%MOD;
				P[j+k]=(P[j+k]+t)%MOD;
			}
		}
	}
}

int dlog[MAXM];
int n,m,lim,invlim,rm,S;
LL R[MAXL],X[MAXL];

void conv(LL* A,LL* B){
	LL C[MAXL];
	for(int i=0;i<lim;i++) C[i]=B[i];
	NTT(lim,A,omg);
	NTT(lim,C,omg);
	for(int i=0;i<lim;i++)
		A[i]=A[i]*C[i]%MOD;
	NTT(lim,A,iomg);
	for(int i=0;i<m-1;i++)
		A[i]=(A[i]+A[i+m-1])*invlim%MOD;
	memset(A+m-1,0,(lim-m+1)*sizeof(A[0]));
}

int main(){
	scanf("%d %d %d %d",&n,&m,&rm,&S);
	int g=getroot(m);
	for(int i=0,t=1;i<m-1;i++,t=(t*g%m)) dlog[t]=i;
	for(lim=1;lim<2*m;lim<<=1);
	init(lim);
	invlim=binpow(lim,MOD-2,MOD);
	memset(R,0,lim*sizeof(R[0]));
	R[0]=1;
	memset(X,0,lim*sizeof(X[0]));
	for(int i=0,t;i<S;i++){
		scanf("%d", &t);
		if(t%m) X[dlog[t%m]]++;
	}
	while(n){
		if(n&1) conv(R,X);
		conv(X,X);
		n>>=1;
	}
	printf("%lld\n", R[dlog[rm]]);
	return 0;
}