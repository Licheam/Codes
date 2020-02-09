#include <cstdio>
#include <cstdlib>
#include <ctime>
#define LL long long
#define MAXN 100005
#define MAXT 400005

struct node{
	int le,ri;
	LL cnt,mxl,mxi;
}sgt[MAXT];

int count(int cur,LL mxl,LL mxi){
	if(mxl*sgt[cur].mxi>=sgt[cur].mxl*mxi) return 0;
	if(sgt[cur].le==sgt[cur].ri-1) return 1;
	int le=cur<<1,ri=le|1;
	if(mxl*sgt[le].mxi>=sgt[le].mxl*mxi){
		return count(ri,mxl,mxi);
	}
	else{
		return count(le,mxl,mxi)+sgt[ri].cnt;
	}
}

void change(int cur,LL x,LL y){
	if(sgt[cur].le==sgt[cur].ri-1){
		sgt[cur].mxl=y;
		sgt[cur].cnt=1;
	}
	else{
		int le=cur<<1,ri=le|1;
		int mid=(sgt[cur].le+sgt[cur].ri)>>1;
		if(x<mid) change(le,x,y);
		else change(ri,x,y);
		if(sgt[le].mxl*sgt[ri].mxi>=sgt[ri].mxl*sgt[le].mxi){
			sgt[cur].mxl=sgt[le].mxl;
			sgt[cur].mxi=sgt[le].mxi;
		}
		else{
			sgt[cur].mxl=sgt[ri].mxl;
			sgt[cur].mxi=sgt[ri].mxi;
		}
		sgt[cur].cnt=sgt[le].cnt+(sgt[ri].cnt=count(ri,sgt[le].mxl,sgt[le].mxi));
	}
}

void built(int cur,int l,int r){
	sgt[cur].le=l; sgt[cur].ri=r;
	sgt[cur].cnt=0;
	sgt[cur].mxl=0;
	sgt[cur].mxi=l;
	if(l<r-1){
		built(cur<<1,l,(l+r)>>1);
		built(cur<<1|1,(l+r)>>1,r);
	}
}

int n,m;

int main(){
	srand(time(0));
	scanf("%d %d", &n, &m);
	built(1,1,n+1);
	for(int i=1;i<=m;i++){
		LL x,y;
		scanf("%lld %lld", &x, &y);
		change(1,x,y);
		printf("%lld\n", sgt[1].cnt);
	}
	return 0;
}