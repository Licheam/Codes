const maxn=500;
    maxn2=250000;
var n,i,j,s,tot,cnt:longint;
    a,b,fa:array[1..maxn]of longint;
    f,g:array[1..maxn2]of longint;
    w:array[1..maxn2]of real;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:longint);//ascend
var x,y:longint;
    key,t:real;
begin
    x:=l;y:=r;
    key:=w[(l+r)shr 1];
    repeat
        while w[x]<key do inc(x);
        while w[y]>key do dec(y);
        if x<=y then
        begin
            t:=w[x];
            w[x]:=w[y];
            w[y]:=t;
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
    cnt:=0;
    for i:=1 to tot do
    begin
        rx:=find(f[i]);
        ry:=find(g[i]);
        if rx=ry then
            continue;
        inc(cnt);
        if cnt=s then
        begin
            writeln(w[i]:0:2);
            halt;
        end;
        fa[rx]:=ry;
    end;
end;

begin
    readln(s,n);
    s:=n-s;
    for i:=1 to n do
    begin
        readln(a[i],b[i]);
        fa[i]:=i;
    end;
    tot:=0;
    for i:=1 to n do
    for j:=1 to n do
    begin
        inc(tot);
        f[tot]:=i;
        g[tot]:=j;
        w[tot]:=sqrt((a[i]-a[j])*(a[i]-a[j])+(b[i]-b[j])*(b[i]-b[j]));
        //writeln(f[tot],'-',g[tot],':',w[tot]:0:2);
    end;
    qs(1,tot);
    kruskal;
end.