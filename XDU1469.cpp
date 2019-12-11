#include <cstdio>
#include <algorithm>
#define MAXN 100005

using namespace std;

struct point{
    int x,y;
    point():x(0),y(0){}
}p[MAXN];

bool cmp(point a,point b){
    if(a.y-a.x!=b.y-b.x)
        return a.y-a.x<b.y-b.x;
    else
        return a.x+a.y<b.x+b.y;
}

int n,arr[MAXN],len;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&p[i].x,&p[i].y);
    }
    sort(p+1,p+1+n,cmp);
    len=0;
    arr[0]=0;
    for(int i=lower_bound(p+1,p+1+len,point(),cmp)-p;i<=n;i++){
        int t=p[i].y+p[i].x;
        if(t<0) continue;
        if(arr[len]<=t)
            arr[++len]=t;
        else{
            *upper_bound(arr+1,arr+1+len,t,less<int>())=t;
        }
    }
    printf("%d\n", len);
    return 0;
}