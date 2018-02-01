const maxn=16;
    maxans=480000;
var n,m,r,c,i,j,ans:longint;
    a:array[1..maxn,1..maxn]of longint;
    column,per:array[1..maxn]of longint;
    row,f:array[1..maxn,1..maxn]of longint;
    flag:array[1..maxn]of boolean;

procedure dp();
var i,j,k:longint;
begin
    //pre
    filldword(column,m,0);
    for j:=1 to m do
        for i:=2 to r do
            inc(column[j],abs(a[per[i],j]-a[per[i-1],j]));
    for i:=1 to m-1 do
        for j:=i+1 to m do
        begin
            row[i,j]:=0;
            for k:=1 to r do
                inc(row[i,j],abs(a[per[k],i]-a[per[k],j]));
        end;
    for i:=1 to m do
        f[i,1]:=column[i];
    //end pre
    for j:=2 to c do
    begin
        for i:=j to m do
        begin
            f[i,j]:=f[j-1,j-1]+column[i]+row[j-1,i];
            for k:=j to i-1 do
                if f[i,j]>f[k,j-1]+column[i]+row[k,i] then
                    f[i,j]:=f[k,j-1]+column[i]+row[k,i];
        end;
    end;
    for i:=c to m do
    begin
        if f[i,c]<ans then
            ans:=f[i,c];
    end;
end;

procedure dfs(dep,last:longint);
var i:longint;
begin
    if dep>r then
    begin
        dp;
        exit;
    end;
    for i:=last+1 to n-r+dep do
        if not(flag[i]) then
        begin
            flag[i]:=true;
            per[dep]:=i;
            dfs(dep+1,i);
            flag[i]:=false;
        end;
end;

begin
    readln(n,m,r,c);
    for i:=1 to n do
    for j:=1 to m do
        read(a[i,j]);
    fillchar(flag,n,false);
    ans:=maxans;
    dfs(1,0);
    writeln(ans);
end.