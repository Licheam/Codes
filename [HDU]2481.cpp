/*
	Coded with Leachim's ACM Template.
	No errors. No warnings. ~~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int RT=3;
const int MAXN=2000005;

LL MOD=998244353;

struct Matrix{
	__int128 num[3][3];
	int n,m;

	Matrix(int nn,int mm){
		n=nn; m=mm;
		memset(num,0,sizeof(num));
	}
	Matrix(int nn){
		n=m=nn;
		memset(num,0,sizeof(num));
		for(int i=1;i<=nn;i++) num[i][i]=1;
	}

	Matrix operator*(const Matrix &y) const{
		Matrix x=*this,ans(x.n,y.m);
		if(x.m!=y.n) return ans;
		for(int i=1;i<=x.n;i++){
			for(int j=1;j<=y.m;j++){
				for(int k=1;k<=x.m;k++){
					ans.num[i][j]=(ans.num[i][j]+x.num[i][k]*y.num[k][j]%MOD)%MOD;
				}
			}
		}
		return ans;
	}
};

Matrix binpow(Matrix x,int y){
	Matrix r(x.n);
	while(y){
		if(y&1) r=r*x;
		x=x*x;
		y>>=1;
	}
	return r;
}

LL f(int x) {
	Matrix T(2,2),B(1,2);
	T.num[1][1]=3;
	T.num[1][2]=1;
	T.num[2][1]=MOD-1;
	T.num[2][2]=0;
	T=binpow(T,x-1);
	B.num[1][1]=3;
	B.num[1][2]=1;
	B=B*T;
	return ((2*B.num[1][1]%MOD-3*B.num[1][2]%MOD-2)%MOD+MOD)%MOD;
}

int phi(int x) {
	int r=x;
	for(int i=2;i*i<=x;i++) {
		if(x%i==0) {
			while(x%i==0) x/=i;
			r=r/i*(i-1);
		}
	}
	if(x>1) r=r/x*(x-1);
	return r;
}

void solve() {
	int n,m;
	while(~scanf("%d %d", &n, &m)) {
		MOD=1LL*n*m;
		LL ans=0;
		for(int i=1;i*i<=n;i++) {
			if(n%i==0) {
				ans=(ans+(__int128)f(i)*phi(n/i)%MOD)%MOD;
				if(i*i!=n) {
					ans=(ans+(__int128)f(n/i)*phi(i)%MOD)%MOD;
				}
			}
		}
		printf("%lld\n", ans/n);
	}
}

int main() {
	int T=1,cas=1;(void)(cas);
	// scanf("%d", &T);
	while(T--) {
		// printf("Case #%d: ", cas++);
		solve();
	}
	return 0;
}