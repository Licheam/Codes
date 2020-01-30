#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define MAXN 10000005
#define MOD 20101009

using namespace std;

int n,m,lim;
int p[MAXN],cnt;
bool inp[MAXN];

LL mu[MAXN],smu[MAXN];

void pre(){
	memset(inp+1,0,lim*sizeof(inp[0]));
	inp[0]=inp[1]=1;
	cnt=0;
	smu[0]=0;
	smu[1]=mu[1]=1;
	for(int i=2;i<=lim;i++){
		if(!inp[i]) p[++cnt]=i, mu[i]=-1;
		for(int j=1;j<=cnt && i*p[j]<=lim;j++){
			inp[i*p[j]]=1;
			if(i%p[j]){
				mu[i*p[j]]=-mu[i];
			}
			else{
				mu[i*p[j]]=0;
				break;
			}
		}
		smu[i]=(smu[i-1]+1LL*i*i%MOD*mu[i]%MOD+MOD)%MOD;
	}
}

LL sumf(LL d){
	LL res=0;
	LL bound=lim/d, nd=n/d, md=m/d;
	for(LL i=1;i<=bound;i++){
		LL j=min(nd/(nd/i),md/(md/i));
		res=(res+(smu[j]-smu[i-1]+MOD)*((1+nd/i)*(nd/i)/2%MOD)%MOD*((1+md/i)*(md/i)/2%MOD)%MOD)%MOD;
		i=j;
	}
	return res;
}

int main(){
	scanf("%d %d", &n, &m);
	lim=min(n,m);
	pre();
	LL ans=0;
	for(LL i=1;i<=lim;i++){
		LL j=min(n/(n/i),m/(m/i));
		ans=(ans+(((i+j)*(j-i+1)/2)%MOD*sumf(i)%MOD)+MOD)%MOD;
		i=j;
	}
	printf("%lld\n", ans);
	return 0;
}