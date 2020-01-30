#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#define LL long long
#define MAXN 100005
#define N 100000
#define MAXQ 20005

using namespace std;

int n,m,a,ans[MAXN];
int p[MAXN],cnt;
bool inp[MAXN];
int mu[MAXN],sgmf[MAXN];
pair<int,int> sgm[MAXN];
int g[MAXN];

struct Qry{
    int n,m,a,num;
}qry[MAXQ];

bool cmp(Qry x,Qry y){
    return x.a<y.a;
}

void pre(){
    memset(inp+1,0,N*sizeof(inp[0]));
    inp[0]=inp[1]=1;
    cnt=0;
    mu[1]=1;
    sgm[1]=make_pair(1,1);
    sgmf[1]=1;
    for(int i=2;i<=N;i++){
        if(!inp[i]) p[++cnt]=i, mu[i]=-1, sgm[i]=make_pair(i+1,i), sgmf[i]=i+1;
        for(int j=1;j<=cnt && i*p[j]<=N;j++){
            inp[i*p[j]]=1;
            if(i%p[j]){
                mu[i*p[j]]=-mu[i];
                sgm[i*p[j]]=make_pair(sgm[i].first*(p[j]+1),i*p[j]);
                sgmf[i*p[j]]=p[j]+1;
            }
            else{
                mu[i*p[j]]=0;
                sgmf[i*p[j]]=p[j]*sgmf[i]+1;
                sgm[i*p[j]]=make_pair(sgm[i].first/sgmf[i]*sgmf[i*p[j]],i*p[j]);
                break;
            }
        }
    }
}

int lowbit(int x){
    return x&(-x);
}

void change(int x,int y){
    for(;x<=N;x+=lowbit(x))
        g[x]+=y;
}

int sum(int x){
    int s=0;
    for(;x;x-=lowbit(x))
        s+=g[x];
    return s;
}

int main(){
    int T;
    scanf("%d", &T);
    pre();
    sort(sgm+1,sgm+N+1);
    for(int i=1;i<=T;i++){
        scanf("%d %d %d", &qry[i].n, &qry[i].m, &qry[i].a);
        qry[i].num=i;
    }
    sort(qry+1,qry+T+1,cmp);
    int pos=1;
    for(int k=1;k<=T;k++){
        n=qry[k].n, m=qry[k].m, a=qry[k].a;
        while(pos<=N && sgm[pos].first<=a){
            int f=sgm[pos].first,d=sgm[pos].second;
            for(int i=1;i<=N/d;i++){
                change(i*d,f*mu[i]);
            }
            pos++;
        }
        int &an=ans[qry[k].num]=0;
        for(int i=1;i<=min(n,m);i++){
            int j=min(n/(n/i),m/(m/i));
            an+=(n/i)*(m/i)*(sum(j)-sum(i-1));
            i=j;
        }
    }
    for(int i=1;i<=T;i++)
    	printf("%d\n", ans[i]&(~(1<<31)));
    return 0;
}