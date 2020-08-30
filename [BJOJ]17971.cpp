/*
    Coded with Leachim's ACM Template.
    No error. No warning~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAXN=55;
const int MAXM=1005;

map<pair<int,int>,int> bar;
pair<int,int> mark[MAXN][MAXN];
int pole[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    for(int i=1;i<n;i++) {
        int t,cnt=0;
        for(scanf("%d", &t);t;scanf("%d", &t)) {
            bar[make_pair(t,i)]=++cnt;
        }
    }
    bool del=true;
    while(del) {
        del=false;
        for(int i=1;i<=n;i++) pole[i]=i;
        for(auto pr:bar) {
            int &l=pole[pr.first.second], &r=pole[pr.first.second+1];
            if(l<r) mark[l][r]=pr.first;
            else {
                del=true;
                bar.erase(mark[r][l]);
                bar.erase(pr.first);
                break;
            }
            swap(l,r);
        }
    }
    printf("%lu\n", bar.size());
    for(auto pr:bar) {
        printf("%d %d\n", pr.first.second, pr.second);
    }
}

int main() {
    int T=1,cas=1;(void)(cas);
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}