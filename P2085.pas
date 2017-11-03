const maxn=10000;
var n,m,i:longint;
    a,b,c,h,f,mark:array[1..maxn]of longint;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure down(x:longint);
var t:longint;
begin
    t:=x shl 1;
    if t>n then exit
    else if (t<n)and(h[t]>h[t+1]) then inc(t);
    if h[t]<h[x] then
    begin
        swap(h[x],h[t]);
        swap(f[x],f[t]);
        swap(mark[x],mark[t]);
        down(t);
    end;

end;

begin
    readln(n,m);
    filldword(f,n,1);
    for i:=1 to n do
    begin
        readln(a[i],b[i],c[i]);
        h[i]:=a[i]+b[i]+c[i];
        mark[i]:=i;
    end;
    for i:=n shr 1 downto 1 do
    down(i);
    for i:=1 to m-1 do
    begin
        write(h[1],' ');
        inc(f[1]);
        h[1]:=a[mark[1]]*f[1]*f[1]+b[mark[1]]*f[1]+c[mark[1]];
        down(1);
    end;
    writeln(h[1]);
end.