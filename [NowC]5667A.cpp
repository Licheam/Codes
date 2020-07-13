#include <bits/stdc++.h>
#define MAXN 2000005
#define LL long long
using namespace std;
// const int inf=0x3f3f3f3f;
// const double eps=1e-7;
// const int dx[4]={1,-1,0,0};
// const int dy[4]={0,0,1,-1};
const int MOD=998244353;
const int P1=1e9+7;
const int P2=1e9+9;
const int BASE=9209;


void kmp(char* s,int* nxt){
    int len=strlen(s+1);
    nxt[0]=-1;
    for(int i=1,k=-1;i<=len;i++){
        while(~k && s[k+1]!=s[i])
            k=nxt[k];
        nxt[i]=++k;
    }
}

char s[MAXN];
int sp[MAXN];
int nxt[MAXN];
map<pair<int,int>,int> mp;
int cnt[MAXN];

void solve() {
    mp.clear();
    int n;
    scanf("%d", &n);
    sp[1]=0;
    for(int i=1;i<=n;i++) {
        scanf("%s", s+sp[i]+1);
        kmp(s+sp[i],nxt+sp[i]);
        int len=strlen(s+sp[i]+1);
        int hsh1=0,hsh2=0,t1=1,t2=1;
        for(int j=sp[i]+len;j>=sp[i]+1;j--) {
            hsh1=(hsh1+1LL*s[j]*t1%P1)%P1;
            hsh2=(hsh2+1LL*s[j]*t2%P2)%P2;
            mp[make_pair(hsh1,hsh2)]++;
            t1=1LL*t1*BASE%P1;
            t2=1LL*t2*BASE%P2;
        }
        sp[i+1]=sp[i]+1+len;
    }
    memset(cnt+1,0,sp[n+1]*sizeof(cnt[0]));
    int ans=0;
    for(int i=1;i<=n;i++) {
        int hsh1=0,hsh2=0;
        for(int j=sp[i]+1;j<sp[i+1];j++) {
            hsh1=(1LL*hsh1*BASE%P1+s[j])%P1;
            hsh2=(1LL*hsh2*BASE%P2+s[j])%P2;
            cnt[j]=mp[make_pair(hsh1,hsh2)];
            if(~nxt[j])
                cnt[sp[i]+nxt[j]]-=cnt[j];
        }
        for(int j=sp[i]+1;j<sp[i+1];j++) 
            ans=(ans+1LL*cnt[j]*(j-sp[i])%MOD*(j-sp[i])%MOD)%MOD;
    }
    printf("%d\n", ans);
}

int main() {
    int T=1,cas=1;
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}