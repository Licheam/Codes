#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=300005;

int to[MAXN],tto[MAXN],d[MAXN];
char s[MAXN];
int sa[MAXN],rk[MAXN],tp[MAXN],tax[MAXN];

void rsort(int n,int m) {
    memset(tax,0,(m+1)*sizeof(tax[0]));
    for(int i=1;i<=n;i++) tax[rk[i]]++;
    for(int i=1;i<=m;i++) tax[i]+=tax[i-1];
    for(int i=n;i>=1;i--) sa[tax[rk[tp[i]]]--]=tp[i];
}

void solve() {
    int n,m;
    scanf("%d", &n);
    scanf("%s", s+1);
    for(int i=1;i<=n;i++){
        d[i]=s[i]-'0';
        to[i]=((1LL*(i-1)*(i-1)+1)%n)+1;
    }

    m=0;
    for(int i=1;i<=n;i++) {
        m=max(m,rk[i]=d[i]);
        tp[i]=i;
    }

    rsort(n,m);
    for(int k=1,p;k<n;k<<=1,m=p) {
        p=0;
        memset(tax,0,(m+1)*sizeof(tax[0]));
        for(int i=1;i<=n;i++) tax[rk[to[i]]]++;
        for(int i=1;i<=m;i++) tax[i]+=tax[i-1];
        for(int i=1;i<=n;i++) tp[tax[rk[to[i]]]--]=i;

        rsort(n,m);

        swap(tp,rk);
        rk[sa[1]]=p=1;
        for(int i=2;i<=n;i++)
            rk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]] && tp[to[sa[i]]]==tp[to[sa[i-1]]])?p:++p;

        for(int i=1;i<=n;i++)
            tto[i]=to[to[i]];
        swap(tto,to);
    }

    int cur=sa[n];
    for(int i=1;i<=n;i++) {
        printf("%d", d[cur]);
        cur=((1LL*(cur-1)*(cur-1)+1)%n)+1;
    }
    puts("");
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