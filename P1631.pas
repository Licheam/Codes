const maxn=100000;
var n,i,len:longint;
    a,b,s,pa,pb,ta:array[1..maxn]of longint;

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
    if t>len then exit
    else if (t<len)and(s[t]>s[t+1]) then inc(t);
    if s[t]<s[x] then
    begin
        swap(s[x],s[t]);
        swap(pa[x],pa[t]);
        swap(pb[x],pb[t]);
        down(t);
    end;
end;

procedure delete(x:longint);
begin
    s[x]:=s[len];
    pa[x]:=pa[len];
    pb[x]:=pb[len];
    dec(len);
    down(x);
end;

procedure up(x:longint);
var t:longint;
begin
    if x<=1 then exit;
    t:=x shr 1;
    if s[x]<s[t] then
    begin
        swap(s[x],s[t]);
        swap(pa[x],pa[t]);
        swap(pb[x],pb[t]);
        up(t);
    end;
end;

procedure insert(x,y,z:longint);
begin
    inc(len);
    s[len]:=x;
    pa[len]:=y;
    pb[len]:=z;
    up(len);
end;

begin
    readln(n);
    for i:=1 to n do read(a[i]);
    for i:=1 to n do read(b[i]);
    filldword(ta,n,1);//b to a第几个
    len:=0;
    for i:=1 to n do
    insert(a[1]+b[i],1,i);
    for i:=1 to n do
    begin
        write(s[1],' ');
        if (pa[1]<n)and(ta[pb[1]]<=pa[1]) then//加个判重
        begin
            insert(a[pa[1]+1]+b[pb[1]],pa[1]+1,pb[1]);
            ta[pb[1]]:=pa[1]+1;
        end;
        delete(1);
    end;
end.