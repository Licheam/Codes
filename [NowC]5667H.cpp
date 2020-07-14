#include <bits/stdc++.h>
#define MAXN 200005
#define LL long long
using namespace std;

const LL inf=0x3f3f3f3f3f3f3f3f;

int root,len;

struct node{
    LL v;
    int fa,ch[2],size,cnt;
    LL mn;
    int pre,succ;
}sp[MAXN];

int getch(int x){return sp[sp[x].fa].ch[1]==x;}

void pushup(int x) {
    int lc=sp[x].ch[0], rc=sp[x].ch[1];
    sp[x].size=sp[x].cnt+sp[lc].size+sp[rc].size;
    if(sp[x].cnt>1) sp[x].mn=0;
    else sp[x].mn=min(min(sp[lc].mn,sp[rc].mn),sp[x].v-sp[sp[x].pre].v);
}

void rotate(int x) {
    int f=sp[x].fa, ff=sp[f].fa;
    int k=getch(x);
    sp[ff].ch[getch(f)]=x; sp[x].fa=ff;
    sp[sp[x].ch[k^1]].fa=f; sp[f].ch[k]=sp[x].ch[k^1];
    sp[x].ch[k^1]=f; sp[f].fa=x;
    pushup(f); pushup(x);
}

void splay(int x,int goal=0) {
    for(int f;(f=sp[x].fa)!=goal;rotate(x)) {
        if(sp[f].fa!=goal)
            rotate(getch(x)==getch(f)?f:x);
    }
    if(!goal) root=x;
}

void insert(LL x) {
    int cur=root, f=0;
    while(cur) {
        f=cur;
        cur=sp[cur].ch[x>sp[cur].v];
    }
    if(cur){
        sp[cur].cnt++;
        sp[cur].mn=0;
        sp[cur].size++;
    }
    else {
        cur=++len;
        sp[f].ch[x>sp[f].v]=cur;
        sp[cur].ch[0]=sp[cur].ch[1]=0;
        sp[cur].fa=f;
        sp[cur].v=x;
        sp[cur].cnt=sp[cur].size=1;
        if(getch(cur)) {
            sp[cur].succ=sp[f].succ;
            sp[sp[f].succ].pre=cur;
            sp[f].succ=cur;
            sp[cur].pre=f;
        } else {
            sp[cur].pre=sp[f].pre;
            sp[sp[f].pre].succ=cur;
            sp[f].pre=cur;
            sp[cur].succ=f;
        }
        sp[cur].mn=sp[cur].v-sp[sp[cur].pre].v;
    }
    splay(cur);
}

void find(LL x) {
    int cur=root;
    while(x!=sp[cur].v && sp[cur].ch[x>sp[cur].v])
        cur=sp[cur].ch[x>sp[cur].v];
    splay(cur);
}

void erase(LL x) {
    find(x);
    int last=sp[root].pre, next=sp[root].succ;
    splay(last); splay(next,last);
    int del=sp[next].ch[0];
    if(sp[del].cnt>1) {
        sp[del].cnt--;
        pushup(del);
        splay(del);
    } else {
        sp[next].ch[0]=0;
        sp[next].pre=last;
        sp[last].succ=next;
        pushup(next);
        pushup(last);
    }
}


void solve() {
    int n;
    scanf("%d", &n);
    memset(sp,0,sizeof(sp[0]));
    sp[0].v=-inf;
    sp[0].mn=inf;
    root=0;len=0;
    insert(-inf);insert(inf);

    for(int i=1;i<=n;i++) {
        int op,x;
        scanf("%d %d", &op, &x);
        if(op==1) insert(x);
        else if(op==2) erase(x);
        else {
            bool yes=0;

            find(x);
            int last,next;
            if(sp[root].v<x) last=root, next=sp[root].succ;
            else next=root, last=sp[root].pre;

            splay(next);splay(last,next);
            if(sp[last].size>=3) {
                if(sp[last].cnt>1 && sp[last].v+sp[last].v>x) yes=1;
                else if(sp[last].v+sp[sp[last].pre].v>x) yes=1;
            }
            
            splay(last);splay(next,last);
            if(sp[next].mn<x) yes=1;
            if(yes) printf("Yes\n");
            else printf("No\n");
        }
    }
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