#include <cstdio>
#include <algorithm>
#define MAXN 500005
#define MAXT 2000005

using namespace std;

struct node{
	int le,ri;
	int lmax,rmax,mmax,sum;
}sgt[MAXT];

void change(int cur,int p,int s){
	if(sgt[cur].le==sgt[cur].ri-1){
		sgt[cur].lmax=sgt[cur].rmax=sgt[cur].mmax=sgt[cur].sum=s;
	}
	else{
		int le=cur<<1,ri=le|1;
		int mid=(sgt[cur].le+sgt[cur].ri)>>1;
		if(p<mid){
			change(cur<<1,p,s);
		}
		else change(cur<<1|1,p,s);
		sgt[cur].lmax=max(sgt[le].lmax,sgt[le].sum+sgt[ri].lmax);
		sgt[cur].rmax=max(sgt[ri].rmax,sgt[ri].sum+sgt[le].rmax);
		sgt[cur].mmax=max(max(sgt[le].mmax,sgt[ri].mmax),sgt[le].rmax+sgt[ri].lmax);
		sgt[cur].sum=sgt[le].sum+sgt[ri].sum;
	}
}

node query(int cur,int l,int r){
	if(l<=sgt[cur].le && sgt[cur].ri<=r)
		return sgt[cur];
	int mid=(sgt[cur].le+sgt[cur].ri)>>1;
	if(r<=mid)
		return query(cur<<1,l,r);
	else if(l>=mid)
		return query(cur<<1|1,l,r);
	else{
		node t,tl=query(cur<<1,l,r),tr=query(cur<<1|1,l,r);
		t.lmax=max(tl.lmax,tl.sum+tr.lmax);
		t.rmax=max(tr.rmax,tr.sum+tl.rmax);
		t.mmax=max(max(tl.mmax,tr.mmax),tl.rmax+tr.lmax);
		t.sum=tl.sum+tr.sum;
		return t;
	}

}

int a[MAXN];

void build(int cur,int l,int r){
	sgt[cur].le=l;
	sgt[cur].ri=r;
	if(l==r-1){
		sgt[cur].lmax=sgt[cur].rmax=sgt[cur].mmax=sgt[cur].sum=a[l];
	}
	else{
		int le=cur<<1,ri=le|1;
		build(le,l,(l+r)>>1);
		build(ri,(l+r)>>1,r);
		sgt[cur].lmax=max(sgt[le].lmax,sgt[le].sum+sgt[ri].lmax);
		sgt[cur].rmax=max(sgt[ri].rmax,sgt[ri].sum+sgt[le].rmax);
		sgt[cur].mmax=max(max(sgt[le].mmax,sgt[ri].mmax),sgt[le].rmax+sgt[ri].lmax);
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
		int k;scanf("%d", &k);
		if(k==1){
			int l,r;
			scanf("%d %d", &l, &r);
			if(l>r)swap(l,r);
			printf("%d\n", query(1,l,r+1).mmax);
		}
		else{
			int p,s;
			scanf("%d %d", &p, &s);
			change(1,p,s);
		}
	}
	return 0;
}