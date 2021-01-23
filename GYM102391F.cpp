#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int MAXN = 300005;
const int inf = 0x3f3f3f3f;
const int MOD = 1e9+7;
struct SGT{
	LL sum[MAXN<<2],ts[MAXN<<2],tm[MAXN<<2];
	
	void pushup(int x) {sum[x]=(sum[x<<1]+sum[x<<1|1])%MOD;}
	void pushdown(int x,int l,int r) {
		int m=(l+r)>>1;
		sum[x<<1]=(sum[x<<1]*tm[x]%MOD + ts[x]*(m-l+1)%MOD)%MOD;
		sum[x<<1|1]=(sum[x<<1|1]*tm[x]%MOD + ts[x]*(r-m)%MOD)%MOD;
		tm[x<<1]=tm[x<<1]*tm[x]%MOD;
		tm[x<<1|1]=tm[x<<1|1]*tm[x]%MOD;
		ts[x<<1]=(ts[x<<1]*tm[x]%MOD+ts[x])%MOD;
		ts[x<<1|1]=(ts[x<<1|1]*tm[x]%MOD+ts[x])%MOD;
		tm[x]=1;
		ts[x]=0;
	}
	
	void build(int x,int l,int r,LL a) {
		ts[x]=0,tm[x]=1;
		if(l==r) sum[x]=a;
		else {
			int m=(l+r)>>1;
			build(x<<1,l,m,a);
			build(x<<1|1,m+1,r,a);
			pushup(x);
		}
	}
	
	void plus(int x,int l,int r,int ql,int qr,LL d) {
		if(ql>qr) return;
		
		if(ql<=l && r<=qr) {
			sum[x]=(sum[x]+d*(r-l+1)%MOD)%MOD;
			ts[x]=(ts[x]+d)%MOD;
		} else {
			pushdown(x,l,r);
			int m=(l+r)>>1;
			if(ql<=m) plus(x<<1,l,m,ql,qr,d);
			if(m<qr) plus(x<<1|1,m+1,r,ql,qr,d);
			pushup(x);
		}
	}

	void multi(int x,int l,int r,int ql,int qr,LL d) {
		if(ql>qr) return;

        if(ql<=l && r<=qr) {
            sum[x]=(sum[x]*d)%MOD;
            ts[x]=(ts[x]*d)%MOD;
            tm[x]=(tm[x]*d)%MOD;
            return;
        }

        pushdown(x,l,r);
        int m=(l+r)>>1;
        if(ql<=m) multi(x<<1,l,m,ql,qr,d);
        if(m<qr) multi(x<<1|1,m+1,r,ql,qr,d);
        pushup(x);
    }

    LL query(int x,int l,int r,int q) {
        if(l==r && l==q) return sum[x];

        pushdown(x,l,r);
        int m=(l+r)>>1;
        LL res=0;
        if(q<=m) res=(res+query(x<<1,l,m,q))%MOD;
        else if(m<q) res=(res+query(x<<1|1,m+1,r,q))%MOD;
        return res;
    }
}sgt,gap;

vector<LL> v[MAXN];

void solve() {
	int n;
	scanf("%d", &n);
	int cnt=0,bom=0,zero=0;
	sgt.build(1,0,n,0);
	gap.build(1,0,n,1);
	v[0].push_back(0);
	for(int i=1;i<=n;i++) {
		int opt;
		scanf("%d", &opt);
		if(opt==1) {
			++cnt;
			int k;
			scanf("%d", &k);
			if(k) {
				zero=cnt;
				sgt.plus(1,0,n,0,cnt-1,k);
				v[bom].push_back(v[bom].back()+k);
			} else {
				v[++bom].push_back(0);
				sgt.multi(1,0,n,0,cnt-1,2);
				sgt.plus(1,0,n,cnt,cnt,1);
				gap.multi(1,0,n,0,cnt,2);
			}
		} else if(opt==2) {
			int g,x;
			scanf("%d %d", &g, &x);
			printf("%lld\n", (sgt.query(1,0,n,g)+(x-1)*gap.query(1,0,n,g)%MOD)%MOD);
		} else {
			LL x;
			scanf("%lld", &x);
			if(x==0) {
				printf("%d\n", zero);
				continue;
			}
			int ans=cnt;
			for(int j=bom;j>=0;j--) {
				if(x>=v[j].back()) {
					x-=v[j].back();
					ans-=v[j].size();
					if(x&1) break;
					else x>>=1;
				} else {
					x=v[j].back()-x;
					int t=lower_bound(v[j].begin(),v[j].end(),x)-v[j].begin();
					ans-=v[j].size()-t;
					break;
				}
			}
			printf("%d\n", ans+1);
		}
	}
}

int main() {
	int T=1;
	while(T--) {
		solve();
	}
	return 0;
}