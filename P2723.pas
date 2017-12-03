const maxn=100000;
    maxk=100;
var n,i,j,len,k:longint;
    t:Int64;
    a:array[1..maxk*maxn]of Int64;
    p:array[1..maxk]of longint;

procedure swap(var x,y:Int64);
var t:Int64;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure up(x:Int64);
var t:Int64;
begin
    t:=x shr 1;
    if (x>1)and(a[x]<a[t]) then
    begin
        swap(a[x],a[t]);
        up(t);
    end;
end;

procedure down(x:Int64);
var t:Int64;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(a[t]>a[t+1]) then inc(t);
    if a[t]<a[x] then
    begin
        swap(a[x],a[t]);
        down(t);
    end;
end;

procedure insert(x:Int64);
begin
    inc(len);
    a[len]:=x;
    up(len);
end;

procedure delete(x:Int64);
begin
    a[x]:=a[len];
    dec(len);
    down(x);
end;

begin
    readln(k,n);
    for i:=1 to k do
    begin
        read(p[i]);
        a[i]:=p[i];
    end;
    len:=k;
    for i:=k shr 1 downto 1 do
    down(i);
    for i:=1 to n-1 do
    begin
        t:=a[1];
        for j:=1 to k do
        insert(t*p[j]);
        while t=a[1] do
        delete(1);
    end;
    writeln(a[1]);
end.