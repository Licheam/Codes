#include <cstdio>
#define MAXN 15
#define MAXT 105

const int inf=0x3f3f3f3f;

int n,m,d[MAXN][MAXN],f[MAXT][MAXT];

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d", &d[i][j]);
        }
    }
    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            int mx=0;
            for(int ii=1;ii<=n;ii++){
                for(int jj=1;jj<=m;jj++){
                    if(mx<d[ii][jj]-ii*i-jj*j)
                        mx=d[ii][jj]-ii*i-jj*j;
                }
            }
            f[i][j]=mx;
        }
    }
    int psb=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int mn=inf;
            for(int ii=0;ii<=100;ii++){
                for(int jj=0;jj<=100;jj++){
                    if(mn>f[ii][jj]+ii*i+jj*j)
                        mn=f[ii][jj]+ii*i+jj*j;
                }
            }
            if(d[i][j]!=mn){
                psb=0;
                break;
            }
        }
        if(!psb){
            break;
        }
    }
    if(!psb){
        printf("Impossible\n");
    }
    else{
        printf("Possible\n");
        printf("202 10401\n");
        for(int i=1;i<=100;i++){
            printf("%d %d X\n",i,i+1);
        }
        for(int j=1;j<=100;j++){
            printf("%d %d Y\n",j+101,j+102);
        }
        for(int i=0;i<=100;i++){
            for(int j=0;j<=100;j++){
                printf("%d %d %d\n",i+1,202-j,f[i][j]);
            }
        }
        printf("1 202\n");
    }
    return 0;
}