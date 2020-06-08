#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define MAXN 2000005
#define MOD 1000000007
const int inf=0x3f3f3f3f;

int n;

LL binpow(LL x,LL y,LL m){
    LL r=1%m;
    while(y){
        if(y&1)
            r=r*x%m;
        x=x*x%m;
        y>>=1;
    }
    return r;
}

double calc(int x,int k) {
    double r=0;
    for(int i=0;i<=n-1;i++) {
        r+=(double)binpow(16,n-1-i,8*i+x)*k/(8*i+x);
    }
    return r;
}

void solve() {
    scanf("%d", &n);
    double ans=calc(1,4)-calc(4,2)-calc(5,1)-calc(6,1);
    ans-=(int)ans;
    ans+=1;
    ans-=(int)ans;
    int digit=(int)(ans*16)%16;
    printf("%d %c\n",n,digit>9?digit-10+'A':digit+'0');
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