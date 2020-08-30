/*
    Coded with Leachim's ACM Template.
    No errors. No warnings. ~~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAXN=2000005;

int n,m;
int bit[MAXN];
int lowbit(int x){
    return x&(-x);
}

void change(int x,int y){
    for(;x<=n;x+=lowbit(x))
        bit[x]+=y;
}

void build() {
    for(int x=1;x<<1<=n;x<<=1)
        for(int i=x;i+x<=n;i+=x<<1)
            bit[i+x]+=bit[i];
}

int query(int k){
    int x=n;
    int t=0,i=1;
    for(;i<<1<=x;i<<=1);
    for(;i;i>>=1) {
        if(x&i) {
            t+=i;
            if(bit[t]<k) k-=bit[t];
            else x=t-1, t-=i;
        }
    }
    return t+1;
}

int p1[MAXN],p2[MAXN],*p=p1,*pp=p2;
int per[MAXN];
bool flag[MAXN];

void solve() {
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) p[i]=i;

    while(m--) {
        int k,x;
        scanf("%d %d", &k, &x);
        for(int i=1;i<=n;i++) bit[i]=1;
        build();
        for(int i=1,sz=n,cur=1;i<=n;i++,sz--) {
            cur=(cur+k-2)%sz+1;
            int t=query(cur);
            per[t]=i;
            change(t,-1);
        }

        memset(flag+1,0,n*sizeof(flag[0]));
        for(int i=1;i<=n;i++) {
            if(flag[i]) continue;
            int cur=i,l=0;
            for(;!flag[cur];cur=per[cur],l++)
                flag[cur]=1;
            int to=i;
            int y=x%l;
            while(y--) to=per[to];
            for(;l--;to=per[to],cur=per[cur])
                pp[to]=p[cur];
        }
        swap(p,pp);
    }
    for(int i=1;i<=n;i++) 
        printf("%d%c",p[i],i==n?'\n':' ');
}

int main() {
    int T=1,cas=1;(void)(cas);
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}