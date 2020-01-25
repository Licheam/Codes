#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n;

set<int> e[MAXN];
set<int>::iterator it;
list<pair<int,int>> ans;
list<pair<int,int>>::iterator ite;

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		e[i].insert(i+1>n?i+1-n:i+1);
		e[i].insert(i-1<1?i-1+n:i-1);
		// cout<<(i+1>n?i+1-n:i+1)<<' '<<(i-1<1?i-1+n:i-1)<<endl;
	}
	for(int i=1;i<=n-3;i++){
		int f,g;
		scanf("%d %d", &f, &g);
		e[f].insert(g);
		e[g].insert(f);
	}
	it=e[1].begin();
	for(int u=*it,v=1;it!=e[1].end();v=u,u=*++it){
		if(u-v>1){
			e[u].erase(v);
			e[v].erase(u);
			ans.push_back(make_pair(u,v));
			it--;
			e[1].insert(it,*--e[v].lower_bound(u));
			u=v;

		}
	}
	for(int i=1;i<=n;i++){
		e[i].clear();
		e[i].insert(i+1>n?i+1-n:i+1);
		e[i].insert(i-1<1?i-1+n:i-1);
	}
	for(int i=1;i<=n-3;i++){
		int f,g;
		scanf("%d %d", &f, &g);
		e[f].insert(g);
		e[g].insert(f);
	}
	it=e[1].begin();
	ite=ans.end();
	for(int u=*it,v=1;it!=e[1].end();v=u,u=*++it){
		if(u-v>1){
			e[u].erase(v);
			e[v].erase(u);
			it--;
			ite=ans.insert(ite,make_pair(1,*e[1].insert(it,*--e[v].lower_bound(u))));
			u=v;
		}
	}
	printf("%lu\n", ans.size());
	for(auto p:ans){
		printf("%d %d\n",p.first,p.second);
	}
	return 0;
}