#include <bits/stdc++.h>
#define LL long long
#define MAXN 500005
using namespace std;

LL m[MAXN],ls[MAXN],rs[MAXN];
stack<int> st;

void solve(){
	int n;
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
		scanf("%lld", &m[i]);
	for(int i=1;i<=n;i++){
		while(!st.empty() && m[st.top()]>m[i])
			st.pop();
		if(!st.empty()) ls[i]=ls[st.top()]+m[i]*(i-st.top());
		else ls[i]=m[i]*i;
		st.push(i);
	}
	st=stack<int>();
	for(int i=n;i>=1;i--){
		while(!st.empty() && m[i]<m[st.top()])
			st.pop();
		if(!st.empty()) rs[i]=rs[st.top()]+m[i]*(st.top()-i);
		else rs[i]=m[i]*(n-i+1);
		st.push(i);
	}
	LL mx=0,mi=0;
	for(int i=n;i>=1;i--)
		if(ls[i]+rs[i]-m[i]>mx)
			mx=ls[i]+rs[i]-m[i], mi=i;
	for(int i=mi-1;i>=1;i--)
		m[i]=min(m[i],m[i+1]);
	for(int i=mi+1;i<=n;i++)
		m[i]=min(m[i],m[i-1]);
	for(int i=1;i<=n;i++)
		printf("%lld ", m[i]);
}

int main(){
	int T=1;
	// scanf("%d", &T);
	while(T--){
		solve();
	}
	return 0;
}