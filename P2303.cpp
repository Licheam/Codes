#include <cstdio>
#define LL long long

LL n;

int main(){
	scanf("%lld", &n);
	LL ans=n;
	for(LL i=2;i*i<=n;i++){
		if(n%i==0){
			LL cnt=0;
			while(n%i==0) cnt++,n/=i;
			ans=ans/i*(cnt*(i-1)+i);
		}
	}
	if(n>1) ans=ans/n*(2*n-1);
	printf("%lld\n", ans);
	return 0;
}