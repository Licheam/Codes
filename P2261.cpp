#include <cstdio>
#define LL long long

LL n,k;

int main(){
	scanf("%lld %lld", &n, &k);
	LL ans=0;
	if(n>=k){
		for(LL i=1;i<=k;i++){
			LL t=k/i,j=k/t;
			ans+=(j-i+1)*k-(i+j)*(j-i+1)/2*t;
			i=j;
		}
		ans+=(n-k)*k;
	}
	else{
		for(LL i=1;i<=n;i++){
			LL t=k/i,j=k/t;
			if(j>n) j=n;
			ans+=(j-i+1)*k-(i+j)*(j-i+1)/2*t;
			i=j;
		}
	}
	printf("%lld\n", ans);
	return 0;
}