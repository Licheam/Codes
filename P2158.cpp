#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define MAXN 2000005

int p[MAXN],cnt;
bool inp[MAXN];
int phi[MAXN],sphi[MAXN];


void es(int n) {
    memset(inp+1,0,n*sizeof(inp[0]));
    inp[0]=inp[1]=1;
    cnt=0;
    sphi[1]=phi[1]=1;
    for(int i=2;i<=n;i++) {
        if(!inp[i]) p[++cnt]=i, phi[i]=i-1;
        for(int j=1;j<=cnt && i*p[j]<=n;j++) {
            inp[i*p[j]]=1;
            if(i%p[j]) {
                phi[i*p[j]]=phi[i]*(p[j]-1);
            } else {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
        }
        sphi[i]=sphi[i-1]+phi[i];
    }
}


void solve() {
    int n;
    scanf("%d", &n);
    if(n==1){
        printf("0\n");
        return;
    }
    es(n-1);
    printf("%lld\n", 2LL*(sphi[n-1]-1)+3);
}

int main() {
    int T=1;
    // scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}