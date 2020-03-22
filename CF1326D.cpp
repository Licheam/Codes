#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define MAXN 1000005

char s[MAXN],rs[MAXN],ss[MAXN<<1];
int nxt[MAXN<<1];

void solve(){
	scanf("%s", s);
	int len=strlen(s),x;
	for(x=0;x<len/2;x++)
		if(s[x]!=s[len-x-1]) break;
	if(x==len/2){
		printf("%s\n", s);
		return;
	}
	int n=len-2*x;
	int mx1=0;
	for(int i=0;i<n;i++){
		ss[i]=s[x+i];
		ss[n+i+1]=s[x+n-i-1];
	}
	ss[n]='#';
	nxt[0]=-1;
	for(int i=1,k=-1;i<=2*n+1;i++){
		while(k!=-1 && ss[k]!=ss[i-1])
			k=nxt[k];
		nxt[i]=++k;
	}
	mx1=nxt[2*n+1];
	int mx2=0;
	for(int i=0;i<n;i++){
		ss[i]=s[x+n-i-1];
		ss[n+i+1]=s[x+i];
	}
	ss[n]='#';
	nxt[0]=-1;
	for(int i=1,k=-1;i<=2*n+1;i++){
		while(k!=-1 && ss[k]!=ss[i-1])
			k=nxt[k];
		nxt[i]=++k;
	}
	mx2=nxt[2*n+1];
	if(mx1>=mx2){
		for(int i=0;i<x+mx1;i++){
			putchar(s[i]);
		}
		for(int i=x-1;i>=0;i--)
			putchar(s[i]);
		puts("");
	}
	else{
		for(int i=len-1;i>len-x-1-mx2;i--){
			putchar(s[i]);
		}
		for(int i=x-1;i>=0;i--)
			putchar(s[i]);
		puts("");
	}
}


int main(){
	int T=1;
	scanf("%d\n", &T);
	while(T--){
		solve();
	}
	return 0;
}