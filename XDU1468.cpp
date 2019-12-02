#include <cstdio>
#include <set>
#define MAXN 100005

using namespace std;

set<int> sb;

int n,p,sum[MAXN][3];

int main(){
    scanf("%d %d", &n, &p);
    for(int i=0;i<3;i++){
        sum[0][i]=0;
        for(int j=1;j<=n;j++){
            int t;
            scanf("%d",&t);
            sum[j][i]=(sum[j-1][i]+t)%p;
        }
    }
    int mx=0;
    for(int i=n;i;i--){
        int b,a=((sum[n][2]+sum[i][0]-sum[i-1][1])%p+p)%p;//b=sum[j][1]-sum[j-1][2]
        sb.insert(((sum[i][1]-sum[i-1][2])%p+p)%p);
        set<int>::iterator ite=sb.lower_bound(p-a);
        if(ite==sb.begin()){
            ite=sb.end();
        }
        ite--;
        b=*ite;
        if(mx<(a+b)%p)
            mx=(a+b)%p;
    }
    printf("%d\n", mx);
    return 0;
}