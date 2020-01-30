#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define LL long long
#define MAXR R+5
#define R 5000000
#define MOD 1000000007
#define rev2 500000004
#define rev6 166666668

using namespace std;

LL n,r;
int p[MAXR],cnt;
bool inp[MAXR];

LL vid[MAXR],svid[MAXR],svidr[MAXR];//vid=(n^2*mu(n))*id

void pre(){
    memset(inp+1,0,r*sizeof(inp[0]));
    inp[0]=inp[1]=1;
    cnt=0;
    svid[0]=0;
    svid[1]=vid[1]=1;
    for(LL i=2;i<=r;i++){
        if(!inp[i]) p[++cnt]=i, vid[i]=(1-i)*i;
        for(LL j=1;j<=cnt && i*p[j]<=r;j++){
            inp[i*p[j]]=1;
            if(i%p[j]){
                vid[i*p[j]]=vid[p[j]]*vid[i];
            }
            else{
                vid[i*p[j]]=vid[i]*p[j];
                break;
            }
        }
        svid[i]=((svid[i-1]+vid[i])%MOD+MOD)%MOD;
    }
}

LL sum(LL x){
    return (x%MOD)*((x+1)%MOD)%MOD*rev2%MOD;
}

LL sum2(LL x){
    return (x%MOD)*((x+1)%MOD)%MOD*((2*x+1)%MOD)%MOD*rev6%MOD;
}

LL sumvid(LL x){
    if(x<=r) return svid[x];
    else if(svidr[n/x]) return svidr[n/x];
    LL &sv=svidr[n/x];
    sv=sum(x);
    for(LL i=2;i<=x;i++){
        LL j=x/(x/i);
        sv=(sv-((sum2(j)-sum2(i-1))%MOD+MOD)%MOD*sumvid(x/i)%MOD+MOD)%MOD;
        i=j;
    }
    return sv;
}

int main(){
    scanf("%lld", &n);
    r=min(n,(LL)R);
    pre();
    memset(svidr+1,0,(n/(r+1))*sizeof(svidr[0]));
    LL ans=0;
    for(LL i=1;i<=n;i++){
        LL j=n/(n/i);
        ans=(ans+(sumvid(j)-sumvid(i-1)+MOD)%MOD*(sum(n/i)*sum(n/i)%MOD)%MOD)%MOD;
        i=j;
    }
    printf("%lld\n", ans);
    return 0;
}