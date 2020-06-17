// #include <bits/stdc++.h>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
#define LL long long
#define LD long double
#define MAXN 1005
const double eps=1e-6;

int n;
LD e[MAXN][MAXN],d[MAXN][MAXN];
bool flag[MAXN];
int x[MAXN],y[MAXN],al[MAXN];
LD mne[MAXN];
int to[MAXN];


LD dist(int i,int j) {
    return sqrt((LD)(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

LD prim(){
    LD ans=0;
    memset(flag+1,0,n*sizeof(flag[0]));
    for(int i=0;i<=n;i++)
        mne[i]=10000000000;
    flag[1]=1;
    mne[1]=0;
    for(int i=2;i<=n;i++)
        mne[i]=e[1][i], to[i]=1;
    for(int i=1;i<n;i++) {
        int mj=0;
        for(int j=1;j<=n;j++)
            if(!flag[j] && mne[j]<mne[mj]) mj=j;
        ans+=e[to[mj]][mj];
        flag[mj]=1;
        for(int j=1;j<=n;j++)
            if(!flag[j] && e[mj][j]<mne[j]) mne[j]=e[mj][j], to[j]=mj;
    }
    return ans;
}

bool check(LD mid) {
    for(int i=1;i<n;i++) {
        for(int j=i+1;j<=n;j++) {
            e[i][j]=e[j][i]=abs(al[i]-al[j])-mid*d[i][j];
        }
    }
    return prim()<-eps;
}

void solve() {
    while(~scanf("%d", &n)) {
        if(!n) return;
        for(int i=1;i<=n;i++)
            scanf("%d %d %d", &x[i], &y[i], &al[i]);
        for(int i=1;i<n;i++)
            for(int j=i+1;j<=n;j++)
                d[i][j]=d[j][i]=dist(i,j);
        LD l=0,r=10000000000;
        while(r-l>eps) {
            LD mid=(l+r)/2;
            if(check(mid)) r=mid;
            else l=mid;
        }
        printf("%.3Lf\n", l);
    }
}

int main() {
    int T=1;
    // scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}