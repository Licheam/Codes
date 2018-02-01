const maxn=300;
    maxm=50000;
var n,m,i,ans:longint;
    f,g,w:array[1..maxm]of longint;
    fa:array[1..maxn]of longint;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:longint);//ascend
var x,y,k:longint;
begin
    x:=l;y:=r;
    k:=w[(l+r)shr 1];
    repeat
        while w[x]<k do inc(x);
        while w[y]>k do dec(y);
        if x<=y then
        begin
            swap(w[x],w[y]);
            swap(f[x],f[y]);
            swap(g[x],g[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if x<r then qs(x,r);
    if y>l then qs(l,y);
end;

function find(x:longint):longint;
begin
    if fa[x]=x then exit(x);
    fa[x]:=find(fa[x]);
    exit(fa[x]);
end;

procedure kruskal();
var i,rx,ry:longint;
begin
    for i:=1 to m do
    begin
        rx:=find(f[i]);
        ry:=find(g[i]);
        if rx=ry then continue;
        ans:=w[i];
        fa[rx]:=ry;
    end;
end;

begin
    readln(n,m);
    for i:=1 to n do
        fa[i]:=i;
    for i:=1 to m do
        readln(f[i],g[i],w[i]);
    qs(1,m);
    kruskal;
    writeln(n-1,' ',ans);
end.