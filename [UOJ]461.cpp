#include <bits/stdc++.h>
#include "graph.h"


std::vector<int> check_bipartite(int vsize){
	const int MAXN=205;
	int n=vsize;
	bool flag[MAXN];
	int color[MAXN];
	std::set<std::pair<int,int> > tree_edges;
	std::vector<std::pair<int,int> > del_edges;
	std::vector<int> nodes[2];
	memset(flag,0,n*sizeof(flag[0]));
	memset(color,-1,n*sizeof(color[0]));
	std::queue<int> q;
	color[0]=0;
	q.push(0);
	flag[0]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		nodes[color[u]].push_back(u);
		std::vector<std::pair<int,int> > bi_edges;
		for(int v=0;v<n;v++){
			if(flag[v]) continue;
			bi_edges.push_back(std::make_pair(u,v));
		}
		int ll=0;
		while(ll<bi_edges.size()){
			int l=ll,r=bi_edges.size()-1;
			std::vector<std::pair<int,int> > qry_edges=del_edges;
			qry_edges.insert(qry_edges.end(),bi_edges.begin()+l,bi_edges.begin()+r+1);
			if(query(qry_edges)){
				del_edges.insert(del_edges.end(),bi_edges.begin()+l,bi_edges.begin()+r+1);
				break;
			}
			while(l<r){
				int mid=(l+r)>>1;
				qry_edges=del_edges;
				qry_edges.insert(qry_edges.end(),bi_edges.begin()+l,bi_edges.begin()+mid+1);
				if(!query(qry_edges)){//is cut edges
					r=mid;
				}
				else{
					del_edges.insert(del_edges.end(),bi_edges.begin()+l,bi_edges.begin()+mid+1);
					l=mid+1;
				}
			}
			int v=bi_edges[l].second;
			color[v]=color[u]^1;
			q.push(v);
			tree_edges.insert(std::make_pair(std::min(u,v),std::max(u,v)));
			flag[v]=1;
			ll=l+1;
		}
	}
	std::vector<std::pair<int,int> > qry_edges;
	for(int u:nodes[0]){
		for(int v:nodes[1]){
			if(tree_edges.find(std::make_pair(std::min(u,v),std::max(u,v)))==tree_edges.end()){
				qry_edges.push_back(std::make_pair(u,v));
			}
		}
	}
	bool isbi=1;
	for(auto edge:tree_edges){
		qry_edges.push_back(edge);
		if(query(qry_edges)){
			isbi=0;
			break;
		}
		qry_edges.pop_back();
	}
	if(isbi){
		return nodes[0];
	}
	else return std::vector<int>();
}