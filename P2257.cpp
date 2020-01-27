#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define MAXN 10000005

const int N=10000000;

using namespace std;

int n,m,p[MAXN],cnt,mu[MAXN];
LL g[MAXN],sumg[MAXN];
bool inp[MAXN];

void pre(){
	memset(inp+1,0,N*sizeof(inp[0]));
	inp[0]=inp[1]=1;
	sumg[1]=g[1]=0;
	mu[1]=1;
	cnt=0;
	for(int i=2;i<=N;i++){
		if(!inp[i]) p[++cnt]=i, mu[i]=-1, g[i]=1;
		for(int j=1;j<=cnt&&i*p[j]<=N;j++){
			inp[i*p[j]]=1;
			if(i%p[j]){
				mu[i*p[j]]=-mu[i];
				g[i*p[j]]=-g[i]+mu[i];
			}
			else {
				mu[i*p[j]]=0;
				g[i*p[j]]=mu[i];
				break;
			}
		}
		sumg[i]=sumg[i-1]+g[i];
	}
}

int main(){
	int T;
	scanf("%d", &T);
	pre();
	while(T--){
		scanf("%d %d", &n, &m);
		LL ans=0;
		for(int i=1;i<=min(n,m);i++){
			int j=min(n/(n/i),m/(m/i));
			ans+=1LL*(n/i)*(m/i)*(sumg[j]-sumg[i-1]);
			i=j;
		}
		printf("%lld\n", ans);
	}
	return 0;
}