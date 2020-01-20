#include <cstdio>
#include <bitset>
#define MAXN 1005

using namespace std;

const int inf=0x3f3f3f3f;

int n,fa[MAXN];
bitset<MAXN> nr[MAXN],nrr[MAXN],nl;

int find(int x){
    if(fa[x]==x)
        return x;
    return fa[x]=find(fa[x]);
}

int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        int k;
        scanf("%d", &k);
        for(int j=1;j<=k;j++){
            int t;
            scanf("%d", &t);
            nr[i][t]=1;
        }
    }
    for(int i=1;i<=n;i++)
        fa[i]=i;
    bitset<MAXN> itr;
    int cnt=0,u,v;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            itr=nr[i]&nr[j];
            if(itr.count()==2){
                u=v=0;
                for(int k=1;k<=n;k++){
                    if(itr[k]){
                        if(u){
                            v=k;
                            break;
                        }
                        else u=k;
                    }
                }
                int ru=find(u),rv=find(v);
                if(ru!=rv){
                    fa[ru]=rv;
                    printf("%d %d\n",u,v);
                    cnt++;
                    nrr[u][u]=nrr[v][v]=nrr[u][v]=nrr[v][u]=1;
                    nl[u]=nl[v]=1;
                }
            }
        }
    }
    if(cnt==0){
        for(int i=2;i<=n;i++)
            printf("%d %d\n",1,i);
    }
    else if(cnt==1){
        for(int i=1;i<=n;i++){
            if(nr[i].count()<n){
                for(int j=1;j<=n;j++){
                    if(!nl[j])
                        printf("%d %d\n",j,nr[i][j]?u:v);
                }
                break;
            }
        }
    }
    else{
        for(int i=1;i<=n;i++){
            if(!nl[i]){
                int mn=inf,mnr=inf;
                for(int j=1;j<=n;j++){
                    if(nr[j][i] && (nr[j]&nl).count()<mn){
                        itr=(nr[j]&nl);
                        mn=itr.count();
                        mnr=nr[j].count();
                    }
                }
                for(int j=1;j<=n;j++){
                    if(itr[j] && nrr[j]==itr){
                        printf("%d %d\n",i,j);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}