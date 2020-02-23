#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#define M 500000
#define MAXN 100005
#define MAXM 500005
#define MAXS 20
#define LL long long
using namespace std;

int n;
LL bit[MAXN];

int lowbit(int x){return x&(-x);}
void change(int x,LL d){for(;x<=n;x+=lowbit(x)) bit[x]+=d;}
LL sum(int x){LL r=0;for(;x;x-=lowbit(x)) r+=bit[x];return r;}

struct node{
	int v,fa,ch[2],cnt;
	int size;
}sp[MAXM*MAXS];

int a[MAXN],len;

int getch(int x){return sp[sp[x].fa].ch[1]==x;}
void pushup(int x){sp[x].size=sp[sp[x].ch[0]].size+sp[sp[x].ch[1]].size+sp[x].cnt;}

void rotate(int x){
	int f=sp[x].fa, ff=sp[f].fa;
	int k=sp[f].ch[1]==x;
	sp[ff].ch[getch(f)]=x; sp[x].fa=ff;
	sp[sp[x].ch[k^1]].fa=f; sp[f].ch[k]=sp[x].ch[k^1];
	sp[x].ch[k^1]=f; sp[f].fa=x;
	pushup(f); pushup(x);
}

void splay(int x,int goal,int &root){
	for(int f;(f=sp[x].fa)!=goal;rotate(x))
		if(sp[f].fa!=goal)
			rotate(getch(x)==getch(f)?f:x);
	if(!goal)
		root=x;
}

// int find(int x,int &root){
// 	int cur=root;
// 	while(1){
// 		if(x<=sp[sp[cur].ch[0]].size)
// 			cur=sp[cur].ch[0];
// 		else if(x>sp[sp[cur].ch[1]].size+sp[cur].cnt){
// 			x-=sp[sp[cur].ch[1]].size+sp[cur].cnt;
// 			cur=sp[cur].ch[1];
// 		}
// 		else return cur;
// 	}
// }

int succ(int cur){
	if(!sp[cur].ch[1]) return sp[cur].fa;
	cur=sp[cur].ch[1];
	while(sp[cur].ch[0]) cur=sp[cur].ch[0];
	return cur;
}

int pre(int cur){
	if(!sp[cur].ch[0]) return sp[cur].fa;
	cur=sp[cur].ch[0];
	while(sp[cur].ch[1]) cur=sp[cur].ch[1];
	return cur;
}

void dfs(int cur,int x,int &root){
	if(!cur) return;
	dfs(sp[cur].ch[0],x,root);
	dfs(sp[cur].ch[1],x,root);
	if(a[sp[cur].v]%x==0){
		change(sp[cur].v,a[sp[cur].v]/x-a[sp[cur].v]);
		a[sp[cur].v]/=x;
	}
	// if(a[sp[cur].v]%x){
	// 	if(sp[cur].ch[1]){
	// 		splay(succ(cur),cur,root);
	// 		sp[sp[cur].fa].ch[getch(cur)]=sp[cur].ch[1];
	// 		sp[sp[cur].ch[1]].fa=sp[cur].fa;
	// 		sp[sp[cur].ch[1]].ch[0]=sp[cur].ch[0];
	// 	}
	// 	else{
	// 		sp[sp[cur].fa].ch[getch(cur)]=sp[cur].ch[0];
	// 		sp[sp[cur].ch[0]].fa=sp[cur].fa;
	// 	}
	// }
}

int findv(int x,int &root){
	int cur=root;
	while(x!=sp[cur].v && sp[cur].ch[sp[cur].v<x])
		cur=sp[cur].ch[sp[cur].v<x];
	return cur;
}

void modify(int l,int r,int x,int &root){
	int ll=findv(l,root), rr=findv(r,root);
	if(sp[ll].v>=l) ll=pre(ll);
	if(sp[rr].v<=r) rr=succ(rr);
	splay(ll,0,root); splay(rr,ll,root);
	dfs(sp[rr].ch[0],x,root);
}

int m,root[MAXM],last;
vector<int> v[MAXM];

int built(int f,int l,int r,int x){
	if(l>r) return 0;
	int mid=(l+r)>>1,cur=++len;
	sp[cur].v=v[x][mid];
	sp[cur].fa=f;
	sp[cur].cnt=1;
	sp[cur].ch[0]=built(cur,l,mid-1,x);
	sp[cur].ch[1]=built(cur,mid+1,r,x);
	pushup(cur);
	return cur;
}

void decompose(int x){
	int t=a[x];
	for(int i=2;i<=sqrt(t)+0.5;i++){
		if(t%i==0){
			v[i].push_back(x);
			while(t%i==0) t/=i;
		}
	}
	if(t>1) v[t].push_back(x);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=2;i<=M;i++)
		v[i].push_back(0);
	memset(bit+1,0,n*sizeof(bit[0]));
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		change(i,a[i]);
		decompose(i);
	}
	len=0;
	memset(sp,0,sizeof(sp[0]));
	for(int i=2;i<=M;i++){
		v[i].push_back(n+1);
		root[i]=built(0,0,v[i].size()-1,i);
	}
	LL last=0;
	for(int i=1;i<=m;i++){
		int opt;
		scanf("%d", &opt);
		if(opt==1){
			LL l,r,x;
			scanf("%lld %lld %lld", &l, &r, &x);
			// l^=last; r^=last; x^=last;
			if(x!=1) modify(l,r,x,root[x]);

			// for(int i=1;i<=n;i++){
			// 	printf("%d ", a[i]);
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