const maxn=100000;

var n,i,loop:longint;
    next,cnt:array[1..maxn]of longint;
    flag:array[1..maxn]of boolean;

procedure visit(x:longint);
var v:longint;
begin
    flag[x]:=true;
    if not(flag[next[x]])then
    visit(next[x])
    else if cnt[next[x]]=0 then
    loop:=next[x];
    cnt[x]:=cnt[next[x]]+1;
    if loop=x then
    begin
        v:=x;
        while next[v]<>x do
        begin
            v:=next[v];
            cnt[v]:=cnt[x];
        end;
    end;
end;

begin
    readln(n);
    for i:=1 to n do
    readln(next[i]);
    fillchar(flag,n,false);
    filldword(cnt,n,0);
    loop:=0;
    for i:=1 to n do
        if not(flag[i])then
        visit(i);
    for i:=1 to n do
    writeln(cnt[i]);
end.