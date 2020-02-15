#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define N 100000
#define MAXN 100005
#define MOD 1000000007
using namespace std;

LL bit1[MAXN],bit2[MAXN],pw[MAXN],a[MAXN];
int n;

LL lowbit(LL x){return x&(-x);}
void modify(LL x,LL *bit){for(LL i=x;i<=n;i+=lowbit(i)) bit[i]=(bit[i]+pw[x])%MOD;}
LL query(LL x,LL *bit){LL res=0; for(;x>0;x-=lowbit(x)) res=(res+bit[x])%MOD; return res;}

void solve(){
	scanf("%d", &n);
	memset(bit1+1,0,n*sizeof(bit1[0]));
	memset(bit2+1,0,n*sizeof(bit2[0]));
	for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
	for(int i=1;i<=n;i++){
		modify(a[i],bit1);modify(n-a[i]+1,bit2);
		LL l=max(1LL,2*a[i]-n),r=min((LL)n,2*a[i]-1);
		if((query(r,bit1)-query(l-1,bit1)+MOD)*pw[n-r+1]%MOD!=(query(n-l+1,bit2)-query(n-r,bit2)+MOD)*pw[l]%MOD){
			printf("Y\n");
			return;
		}
	}
	printf("N\n");
}

int main(){
	int T;
	scanf("%d", &T);
	pw[1]=1;
	for(LL i=2;i<=N;i++) pw[i]=(pw[i-1]<<1)%MOD;
	while(T--){
		solve();
	}
	return 0;
}