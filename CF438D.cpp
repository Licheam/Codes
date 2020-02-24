#include <cstdio>
#include <algorithm>
#define LL long long
#define MAXN 100005

using namespace std;

struct node{
	int le,ri;
	int mx;
	LL sum;
}sgt[MAXN<<2];

int a[MAXN];

void module(int cur,int l,int r,int x){
	if(sgt[cur].le==sgt[cur].ri-1){
		sgt[cur].sum=sgt[cur].mx%=x;
	}
	else{
		int le=cur<<1, ri=le+1;
		int mid=(sgt[cur].le+sgt[cur].ri)>>1;
		if(l<mid && sgt[le].mx>=x) module(le,l,r,x);
		if(r>mid && sgt[ri].mx>=x) module(ri,l,r,x);
		sgt[cur].mx=max(sgt[le].mx,sgt[ri].mx);
		sgt[cur].sum=sgt[le].sum+sgt[ri].sum;
	}
}

void modify(int cur,int k,int x){
	if(sgt[cur].le==sgt[cur].ri-1){
		sgt[cur].sum=sgt[cur].mx=x;
	}
	else{
		int le=cur<<1,ri=le+1;
		int mid=(sgt[cur].le+sgt[cur].ri)>>1;
		if(k<mid) modify(le,k,x);
		else modify(ri,k,x);
		sgt[cur].mx=max(sgt[le].mx,sgt[ri].mx);
		sgt[cur].sum=sgt[le].sum+sgt[ri].sum;
	}
}

LL query(int cur,int l,int r){
	if(l<=sgt[cur].le && sgt[cur].ri<=r){
		return sgt[cur].sum;
	}
	else{
		int le=cur<<1,ri=le+1;
		int mid=(sgt[cur].le+sgt[cur].ri)>>1;
		LL res=0;
		if(l<mid) res+=query(le,l,r);
		if(mid<r) res+=query(ri,l,r);
		return res;
	}
}

void build(int cur,int l,int r){
	sgt[cur].le=l;
	sgt[cur].ri=r;
	if(l==r-1) sgt[cur].sum=sgt[cur].mx=a[l];
	else{
		int le=cur<<1,ri=le+1;
		build(le,l,(l+r)>>1);
		build(ri,(l+r)>>1,r);
		sgt[cur].mx=max(sgt[le].mx,sgt[ri].mx);
		sgt[cur].sum=sgt[le].sum+sgt[ri].sum;
	}
}

int n,m;
int main(){
	scanf("%d %d", &n, &m);
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	build(1,1,n+1);
	for(int i=1;i<=m;i++){
		int opt;
		scanf("%d", &opt);
		if(opt==1){
			int l,r;
			scanf("%d %d", &l, &r);
			printf("%lld\n",query(1,l,r+1));
		}
		else if(opt==2){
			int l,r,x;
			scanf("%d %d %d", &l, &r, &x);
			module(1,l,r+1,x);
		}
		else{
			int k,x;
			scanf("%d %d", &k, &x);
			modify(1,k,x);
		}
	}
	return 0;
}