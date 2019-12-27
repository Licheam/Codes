#include <cstdio>
#include <algorithm>
#define MAXN 200005

using namespace std;

int T,n,p,k,a[MAXN],dp[MAXN];

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %d", &n, &p ,&k);
        for(int i=1;i<=n;i++)
            scanf("%d", &a[i]);
        sort(a+1,a+n+1);
        int ans=0;
        for(int i=1;i<=n;i++){
            dp[i]=a[i]+dp[i-1];
            if(i-k>=0)
                dp[i]=min(dp[i],a[i]+dp[i-k]);
            if(dp[i]<=p) ans=i;
        }
        printf("%d\n", ans);
    }
    return 0;
}