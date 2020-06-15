#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int dx[8]={1,0,-1,0,1,-1,1,-1};
const int dy[8]={0,1,0,-1,1,-1,-1,1};
const double eps=1e-9;

double sum(double a1, double b1, double a2, double b2, double a3, double b3) {
    double aa1=(a1-a2),aa2=(a1-a3),bb1=(b1-b2),bb2=(b1-b3);
    return abs(aa1*bb2-aa2*bb1)/2;
}

bool cross(double a1,double b1,double a2,double b2,double a3,double b3,double a4,double b4) {
    double aa1=(a1-a3),aa2=(a1-a4),bb1=(b1-b3),bb2=(b1-b4);
    double aa3=(a2-a3),aa4=(a2-a4),bb3=(b2-b3),bb4=(b2-b4);
    if((aa1*bb2-aa2*bb1)*(aa3*bb4-aa4*bb3)>-eps) return false;

    aa1=(a1-a3),aa2=(a1-a2),bb1=(b1-b3),bb2=(b1-b2);
    aa3=(a1-a2),aa4=(a1-a4),bb3=(b1-b2),bb4=(b1-b4);
    if((aa1*bb2-aa2*bb1)*(aa3*bb4-aa4*bb3)<eps) return false;
    return true;
}

int n;
double a1,a2,a3,b1,b2,b3,s;

bool intri(double x,double y) {
    double s1=sum(x,y,a2,b2,a3,b3);
    double s2=sum(a1,b1,x,y,a3,b3);
    double s3=sum(a1,b1,a2,b2,x,y);
    if(abs(s1+s2+s3-s)<eps && s1>eps && s2>eps && s3>eps) return 1;
    else return 0;
}


bool out(int x,int y) {
    if(0<=x && x<n && 0<=y && y<n) return 0;
    else return 1;
}

char c[25][25];
bool vis[25][25];

void solve() {
    while(~scanf("%d", &n)) {
        scanf("%lf %lf %lf %lf %lf %lf", &b1, &a1, &b2, &a2, &b3, &a3);
        s=sum(a1,b1,a2,b2,a3,b3);
        for(int i=0;i<n;i++) {
            scanf("%s", c[n-i-1]);
        }
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                if(c[i][j]=='.' && intri(i,j)) {
                    c[i][j]='#';
                }
            }
        }

        queue<pair<pair<int,int>,int > > Q;
        memset(vis,0,sizeof(vis));
        Q.push(make_pair(make_pair(0,0),0));
        int ans=-1;
        while(!Q.empty()) {
            int x=Q.front().first.first;
            int y=Q.front().first.second;
            int len=Q.front().second;
            Q.pop();
            for(int k=0;k<8;k++) {
                int xx=x+dx[k],yy=y+dy[k];
                if(out(xx,yy) || c[xx][yy]=='#') continue;
                if(cross(xx,yy,x,y,a1,b1,a2,b2) 
                    || cross(xx,yy,x,y,a1,b1,a3,b3)
                    || cross(xx,yy,x,y,a3,b3,a2,b2)
                    || cross(xx,yy,x,y,a1,b1,(a2+a3)/2,(b2+b3)/2)
                    || cross(xx,yy,x,y,a2,b2,(a1+a3)/2,(b1+b3)/2)
                    || cross(xx,yy,x,y,a3,b3,(a1+a2)/2,(b1+b2)/2)) {
                    continue;
                }

                if(xx==n-1 && yy==n-1) {
                    ans=len+1;
                    break;
                }
                if(!vis[xx][yy]) {
                    vis[xx][yy]=1;
                    Q.push(make_pair(make_pair(xx,yy),len+1));
                }
            }

            if(ans!=-1) break;
        }
        printf("%d\n", ans);
    }
}

int main() {
    int T=1,cas=1;
    // scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}