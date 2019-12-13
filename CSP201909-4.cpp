#include <cstdio>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <unordered_map>

#define MAXN 30005
#define MAXM 55

using namespace std;

struct com{
	pair<int,int> ti;//type and id
	int score;
	com(int a,int b,int c):ti(make_pair(a,b)),score(c){}
};

struct cmp{
	bool operator()(const com a,const com b)const{
		if(a.score!=b.score)
			return a.score>b.score;
		else if(a.ti.first!=b.ti.first)
			return a.ti.first<b.ti.first;
		else
			return a.ti.second<b.ti.second;
	}
};

int m,n,opt,k[MAXM];

set<com,cmp> s;
unordered_map<int,int> mp[MAXM];
vector<int> ans[MAXM];


int main(){
	scanf("%d %d",&m,&n);
	for(int i=1;i<=n;i++){
		int id,score;
		scanf("%d %d",&id,&score);
		for(int j=0;j<m;j++){
			s.insert(com(j,id,score));
			mp[j].insert(make_pair(id,score));
		}
	}
	scanf("%d",&opt);
	while(opt--){
		int op,type,id,score;
		scanf("%d", &op);
		if(op==1){
			scanf("%d %d %d", &type,&id,&score);
			s.insert(com(type,id,score));
			mp[type].insert(make_pair(id,score));
		}
		else if(op==2){
			scanf("%d %d", &type,&id);
			s.erase(com(type,id,mp[type].find(id)->second));
			mp[type].erase(id);
		}
		else{
			int ks;
			scanf("%d", &ks);
			for(int i=0;i<m;i++){
				scanf("%d",&k[i]);
			}
			for(auto i:s){
				if(!ks) break;
				if(k[i.ti.first]){
					k[i.ti.first]--;
					ans[i.ti.first].push_back(i.ti.second);
					ks--;
				}
			}
			for(int i=0;i<m;i++){
				for(int j:ans[i]){
					printf("%d ", j);
				}

				if(ans[i].empty())
					puts("-1");
				else
					puts("");
				ans[i].clear();
			}
		}
	}
	return 0;
}