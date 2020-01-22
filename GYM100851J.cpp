#include <cstdio>
#include <ctime>
#include <cstdlib>
#define MAXN 1005
 
int n,res,color[MAXN];
char s[MAXN];
 
int main(){
	scanf("%d", &n);
	s[n]='\0';
	srand(time(0));
	do{
		for(int i=0;i<n;i++){
			s[i]='0'+(rand()&1);
		}
		puts(s);
		fflush(stdout);
		scanf("%d", &res);
	}while(!res);
	if(res==n/2){
		s[0]=(s[0]-'0')^1+'0';
		color[0]=1;
		for(int i=1;i<n;i++){
			s[i]=(s[i]-'0')^1+'0';
			puts(s);
			fflush(stdout);
			scanf("%d", &res);
			if(!res) color[i]=1;
			else if(res==n/2) color[i]=0;
			else{
				return 0;
			}
			s[i]=(s[i]-'0')^1+'0';
		}
		for(int i=1;i<n;i++)
			if(color[i])
				s[i]=(s[i]-'0')^1+'0';
		puts(s);
		fflush(stdout);
		scanf("%d", &res);
		if(!res){
			for(int i=0;i<n;i++){
				s[i]=(s[i]-'0')^1+'0';
			}
			puts(s);
			fflush(stdout);
		}
	}
	return 0;
}