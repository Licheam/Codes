#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 150005
#define MAXX 320005

using namespace std;

struct star{
    int x,y;
}s[MAXN];

int n,len,bit[MAXX],lv[MAXN];

bool cmp(star a, star b){
    if(a.x!=b.x)
        return a.x<b.x;
    else
        return a.y<b.y;
}

int lowbit(int x){
    return x&(-x);
}

void change(int x,int y){
    for(;x<=len;x+=lowbit(x))
        bit[x]+=y;
}

int sum(int x){
    int r=0;
    for(;x;x-=lowbit(x))
        r+=bit[x];
    return r;
}

int main(){
    while(~scanf("%d", &n)){
        for(int i=1;i<=n;i++){
            scanf("%d %d",&s[i].x,&s[i].y);
        }
        sort(s+1,s+n+1,cmp);
        len=MAXX;
        memset(bit,0,sizeof(bit));
        memset(lv,0,sizeof(int)*n);
        for(int i=1;i<=n;i++){
            lv[sum(s[i].y+1)]++;
            change(s[i].y+1,1);
        }
        for(int i=0;i<n;i++){
            printf("%d\n",lv[i]);
        }
    }
    return 0;
}