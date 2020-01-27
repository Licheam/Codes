#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 50005
#define N 50000
#define LL long long

using namespace std;

int n,m,cnt;
LL p[MAXN],mu[MAXN],smu[MAXN],d[MAXN],sd[MAXN],alpha[MAXN];
bool inp[MAXN];

void pre(){
	memset(inp+1,0,N*sizeof(inp[0]));
	inp[0]=inp[1]=1;
	smu[1]=mu[1]=1;smu[0]=0;
	sd[1]=d[1]=1;sd[0]=0;
	alpha[1]=0;
	cnt=0;
	for(int i=2;i<=N;i++){
		if(!inp[i]) p[++cnt]=i, mu[i]=-1, d[i]=2, alpha[i]=1;
		for(int j=1;j<=cnt && i*p[j]<=N;j++){
			inp[i*p[j]]=1;
			if(i%p[j]){
				mu[i*p[j]]=-mu[i];
				alpha[i*p[j]]=1;
				d[i*p[j]]=d[i]*2;
			}
			else{
				mu[i*p[j]]=0;
				alpha[i*p[j]]=alpha[i]+1;
				d[i*p[j]]=d[i]/(alpha[i]+1)*(alpha[i*p[j]]+1);
				break;
			}
		}
		smu[i]=smu[i-1]+mu[i];
		sd[i]=sd[i-1]+d[i];
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
			ans+=(smu[j]-smu[i-1])*sd[n/i]*sd[m/i];
			i=j;
		}
		printf("%lld\n", ans);
	}
	return 0;
}