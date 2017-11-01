const maxm=110000;//暴力
var m,q,c,n,i,line:longint;
    v:array[-10000..maxm]of longint;

procedure print();
var t:longint;
begin
    for t:=1 to m do
    write(v[t],' ');
    writeln;
end;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:longint);//descend
var k,x,y:longint;
begin
    x:=l;y:=r;
    k:=v[(l+r)div 2];
    repeat
        while v[x]>k do inc(x);
        while v[y]<k do dec(y);
        if x<=y then
        begin
            swap(v[x],v[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;

procedure insert(x:longint);
var l,r,j,mid:longint;
begin
    l:=line;r:=m;
    while l<r do
    begin
        mid:=(l+r)div 2;
        if mid<0 then dec(mid);
        if v[mid]>x then l:=mid+1
        else r:=mid;
    end;
    if m-l<=l-line then
    begin
        inc(m);
        for j:=m downto l+1 do
        v[j]:=v[j-1];
        v[l]:=x;
    end
    else
    begin
        for j:=line to l-1 do
        v[j-1]:=v[j];
        dec(line);
        v[l-1]:=x;
    end;
    //print;
end;

begin
    readln(m,q);
    for i:=1 to m do read(v[i]);
    qs(1,m);
    line:=1;
    for i:=1 to q do
    begin
        readln(c,n);
        if c=1 then
        writeln(v[line+n-1])
        else
        insert(n);
    end;
end.