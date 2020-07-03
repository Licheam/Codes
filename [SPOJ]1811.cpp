#include<cstdio>
#include<cstring>
#include<algorithm>
#include<tr1/unordered_set>
#define MAXN 250005
using namespace std;
#define LL long long
#define uLL unsigned long long
const uLL base=2333333;

char s1[MAXN],s2[MAXN];
uLL hsh1[MAXN],hsh2[MAXN],pw[MAXN];
int len1,len2;

tr1::unordered_set<uLL> s;

bool check(int len) {
    if(!len) return true;
    s.clear();
    for(int i=len;i<=len1;i++)
        s.insert(hsh1[i]-hsh1[i-len]*pw[len]);
    for(int i=len;i<=len2;i++)
        if(s.find(hsh2[i]-hsh2[i-len]*pw[len])!=s.end())
            return true;
    return false;
}

void solve() {
    pw[0]=1;
    for(int i=1;i<=250000;i++) pw[i]=pw[i-1]*base;
    scanf("%s%s", s1+1, s2+1);
    len1=strlen(s1+1);
    len2=strlen(s2+1);
    hsh1[0]=0;
    for(int i=1;i<=len1;i++)
        hsh1[i]=hsh1[i-1]*base+(s1[i]-'a');
    hsh2[0]=0;
    for(int i=1;i<=len2;i++)
        hsh2[i]=hsh2[i-1]*base+(s2[i]-'a');

    int l=0,r=min(len1,len2);
    while(l<r) {
        int mid=(l+r+1)>>1;
        if(check(mid)) l=mid;
        else r=mid-1;
    }
    printf("%d\n", l);
}

int main(){
    int T=1;
    // scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}
