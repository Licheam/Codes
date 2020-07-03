#include <bits/stdc++.h>
#define MAXN 2000005
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-6;

vector<int> v;
bool flag[MAXN];

int gcd(int x,int y) {
    if(!x || !y) return x+y;
    return gcd(y,x%y);
}

int phi(int x) {
    int res=x;
    for(int i=2;i*i<=x;i++) {
        if(x%i==0) {
            res=res/i*(i-1);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) res=res/x*(x-1);
    return res;
}

void solve() {
    v.clear();
    int n,m;
    scanf("%d %d", &n, &m);
    for(int i=1;i*i<=m;i++) {
        if(m%i==0) {
            v.push_back(i);
            if(i*i!=m && i!=1) v.push_back(m/i);
        }
    }
    memset(flag,0,v.size()*sizeof(flag[0]));
    LL ans=0;
    for(int i=1;i<=n;i++) {
        int a;
        scanf("%d", &a);
        a=gcd(m,a);
        for(int j=0;j<v.size();j++) {
            if(v[j]%a==0 && !flag[j]){
                flag[j]=1;
                ans+=1LL*m*phi(m/v[j])/2;
            }
        }
    }
    printf("%lld\n", ans);
}

int main() {
    int T=1,cas=1;
    scanf("%d", &T);
    while(T--) {
        printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}