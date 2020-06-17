// #include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>
using namespace std;
#define LL long long
#define MAXN 1005
const double eps=1e-6;

int a[MAXN],b[MAXN];
double d[MAXN];

void solve() {
    int n,k;
    while(~scanf("%d %d", &n, &k)){
        if(!n && !k) return;
        for(int i=1;i<=n;i++)
            scanf("%d", &a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d", &b[i]);

        double l=0,r=1;
        while(r-l>eps) {
            double mid=(l+r)/2;
            for(int i=1;i<=n;i++)
                d[i]=a[i]-mid*b[i];
            sort(d+1,d+1+n);
            double sum=0;
            for(int i=k+1;i<=n;i++)
                sum+=d[i];
            if(sum>0) l=mid;
            else r=mid;
        }
        printf("%.0lf\n",l*100);
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