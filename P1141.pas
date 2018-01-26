const maxn=1000;
    maxn2=1000000;
var n,m,i,j,x,y,t:longint;
    ma:array[1..maxn,1..maxn]of char;
    fa:array[1..maxn2]of longint;
    cnt:array[1..maxn2]of longint;

function find(x:longint):longint;
begin
    if fa[x]=x then exit(x);
    fa[x]:=find(fa[x]);
    exit(fa[x]);
end;

procedure union(x,y:longint);
var rx,ry:longint;
begin
    rx:=find(x);ry:=find(y);
    if rx=ry then exit;
    if cnt[rx]>cnt[ry] then
    begin
        fa[ry]:=rx;
        inc(cnt[rx],cnt[ry]);
    end
    else
    begin
        fa[rx]:=ry;
        inc(cnt[ry],cnt[rx]);
    end;
end;

begin
    readln(n,m);
    for i:=1 to n*n do
    begin
        fa[i]:=i;
        cnt[i]:=1;
    end;
    t:=0;
    for i:=1 to n do
    begin
        for j:=1 to n do
        begin
            inc(t);
            read(ma[i,j]);
            if (i>1)and(ma[i,j]<>ma[i-1,j]) then
            union(t,t-n);
            if (j>1)and(ma[i,j]<>ma[i,j-1]) then
            union(t,t-1);
        end;
        readln;
    end;
    //for i:=1 to n*n do
    //writeln(i,':',find(i));
    for i:=1 to m do
    begin
        readln(x,y);
        writeln(cnt[find((x-1)*n+y)]);
    end;
end.