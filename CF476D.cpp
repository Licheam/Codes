#include <cstdio>

int n,k;

int main(){
    scanf("%d %d", &n, &k);
    printf("%d\n", k*(6*n-1));
    for(int i=1;i<=n;i++){
        printf("%d %d %d %d\n", k*(6*i-4), k*(6*i-5), k*(6*i-3), k*(6*i-1));
    }
    return 0;
}