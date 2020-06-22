#include <bits/stdc++.h>
#define MAXN 2000005
#define MAXM 2000005
const int inf=0x3f3f3f3f;
const double eps=1e-6;
using namespace std;
#define MOD 998244353
#define LL long long

int a[MAXN],b[MAXN];
int q[1005];
LL sb[1005],srb[1005];
LL md[1005][1005];

LL k;

int lowbit(int x){
	return x&(-x);
}

void change(int x,int y,int idx){
	for(;x<=1001;x+=lowbit(x))
		md[idx][x]+=y;
}

int sum(int x,int idx){
	int s=0;
	for(;x>0;x-=lowbit(x))
		s+=md[idx][x];
	return s;
}

int n,m;
bool check(LL x) {
	LL res=-n;
	for(int i=1;i<=1000;i++) {
		if(!q[i]) continue;
		res+=(x*q[i]-sb[i]-(q[i]*(x%i)-srb[i]))/i;
		res+=sum(x%i+1,i);
	}
	return res>=k;
}

void solve() {
	
	scanf("%d %d", &n, &m);
	memset(md,0,sizeof(md));
	memset(q+1,0,1000*sizeof(q[0]));
	memset(sb+1,0,1000*sizeof(sb[0]));
	memset(srb+1,0,1000*sizeof(srb[0]));
	for(int i=1;i<=n;i++) {
		scanf("%d", &a[i]);
		q[a[i]]++;
	}
	for(int i=1;i<=n;i++) {
		scanf("%d", &b[i]);
		sb[a[i]]+=b[i];
		srb[a[i]]+=b[i]%a[i];
		change(b[i]%a[i]+1,1,a[i]);
	}

	for(int i=1;i<=m;i++) {
		int opt;
		scanf("%d", &opt);
		if(opt==1) {
			int x,y;scanf("%d %d", &x, &y);
			sb[a[x]]-=b[x];
			q[a[x]]--;
			change(b[x]%a[x]+1,-1,a[x]);
			srb[a[x]]-=b[x]%a[x];

			a[x]=y;

			srb[a[x]]+=b[x]%a[x];
			change(b[x]%a[x]+1,1,a[x]);
			q[a[x]]++;
			sb[a[x]]+=b[x];
		} else if(opt==2) {
			int x,y;scanf("%d %d", &x, &y);
			sb[a[x]]-=b[x];
			change(b[x]%a[x]+1,-1,a[x]);
			srb[a[x]]-=b[x]%a[x];

			b[x]=y;

			srb[a[x]]+=b[x]%a[x];
			change(b[x]%a[x]+1,1,a[x]);
			sb[a[x]]+=b[x];
		} else {
			scanf("%lld", &k);
			LL l=1,r=1e12;
			while(l<r) {
				LL mid=(l+r)>>1;
				if(check(mid)) r=mid;
				else l=mid+1;
			}
			printf("%lld\n", l);
		}
	}
}

int main(){
	int T=1;
	scanf("%d", &T);
	while(T--) {
		solve();
	}
	return 0;
}