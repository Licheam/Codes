#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL T;

struct edge{
	int x1,y1,x2,y2;
	edge(int x1,int y1,int x2,int y2)
		:x1(x1),y1(y1),x2(x2),y2(y2){}
};

vector<edge> v;

void seal(int p,int x){
	switch(x){
		case 0:
		v.push_back(edge(p-1,p+2,p,p+2));
		v.push_back(edge(p-1,p+1,p,p+1));
		v.push_back(edge(p+1,p-1,p+1,p));
		v.push_back(edge(p+2,p-1,p+2,p));
		break;
		case 1:
		v.push_back(edge(p-1,p+1,p,p+1));
		v.push_back(edge(p+1,p-1,p+1,p));
		v.push_back(edge(p+2,p-1,p+2,p));
		break;
		case 2:
		v.push_back(edge(p-1,p+1,p,p+1));
		v.push_back(edge(p+1,p-1,p+1,p));
		break;
		case 3:
		v.push_back(edge(p-1,p+2,p,p+2));
		v.push_back(edge(p+1,p-1,p+1,p));
		v.push_back(edge(p+2,p-1,p+2,p));
		break;
		case 4:
		v.push_back(edge(p+1,p-1,p+1,p));
		v.push_back(edge(p+2,p-1,p+2,p));
		break;
		case 5:
		v.push_back(edge(p+1,p-1,p+1,p));
		break;
	}
}

int main(){
	scanf("%lld", &T);
	stack<int> s;
	while(T){
		s.push(T%6);
		T/=6;
	}
	v.push_back(edge(1,2,2,2));
	v.push_back(edge(2,1,2,2));
	int n=2;
	while(!s.empty()){
		seal(n,s.top());s.pop();
		if(!s.empty()){
			v.push_back(edge(n+2,n,n+3,n));
			v.push_back(edge(n+2,n+1,n+3,n+1));
			v.push_back(edge(n+3,n-1,n+4,n-1));
			v.push_back(edge(n+3,n,n+4,n));
			v.push_back(edge(n,n+2,n,n+3));
			v.push_back(edge(n+1,n+2,n+1,n+3));
			v.push_back(edge(n-1,n+3,n-1,n+4));
			v.push_back(edge(n,n+3,n,n+4));
		}
		n+=2;
	}
	printf("%d %d\n",n,n);
	printf("%lu\n", v.size());
	for(auto e:v){
		printf("%d %d %d %d\n", e.x1,e.y1,e.x2,e.y2);
	}
	return 0;
}