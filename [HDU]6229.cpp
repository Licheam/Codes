#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};

int gcd(int x,int y) {
    if(!x || !y) return x+y;
    return gcd(y,x%y);
}

void solve() {
    set<pair<int,int>> s;
    int n,k,a,b;
    scanf("%d %d", &n, &k);
    if(n==1){
        printf("1/1\n");
        return;
    }
    a=3*3+(2*n-4)*4+(n-1)*(n-2)/2*5;
    b=4*3+(4*n-8)*4+(n-2)*(n-2)*5;
    for(int i=1;i<=k;i++) {
        int x,y;
        scanf("%d %d", &x, &y);
        int cnt=1;
        for(int k=0;k<4;k++) {
            if(0<=x+dx[k] && x+dx[k]<n && 0<=y+dy[k] && y+dy[k]<n && s.find(make_pair(x+dx[k],y+dy[k]))==s.end()) {
                b--;
                cnt++;
                if(x+dx[k]+y+dy[k]>=n-1)
                    a--;
            }
        }
        b-=cnt;
        if(x+y>=n-1) a-=cnt;
        s.insert(make_pair(x,y));
    }
    int g=gcd(a,b);
    printf("%d/%d\n", a/g,b/g);
}

int main() {
    int T=1,cas=1;
    scanf("%d", &T);
    while(T--) {
        printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}