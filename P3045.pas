const maxn=50000;
type arr=array[1..maxn]of Int64;
var n,i,k,len:longint;
    p,c,dis,mp,mc:arr;
    m:Int64;

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
    k:=c[(l+r)shr 1];
    repeat
        while c[x]<k do inc(x);
        while c[y]>k do dec(y);
        if x<=y then
        begin
            swap(c[x],c[y]);
            swap(p[x],p[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;

procedure mdown(x:Int64;var a,ma,mb:arr);
var t:Int64;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(a[t]>a[t+1]) then inc(t);
    if a[t]<a[x] then
    begin
        swap(a[x],a[t]);
        swap(ma[x],ma[t]);
        mb[ma[t]]:=t;
        mb[ma[x]]:=x;
        mdown(t,a,ma,mb);
    end;
end;

procedure down(x:Int64);
var t:Int64;
begin
    t:=x shl 1;
    if t>k then exit
    else if (t<k)and(dis[t]>dis[t+1]) then inc(t);
    if dis[t]<dis[x] then
    begin
        swap(dis[x],dis[t]);
        down(t);
    end;
end;

begin
    readln(n,k,m);
    for i:=1 to n do
    begin
        readln(p[i],c[i]);
        mp[i]:=i;
        mc[i]:=i;
    end;
    qs(1,n);
    for i:=1 to k do
    begin
        dec(m,c[i]);
        dis[i]:=p[i]-c[i];
        if m<=0 then
        begin
            writeln(i-1);
            halt;
        end;
    end;//k,n-k
    len:=n-k;
    for i:=k shr 1 downto 1 do down(i);
    for i:=len shr 1 downto 1 do
    begin
        mdown(i,p,mp,mc);
        mdown(i,c,mc,mp);
    end;
    while len>0 do
    if (m>=p[1])and(p[1]<=c[1]+dis[1]) then//buy with p
    begin
        dec(m,p[1]);
        swap(c[mp[1]],c[len]);
        swap(mc[mp[1]],mc[len]);
        swap(p[1],p[len]);
        swap(mp[1],mp[len]);
        dec(len);
        mdown(mp[len+1],c,mc,mp);
        mdown(1,p,mp,mc);
    end
    else if m>=c[1]+dis[1] then
    begin
        dec(m,c[1]+dis[1]);
        dis[1]:=p[mc[1]]-c[1];
        down(1);
        swap(p[mc[1]],p[len]);
        swap(mp[mc[1]],mp[len]);
        swap(c[1],c[len]);
        swap(mc[1],mc[len]);
        dec(len);
        mdown(mc[len+1],p,mp,mc);
        mdown(1,c,mc,mp);
    end
    else break;
    writeln(n-len);
end.