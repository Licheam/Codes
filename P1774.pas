const maxn=500005;
var n,i,j:longint;
    cnt:Int64;
    a,b,c,t:array[1..maxn]of Int64;

procedure swap(var x,y:Int64);
var t:Int64;
begin   
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:Int64);//ascend
var x,y,k:Int64;
begin
    x:=l;y:=r;
    k:=a[(l+r)shr 1];
    repeat
        while a[x]<k do inc(x);
        while a[y]>k do dec(y);
        if x<=y then
        begin
            swap(a[x],a[y]);
            swap(b[x],b[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;

function lowbit(x:Int64):Int64;
begin
    exit(x and(-x));
end;

procedure change(x:Int64);
begin
    while x<=n do
    begin
        inc(c[x]);
        x:=x+lowbit(x);
    end;
end;

function sum(x:Int64):Int64;
begin
    sum:=0;
    while x>0 do
    begin
        inc(sum,c[x]);
        x:=x-lowbit(x);
    end;
end;

begin
    readln(n);
    for i:=1 to n do
    begin
        read(a[i]);
        b[i]:=i;
    end;
    qs(1,n);
    j:=1;
    a[n+1]:=a[n];
    for i:=1 to n do//discretize
    begin
        if a[i]<>a[i+1] then
        begin
            a[i]:=j;
            inc(j);
        end
        else a[i]:=j;
    end;
    for i:=1 to n do
    t[b[i]]:=a[i];
    filldword(c,n,0);
    cnt:=0;
    for i:=n downto 1 do
    begin
        change(t[i]);
        inc(cnt,sum(t[i]-1));
    end;
    writeln(cnt);
end.