const maxn=40005;
var n,cnt,i,j:longint;
    a,b,c,t:array[1..maxn]of longint;

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

function lowbit(x:longint):longint;
begin
    exit(x and(-x));
end;

procedure change(x:longint);
begin
    while x<=n do
    begin
        inc(c[x]);
        x:=x+lowbit(x);
    end;
end;

function sum(x:longint):longint;
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