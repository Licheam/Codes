#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define MAXN 105
#define MAXM 10005

struct edge{
    int to,next;
}e[MAXM];

int n,m;
int tot,head[MAXN],dgr[MAXN];
int dp[MAXN][MAXN][2];
int cnt[MAXN][MAXN];

void add(int x,int y) {
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

deque<tuple<int,int,int>> Q;

void solve() {
    scanf("%d %d", &n, &m);
    tot=0;
    memset(head+1,0,n*sizeof(head[0]));
    memset(dgr+1,0,n*sizeof(dgr[0]));
    for(int i=1;i<=m;i++) {
        int f,g;
        scanf("%d %d", &f, &g);
        add(g,f);
        dgr[f]++;
    }
    Q.clear();
    memset(dp,0,sizeof(dp));//win

    for(int i=1;i<=n;i++) {
        dp[i][i][0]=dp[i][i][1]=1;
        Q.push_back(make_tuple(i,i,0));
        Q.push_back(make_tuple(i,i,1));
        if(!dgr[i]) {
            for(int j=1;j<=n;j++) {
                if(i==j) continue;
                dp[i][j][0]=1;
                Q.push_back(make_tuple(i,j,0));
            }
        }
    }

    memset(cnt,0,sizeof(cnt));

    while(!Q.empty()) {
        int x=get<0>(Q.front());
        int y=get<1>(Q.front());
        int turn=get<2>(Q.front());
        Q.pop_front();

        if(turn==0) { //Bob
            for(int p=head[y];p;p=e[p].next) {
                int u=e[p].to;
                if(!dp[x][u][1]) {
                    dp[x][u][1]=1;
                    Q.push_back(make_tuple(x,u,1));
                }
            }
        } else {
            for(int p=head[x];p;p=e[p].next) {
                int u=e[p].to;
                if(!dp[u][y][0]) {
                    if(++cnt[u][y]==dgr[u]) {
                        dp[u][y][0]=1;
                        Q.push_back(make_tuple(u,y,0));
                    }
                }
            }
        }
    }

    int x,y;
    scanf("%d %d", &x, &y);
    if(dp[x][y][0]) printf("No\n");
    else printf("Yes\n");
}

int main() {
    int T=1;
    scanf("%d", &T);
    int cas=1;
    while(T--) {
        printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}