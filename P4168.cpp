#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
#define MAXN 40005
#define MAXB 205

using namespace std;

int n,q,blo,id,v[MAXN],bl[MAXN],val[MAXN],cnt[MAXN];
int mo[MAXB][MAXB];
map<int,int> mp;
vector<int> po[MAXN];

void pre(){
	for(int i=1;i<=n;i++){
		if(!mp[v[i]]){
			id++;
			mp[v[i]]=id;
			val[id]=v[i];
		}
		v[i]=mp[v[i]];
		po[v[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
		bl[i]=(i-1)/blo+1;
	memset(mo,0,sizeof(mo));
	for(int i=1;i<=bl[n];i++){
		memset(cnt+1,0,id*sizeof(cnt[0]));
		int mx=0,mxid=0;
		for(int j=(i-1)*blo+1;j<=n;j++){
			cnt[v[j]]++;
			if(cnt[v[j]]>mx || (cnt[v[j]]==mx && val[v[j]]<val[mxid])){
				mx=cnt[v[j]];
				mxid=v[j];
			}
			mo[i][bl[j]]=mxid;
		}
	}
}

int count(int l,int r,int x){
	return upper_bound(po[x].begin(),po[x].end(),r)-lower_bound(po[x].begin(),po[x].end(),l);
}

int query(int l,int r){
	int mxid,mx;
	mxid=mo[bl[l]+1][bl[r]-1];
	mx=count(l,r,mxid);
	if(bl[l]==bl[r]){
		for(int i=l;i<=r;i++){
			int t=count(l,r,v[i]);
			if(t>mx || (t==mx && val[v[i]]<val[mxid])){
				mx=t;
				mxid=v[i];
			}
		}
	}
	else{
		for(int i=l;i<=bl[l]*blo;i++){
			int t=count(l,r,v[i]);
			if(t>mx || (t==mx && val[v[i]]<val[mxid])){
				mx=t;
				mxid=v[i];
			}
		}
		for(int i=(bl[r]-1)*blo+1;i<=r;i++){
			int t=count(l,r,v[i]);
			if(t>mx || (t==mx && val[v[i]]<val[mxid])){
				mx=t;
				mxid=v[i];
			}
		}
	}
	return mxid;
}

int main(){
	scanf("%d %d", &n, &q);blo=sqrt(n);
	id=0;
	for(int i=1;i<=n;i++)
		scanf("%d", &v[i]);
	pre();
	int last=0;
	for(int i=1;i<=q;i++){
		int l,r;
		scanf("%d %d", &l, &r);
		l=(l+last-1)%n+1;r=(r+last-1)%n+1;
		if(l>r)swap(l,r);
		printf("%d\n", last=val[query(l,r)]);
	}
	return 0;
}