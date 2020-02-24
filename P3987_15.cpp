#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#define M 500000
#define MAXN 100005
#define MAXM 500005
#define MAXS 105
#define LL long long
using namespace std;

LL n;
LL bit[MAXN];

LL lowbit(LL x){return x&(-x);}
void change(LL x,LL d){for(;x<=n;x+=lowbit(x)) bit[x]+=d;}
LL sum(LL x){LL r=0;for(;x;x-=lowbit(x)) r+=bit[x];return r;}

struct node{
	int v,fa,ch[2],cnt;
	LL size;
}sp[MAXM*MAXS];

LL a[MAXN],len,recy[MAXM*MAXS],rlen;

LL getch(LL x){return sp[sp[x].fa].ch[1]==x;}
void pushup(LL x){sp[x].size=sp[sp[x].ch[0]].size+sp[sp[x].ch[1]].size+sp[x].cnt;}

void rotate(LL x){
	LL f=sp[x].fa, ff=sp[f].fa;
	LL k=getch(x);
	sp[ff].ch[getch(f)]=x; sp[x].fa=ff;
	sp[sp[x].ch[k^1]].fa=f; sp[f].ch[k]=sp[x].ch[k^1];
	sp[x].ch[k^1]=f; sp[f].fa=x;
	pushup(f); pushup(x);
}

void splay(LL x,LL goal,LL &root){
	for(LL f;(f=sp[x].fa)!=goal;rotate(x)){
		if(sp[f].fa!=goal)
			rotate(getch(x)==getch(f)?f:x);
	}
	if(!goal) root=x;
}

LL find(LL x,LL &root){
	LL cur=root;
	while(x!=sp[cur].v && sp[cur].ch[sp[cur].v<x])
		cur=sp[cur].ch[sp[cur].v<x];
	splay(cur,0,root);
	return cur;
}

LL succ(LL x,LL &root){
	find(x,root);
	if(x<sp[root].v) return root;

	LL cur=sp[root].ch[1];
	while(sp[cur].ch[0])
		cur=sp[cur].ch[0];
	return cur;
}

LL pre(LL x,LL &root){
	find(x,root);
	if(x>sp[root].v) return root;

	LL cur=sp[root].ch[0];
	while(sp[cur].ch[1])
		cur=sp[cur].ch[1];
	return cur;
}

void recycle(LL cur,LL x,LL &root,vector<LL> v){
	if(!cur) return;
	recycle(sp[cur].ch[0],x,root,v);
	if(a[sp[cur].v]%x==0){
		change(sp[cur].v,a[sp[cur].v]/x-a[sp[cur].v]);
		a[sp[cur].v]/=x;
		if(a[sp[cur].v]%x==0)
			v.push_back(sp[cur].v);
	}
	recy[++rlen]=cur;
	recycle(sp[cur].ch[1],x,root,v);
}

LL build(LL f,LL l,LL r,vector<LL>& v){
	if(l>r) return 0;
	LL mid=(l+r)>>1,cur=rlen?recy[rlen--]:++len;
	sp[cur].v=v[mid];
	sp[cur].fa=f;
	sp[cur].cnt=1;
	sp[cur].ch[0]=build(cur,l,mid-1,v);
	sp[cur].ch[1]=build(cur,mid+1,r,v);
	pushup(cur);
	return cur;
}

void modify(LL l,LL r,LL x,LL &root){
	LL last=pre(l,root), next=succ(r,root);

	// printf("\n%lld %lld\n", l,r);
	// printf("\n%lld %lld\n", sp[last].v,sp[next].v);

	splay(last,0,root);
	splay(next,last,root);
	vector<LL> v;
	recycle(sp[next].ch[0],x,root,v);
	sp[next].ch[0]=build(sp[next].ch[0],0,v.size()-1,v);
}

LL m,root[MAXM],last;
vector<LL> v[MAXM];

void decompose(LL x){
	for(LL i=2;i*i<=a[x];i++){
		if(a[x]%i==0){
			v[i].push_back(x);
			if(i*i!=a[x])
				v[a[x]/i].push_back(x);
		}
	}
	if(a[x]>1) v[a[x]].push_back(x);
}

int main(){
	scanf("%lld %lld", &n, &m);
	for(LL i=2;i<=M;i++)
		v[i].push_back(0);
	memset(bit+1,0,n*sizeof(bit[0]));
	for(LL i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		change(i,a[i]);
		decompose(i);
	}
	rlen=0;
	len=0;
	memset(sp,0,sizeof(sp[0]));
	for(LL i=2;i<=M;i++){
		v[i].push_back(n+1);
		root[i]=build(0,0,v[i].size()-1,v[i]);
	}
	LL last=0;
	for(LL i=1;i<=m;i++){
		LL opt;
		scanf("%lld", &opt);
		if(opt==1){
			LL l,r,x;
			scanf("%lld %lld %lld", &l, &r, &x);
			// l^=last; r^=last; x^=last;
			if(x!=1) modify(l,r,x,root[x]);

			// for(LL i=1;i<=n;i++){
			// 	printf("%lld ", a[i]);
			// }
			// puts("");
		}
		else{
			LL l,r;
			scanf("%lld %lld", &l, &r);
			// l^=last; r^=last;
			printf("%lld\n", last=sum(r)-sum(l-1));
		}
	}
	return 0;
}