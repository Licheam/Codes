#include <cstdio>
#include <cstring>
#include <cmath>
#define LL long long

const int MAXN=(1<<16)+5;

LL n,p[MAXN],cnt;
bool inp[MAXN];

void sieve(LL x){
	memset(inp,0,(x+1)*sizeof(inp[0]));
	inp[0]=inp[1]=1;
	cnt=0;
	for(LL i=2;i<=x;i++){
		if(!inp[i]) p[++cnt]=i;
		for(LL j=1;j<=cnt&&i*p[j]<=x;j++){
			inp[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}

LL phi(LL x){
	LL ans=x;
	for(LL i=1;i<=cnt&&p[i]*p[i]<=x;i++){
		if(x%p[i]==0){
			ans=ans/p[i]*(p[i]-1);
			while(x%p[i]==0) x/=p[i];
		}
	}
	if(x>1) ans=ans/x*(x-1);
	return ans;
}

int main(){
	scanf("%lld", &n);
	sieve((LL)sqrt(n));
	LL sum=0;
	for(LL i=1;i*i<=n;i++){
		if(n%i==0){
			sum+=i*phi(n/i);
			if(i*i!=n) sum+=n/i*phi(i);
		}
	}
	printf("%lld\n", sum);
	return 0;
}