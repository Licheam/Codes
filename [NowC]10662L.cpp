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
const int MOD=998244353;
const int MAXN=2000005;

int kmp(int *s1, int *s2, int *nxt, int n, int m){
    nxt[0]=-1;
    for(int i=1,k=-1;i<=m;i++){
        //k初始值为-1. nxt数组可以查询boarder的boarder.
        while(~k && s2[k]!=s2[i-1])
            k=nxt[k];
        nxt[i]=++k;
    }

    int cnt=0;
    for(int i=1,k=0;i<=n;i++){
        //匹配串前缀与模式串后缀比，上一位前缀的boarder的boarder也能匹配。
        while(k==m || (~k && s2[k]!=s1[i-1]))
            k=nxt[k];
        if(m==++k){
            cnt++;
        }
    }
    return cnt;
}

int nxt[MAXN];
LL dp[MAXN][2];
int a[MAXN],c[MAXN],tc[MAXN];

void solve() {
	int m;
	LL n;
	scanf("%d %lld", &m, &n);
	n+=m;
	for(int i=0;i<m;i++)
		scanf("%d", &a[i]);

	int len=0;
	c[0]=0;
	while((1LL<<len)<m) {
		dp[len][0]=dp[len][1]=0;
		for(int i=0;i<(1LL<<len);i++)
			c[(1LL<<len)+i]=c[i]^1;
		len++;
	}
	for(int i=0;i<(1LL<<len);i++)
		c[(1LL<<len)+i]=c[i]^1;

	if((1LL<<len)>=n) {
		printf("%d\n", kmp(c,a,nxt,n,m));
		return;
	}

	dp[len][0]=kmp(c,a,nxt,1LL<<len,m);
	dp[len][1]=kmp(c+(1LL<<len),a,nxt,1LL<<len,m);

	int x[4];
	for(int i=0;i<m-1;i++) tc[i]=c[(1LL<<len)-m+1+i];
	for(int i=0;i<m-1;i++) tc[m-1+i]=c[i];
	x[0]=kmp(tc,a,nxt,2*(m-1),m);
	
	for(int i=0;i<m-1;i++) tc[i]^=1;
	x[2]=kmp(tc,a,nxt,2*(m-1),m);
	
	for(int i=0;i<2*(m-1);i++) tc[i]^=1;

	x[1]=kmp(tc,a,nxt,2*(m-1),m);
	
	for(int i=0;i<m-1;i++) tc[i]^=1;
	x[3]=kmp(tc,a,nxt,2*(m-1),m);

	int flag=0;
	while((1LL<<(len+1))<=n) {
		len++;
		dp[len][0]=dp[len-1][0]+dp[len-1][1]+(flag?x[3]:x[1]);
		dp[len][1]=dp[len-1][1]+dp[len-1][0]+(flag?x[0]:x[2]);
		flag^=1;
	}

	n-=(1LL<<len);
	LL ans=dp[len--][0];
	int cnt,cur=flag;
	for(cnt=1;n && (1LL<<len)>=m;len--,flag^=1) {
		if((1LL<<len)&n) {
			ans+=dp[len][cnt]+x[cur<<1|cnt];
			cnt^=1;
			cur=flag^cnt;
			n-=(1LL<<len);
		}
	}

	cur^=1;
	for(int i=0;i<m-1;i++) tc[i]^=cur;
	for(int i=0;i<n;i++) tc[m-1+i]=c[i]^cnt;

	ans+=kmp(tc,a,nxt,m-1+n,m);
	printf("%lld\n", ans);
}

int main() {
	int T=1,cas=1;(void)(cas);
	scanf("%d", &T);
	while(T--) {
		// printf("Case #%d: ", cas++);
		solve();
	}
	return 0;
}