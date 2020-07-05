#include <bits/stdc++.h>
#define MAXN 3005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;
// const double eps=1e-9;
// const int MOD=1e9+7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};

int n,m,o,l;
int cnt[MAXN][MAXN],sx[MAXN][MAXN],sy[MAXN][MAXN];
int bx[MAXN],by[MAXN];
char s[MAXN];
int op[MAXN];

void pile(int xa,int ya,int xb,int yb) {
    sx[xb][yb]+=sx[xa][ya];
    sy[xb][yb]+=sy[xa][ya];
    cnt[xb][yb]+=cnt[xa][ya];
    cnt[xa][ya]=0;
    sx[xa][ya]=sy[xa][ya]=0;
}

void solve() {
    scanf("%d %d %d %d", &n, &m, &o, &l);
    for(int i=1;i<=o;i++)
        scanf("%d %d", &bx[i], &by[i]);
    scanf("%s",s);

    memset(cnt,0,sizeof(cnt));
    memset(sx,0,sizeof(sx));
    memset(sy,0,sizeof(sy));
    int px=1000, py=1000;

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            cnt[i+px][j+py]=1;
            sx[i+px][j+py]=i;
            sy[i+px][j+py]=j;
        }
    }
    for(int i=1;i<=o;i++){
        cnt[bx[i]+px][by[i]+py]=0;
        sx[bx[i]+px][by[i]+py]=sy[bx[i]+px][by[i]+py]=0;
    }
    
    op['U']=0;op['D']=1;
    op['L']=2;op['R']=3;

    for(int i=0;i<l;i++) {
        int k=op[s[i]];
        px+=dx[k]; py+=dy[k];
        for(int j=1;j<=o;j++)
            pile(px+bx[j],py+by[j],px+bx[j]+dx[k],py+by[j]+dy[k]);
        for(int j=1;j<=n;j++){
            pile(px+j,py,px+j+dx[k],py+dy[k]);
            pile(px+j,py+m+1,px+j+dx[k],py+m+1+dy[k]);
        }
        for(int j=1;j<=m;j++){
            pile(px,py+j,px+dx[k],py+j+dy[k]);
            pile(px+n+1,py+j,px+n+1+dx[k],py+j+dy[k]);
        }
    }

    LL ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans+=i*i+j*j;
    for(int i=1;i<=o;i++)
        ans-=bx[i]*bx[i]+by[i]*by[i];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            ans+=1LL*cnt[px+i][py+j]*(i*i+j*j)
                -2LL*i*sx[px+i][py+j]-2LL*j*sy[px+i][py+j];
        }
    }
    printf("%lld\n", ans);
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