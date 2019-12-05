#include <cstdio>
#include <functional>
#include <algorithm>
#define MAXH 50000
#define MAXN 100005

using namespace std;

int n,a[MAXN],b[MAXN],lena,lenb;//a(down) b(up)

int main(){
    a[lena=0]=MAXH;b[lenb=0]=0;
    for(int t;~scanf("%d", &t);){
        if(t<=a[lena])
            a[++lena]=t;
        else{
            int *p=upper_bound(a+1,a+lena+1,t,greater<int>());
            *p=t;
        }
        if(t>b[lenb])
            b[++lenb]=t;
        else{
            int *p=lower_bound(b+1,b+lenb+1,t,less<int>());
            *p=t;
        }
    }
    printf("%d\n%d",lena,lenb);
    return 0;
}