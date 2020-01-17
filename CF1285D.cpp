#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;

int solve(vector<int> &v,int dep){
    if(dep==-1) return 0;
    vector<int> o,e;
    int t=1<<dep;
    for(int x:v){
        if(x&t) o.push_back(x);
        else e.push_back(x);
    }
    if(o.empty()) return solve(e,dep-1);
    else if(e.empty()) return solve(o,dep-1);
    else return min(solve(o,dep-1),solve(e,dep-1))+t;
}

int main(){
    scanf("%d", &n);
    vector<int> a;
    for(int i=1;i<=n;i++){
        int t;
        scanf("%d", &t);
        a.push_back(t);
    }
    printf("%d\n",solve(a,29));
    return 0;
}