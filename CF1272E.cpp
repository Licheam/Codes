#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define MAXN 200005

using namespace std;


int n,a[MAXN],dis[MAXN];
vector<int> g[MAXN];
queue<int> q;


int main(){
	scanf("%d",&n);
	memset(dis,-1,sizeof(dis));
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(i-a[i]>=1){
			g[i-a[i]].push_back(i);
			if((a[i]&1) != (a[i-a[i]]&1))
				dis[i]=1;
		}
		if(i+a[i]<=n){
			g[i+a[i]].push_back(i);
			if((a[i]&1) != (a[i+a[i]]&1))
				dis[i]=1;
		}
		if(dis[i]==1)
			q.push(i);
	}
	//BFS
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int to:g[u]){
			if(dis[to]==-1 && (a[to]&1)==(a[u]&1)){
				dis[to]=dis[u]+1;
				q.push(to);
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ", dis[i]);
	}
	return 0;
}