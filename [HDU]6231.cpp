#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define MAXN 2000005
#define MAXLN 25
#define MOD 1000000007

int n,k;
LL m;
int a[MAXN],b[MAXN];

bool check(int x) {
    vector<int> v;
    v.push_back(0);
    for(int i=1;i<=n;i++) {
        if(a[i]>=x) v.push_back(i);
    }
    LL ans=0;
    for(int i=k;i<v.size();i++) {
        ans+=1LL*(v[i-k+1]-v[i-k])*(n-v[i]+1);
    }
    return ans>=m;
}

void solve() {
    scanf("%d %d %lld", &n, &k, &m);
    for(int i=1;i<=n;i++){
        scanf("%d", &a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    int cnt=unique(b+1,b+1+n)-b-1;
    int l=1,r=cnt;
    while(l<r){
        int mid=(l+r+1)>>1;
        if(check(b[mid])) l=mid;
        else r=mid-1;
    }
    printf("%d\n", b[l]);
}

int main() {
    int T=1;
    scanf("%d", &T);
    while(T--){
        solve();
    }
    return 0;
}