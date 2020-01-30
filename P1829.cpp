#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define MAXN 10000005
#define MOD 20101009

using namespace std;

int n,m,lim;
int p[MAXN],cnt;
bool inp[MAXN];

LL vid[MAXN],svid[MAXN];//vid=(n^2*mu(n))*id

void pre(){
    memset(inp+1,0,lim*sizeof(inp[0]));
    inp[0]=inp[1]=1;
    cnt=0;
    svid[0]=0;
    svid[1]=vid[1]=1;
    for(LL i=2;i<=lim;i++){
        if(!inp[i]) p[++cnt]=i, vid[i]=((1-i)*i%MOD+MOD)%MOD;
        for(LL j=1;j<=cnt && i*p[j]<=lim;j++){
            inp[i*p[j]]=1;
            if(i%p[j]){
                vid[i*p[j]]=vid[p[j]]*vid[i]%MOD;
            }
            else{
                vid[i*p[j]]=vid[i]*p[j]%MOD;
                break;
            }
        }
        svid[i]=(svid[i-1]+vid[i])%MOD;
    }
}

LL sum(LL x){
    return x*(x+1)/2%MOD;
}

int main(){
    scanf("%d %d", &n, &m);
    lim=min(n,m);
    pre();
    LL ans=0;
    for(LL i=1;i<=lim;i++){
        LL j=min(n/(n/i),m/(m/i));
        ans=(ans+(svid[j]-svid[i-1]+MOD)*((sum(n/i)*sum(m/i))%MOD)%MOD)%MOD;
        i=j;
    }
    printf("%lld\n", ans);
    return 0;
}