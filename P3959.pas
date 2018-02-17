const maxn=12;
    maxm=1000;
    maxl=500001;
var n,m,i,f,g,w,ans:longint;
    dist:array[1..maxn]of longint;
    ma:array[1..maxn,1..maxn]of longint;
    dp:array[1..4095]of longint;

procedure dfs(x:longint);
var i,j:longint;
begin
    //writeln(x);
    for i:=1 to n do
        if ((1 shl(i-1)) and x)>0 then
        begin
            for j:=1 to n do
                if (((1 shl(j-1)) and x)=0)and(ma[i,j]<>maxl) then
                begin
                    if dp[x or (1 shl(j-1))]>dp[x]+dist[i]*ma[i,j] then
                    begin
                        dist[j]:=dist[i]+1;
                        dp[x or (1 shl(j-1))]:=dp[x]+dist[i]*ma[i,j];
                        dfs(x or (1 shl(j-1)));
                    end;
                end;
        end;
end;

begin
    readln(n,m);
    filldword(ma,sizeof(ma)shr 2,maxl);
    for i:=1 to m do
    begin
        readln(f,g,w);
        if ma[f,g]>w then
        begin
            ma[f,g]:=w;
            ma[g,f]:=w;
        end;
    end;
    ans:=maxlongint;
    for i:=1 to n do
    begin
        filldword(dp,(1 shl n)-1,maxlongint);
        dp[1 shl(i-1)]:=0;
        dist[i]:=1;
        dfs(1 shl(i-1));
        if dp[(1 shl n)-1]<ans then
            ans:=dp[(1 shl n)-1];
    end;
    writeln(ans);
end.