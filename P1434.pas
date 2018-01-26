const maxn=100;
var n,m,i,j,max:longint;
    ma,a:array[1..maxn,1..maxn]of longint;
    flag:array[1..maxn,1..maxn]of boolean;

procedure dfs(x,y:longint);
begin
    flag[x,y]:=true;
    if (x>1)and(ma[x,y]>ma[x-1,y]) then
    begin
        if not flag[x-1,y] then
            dfs(x-1,y);
        if a[x-1,y]+1>a[x,y] then
            a[x,y]:=a[x-1,y]+1;
    end;
    if (y>1)and(ma[x,y]>ma[x,y-1])then
    begin
        if not flag[x,y-1] then
            dfs(x,y-1);
        if a[x,y-1]+1>a[x,y] then
            a[x,y]:=a[x,y-1]+1;
    end;
    if (x<n)and(ma[x,y]>ma[x+1,y]) then
    begin
        if not flag[x+1,y] then
            dfs(x+1,y);
        if a[x+1,y]+1>a[x,y] then
            a[x,y]:=a[x+1,y]+1;
    end;
    if (y<m)and(ma[x,y]>ma[x,y+1]) then
    begin
        if not flag[x,y+1] then
            dfs(x,y+1);
        if a[x,y+1]+1>a[x,y] then
            a[x,y]:=a[x,y+1]+1;
    end;
end;

begin
    readln(n,m);
    for i:=1 to n do
    for j:=1 to m do
    begin
        read(ma[i,j]);
        a[i,j]:=1;
        flag[i,j]:=false;
    end;
    max:=1;
    for i:=1 to n do
    for j:=1 to m do
        if not(flag[i,j]) then
        begin
            dfs(i,j);
            if max<a[i,j] then max:=a[i,j];
        end;
    writeln(max);
end.