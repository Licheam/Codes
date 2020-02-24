#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100005
using namespace std;

int bit[MAXN],len;

int lowbit(int x){return x&(-x);}
void change(int x,int d){for(;x<=len;x+=lowbit(x)) bit[x]+=d;}
int sum(int x){int r=0;for(;x;x-=lowbit(x)) r+=bit[x];return r;};

struct node{
    int le,ri;
    int mx,tag;
}sgt[MAXN<<2];


int n,q,b[MAXN];

void updata(int cur){
    int le=cur<<1,ri=le+1;
    sgt[le].mx+=sgt[cur].tag;
    sgt[ri].mx+=sgt[cur].tag;
    sgt[le].tag+=sgt[cur].tag;
    sgt[ri].tag+=sgt[cur].tag;
    sgt[cur].tag=0;
}

void modify(int cur,int l,int r){
    if(l<=sgt[cur].le && sgt[cur].ri<=r){
        sgt[cur].mx++;
        sgt[cur].tag++;
    }
    else{
        if(sgt[cur].tag) updata(cur);
        int le=cur<<1,ri=le+1;
        int mid=(sgt[cur].le+sgt[cur].ri)>>1;
        if(l<mid) modify(le,l,r);
        if(r>mid) modify(ri,l,r);
        sgt[cur].mx=max(sgt[le].mx,sgt[ri].mx);
    }
}

void reset(int cur){
    if(sgt[cur].mx) return;
    if(sgt[cur].le==sgt[cur].ri-1){
        change(sgt[cur].le,1);
        sgt[cur].mx=-b[sgt[cur].le];
    }
    else{
        if(sgt[cur].tag) updata(cur);
        int le=cur<<1,ri=le+1;
        if(!sgt[le].mx) reset(le);
        if(!sgt[ri].mx) reset(ri);
        sgt[cur].mx=max(sgt[le].mx,sgt[ri].mx);
    }
}

void built(int cur,int l,int r){
    sgt[cur].le=l;
    sgt[cur].ri=r;
    sgt[cur].tag=0;
    if(l==r-1) sgt[cur].mx=-b[l];
    else{
        int le=cur<<1,ri=le+1;
        int mid=(l+r)>>1;
        built(le,l,mid);
        built(ri,mid,r);
        sgt[cur].mx=max(sgt[le].mx,sgt[ri].mx);
    }
}

int main(){
    while(~scanf("%d %d", &n, &q)){
	    len=n;
	    memset(bit+1,0,n*sizeof(bit[0]));
	    for(int i=1;i<=n;i++)
	        scanf("%d", &b[i]);
	    built(1,1,n+1);
	    while(q--){
	        char opt[10];
	        scanf("%s",opt);
	        if(opt[0]=='a'){
	            int l,r;
	            scanf("%d %d", &l, &r);
	            modify(1,l,r+1);
	            reset(1);
	        }
	        else{
	            int l,r;
	            scanf("%d %d", &l, &r);
	            printf("%d\n", sum(r)-sum(l-1));
	        }

	    }
	}
    return 0;
}