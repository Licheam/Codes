#include <bits/stdc++.h>
#define MAXN 5005
#define LL long long
using namespace std;

int a[MAXN][MAXN],ans[MAXN][MAXN];

void solve() {
    int n,m,k;
    scanf("%d %d %d", &n, &m, &k);

    memset(a,0,sizeof(a));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!a[i][j])
                for(int k=1;k*i<=n && k*j<=m;k++)
                    a[k*i][k*j]=i*j*k;

    for(int i=1;i<=n;i++) {
        deque<int> Q;
        for(int j=1;j<=m;j++) {
            while(!Q.empty() && a[i][Q.back()]<a[i][j]) Q.pop_back();
            if(!Q.empty() && Q.front()<=j-k) Q.pop_front();
            Q.push_back(j);
            ans[i][j]=a[i][Q.front()];
        }
    }
    swap(ans,a);
    for(int j=k;j<=m;j++) {
        deque<int> Q;
        for(int i=1;i<=n;i++) {
            while(!Q.empty() && a[Q.back()][j]<a[i][j]) Q.pop_back();
            if(!Q.empty() && Q.front()<=i-k) Q.pop_front();
            Q.push_back(i);
            ans[i][j]=a[Q.front()][j];
        }
    }

    LL sum=0;
    for(int i=k;i<=n;i++)
        for(int j=k;j<=m;j++)
            sum+=ans[i][j];

    printf("%lld\n", sum);
}

int main() {
    int T=1,cas=1;
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}