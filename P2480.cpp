#include <cstdio>
#define LL long long
#define MOD 999911658
#define MAXP 35700

const LL div[]={2,3,4679,35617};

LL n,g,f[MAXP],sum[4];

LL binpow(LL x,LL y,LL mod){
	LL r=1%mod;
	for(;y;y>>=1){
		if(y&1) r=r*x%mod;
		x=x*x%mod;
	}
	return r;
}

void pre(LL p){
	f[0]=1;
	for(int i=1;i<=p-1;i++) f[i]=f[i-1]*i%p;
}

LL C(LL x,LL y,LL p){
	if(x<y) return 0;
	return f[x]*binpow(f[y],p-2,p)%p*binpow(f[x-y],p-2,p)%p;
}

LL lucas(LL x,LL y,LL p){
	if(!y) return 1;
	return C(x%p,y%p,p)*lucas(x/p,y/p,p)%p;
}

LL CRT(){
	LL res=0;
	for(int i=0;i<4;i++){
		res=(res+sum[i]*MOD/div[i]%MOD*binpow(MOD/div[i],div[i]-2,div[i])%MOD)%MOD;
	}
	return res;
}

LL getpow(){
	for(int j=0;j<4;j++){
		pre(div[j]);
		for(LL i=1;i*i<=n;i++){
			if(n%i==0){
				sum[j]=(sum[j]+lucas(n,i,div[j]))%div[j];
				if(i*i<n)
					sum[j]=(sum[j]+lucas(n,n/i,div[j]))%div[j];
			}
		}
	}
	return CRT();
}

int main(){
	scanf("%lld %lld", &n, &g);
	if(g%(MOD+1)==0)
		printf("0\n");
	else
		printf("%lld\n", binpow(g,getpow(),MOD+1));
	return 0;
}