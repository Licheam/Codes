#include <bits/stdc++.h>
#define MAXN 200005

const int inf=0x3f3f3f3f;

using namespace std;

int n;
pair<int,int> a[MAXN];

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		int x,w;
		scanf("%d %d", &x,&w);
		a[i]=make_pair(x+w,x-w);
	}
	sort(a+1,a+n+1);
	int last=-inf,ans=0;
	for(int i=1;i<=n;i++){
		if(last<=a[i].second){
			last=a[i].first;
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}