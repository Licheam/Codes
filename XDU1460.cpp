#include <cstdio>
#define LL long long
#define K 2500
#define MAXK 2505
#define MOD 1000000007

int n,k;
LL f[MAXK];

LL binpow(LL x,LL y,LL m){
	if(!x)return 0;
	LL r=1%m;
	while(y){
		if(y&1) r=(r*x)%m;
		x=(x*x)%m;
		y>>=1;
	}
	return r;
}

void pre(LL x,LL p){
	f[0]=1;
	for(int i=1;i<=x;i++) f[i]=f[i-1]*i%p;
}

LL C(LL x,LL y,LL p){//x!/y!(x-y)!
	if(x<y) return 0;
	else if(!y) return 1;
	return f[x]*binpow(f[y],p-2,p)%p*binpow(f[x-y],p-2,p)%p;
}

void solve(){
	scanf("%d %d", &n, &k);
	for(int i=1;i<n;i++){
		int f,g;
		scanf("%d %d", &f, &g);
	}
	LL sum=0;
	for(int i=0;i<k-1;i++){
		if(i&1) sum=(sum-C(k,i,MOD)*(k-i)%MOD*binpow(k-i-1,n-1,MOD)%MOD+MOD)%MOD;
		else	sum=(sum+C(k,i,MOD)*(k-i)%MOD*binpow(k-i-1,n-1,MOD)%MOD+MOD)%MOD;
	}
	printf("%lld\n", sum);
}

int main(){
	int T;
	scanf("%d", &T);
	pre(K,MOD);
	while(T--){
		solve();
	}
	return 0;
}