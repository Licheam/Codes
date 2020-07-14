#include <bits/stdc++.h>
#define MAXN 150005
#define LL long long
using namespace std;

bitset<MAXN> ans,mark;
pair<int,int> a[MAXN],b[MAXN];
void solve() {
    int n,m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++){
        scanf("%d", &a[i].first);
        a[i].second=i;
    }
    for(int i=1;i<=m;i++){
        scanf("%d", &b[i].first);
        b[i].second=i;
    }
    sort(a+1,a+1+n);
    sort(b+1,b+1+m);
    ans.set();
    mark.reset();
    for(int i=m,j=n;i>=1;i--) {
        for(;j && a[j].first>=b[i].first;j--)
            mark.set(a[j].second);
        ans&=(mark>>b[i].second);
    }
    printf("%d\n", ans.count());
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