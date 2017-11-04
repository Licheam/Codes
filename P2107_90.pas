{const maxn=100000;
var n,i,j,len,cnt,las,max:longint;
    m,tot:Int64;
    d,ti,a,p:array[0..maxn]of Int64;

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
    k:=d[(l+r)shr 1];
    repeat
        while d[x]<k do inc(x);
        while d[y]>k do dec(y);
        if x<=y then
        begin
            swap(d[x],d[y]);
            swap(ti[x],ti[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;

procedure down(x:Int64);//ascend
var t:Int64;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(a[t]>a[t+1]) then inc(t);
    if a[t]<a[x] then
    begin
        swap(a[x],a[t]);
        swap(p[x],p[t]);
        down(t);
    end;
end;

procedure delete(x:Int64);
begin
    a[x]:=a[len];
    p[x]:=p[len];
    dec(len);
    down(x);
end;

begin
    readln(n,m);
    for i:=1 to n do
    readln(d[i],ti[i]);
    qs(1,n);
    max:=0;
    d[0]:=0;
    for j:=n downto 0 do
    if d[j]<=m then break;
    for i:=n downto 1 do
    begin
        //deb:=0;
        cnt:=0;
        len:=i;
        for j:=1 to i do
        a[j]:=ti[j];
        for j:=i shr 1 downto 1 do down(j);
        tot:=m-d[len]-a[1];
        while (tot>=0)and(len>=1) do
        begin
            //writeln('debug:',deb);
            //for j:=1 to len do write(a[j],' ');
            //writeln;
            //inc(deb);
            inc(cnt);
            delete(1);
            dec(tot,a[1]);
        end;
        if cnt>max then max:=cnt;
        if max>=i then break;
    end;
    writeln(max);
end.}
const maxn=100005;
var n,i,max,len,cnt,las:longint;
    m,tot:Int64;
    d,ti,a,p:array[0..maxn]of Int64;

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
    k:=d[(l+r)shr 1];
    repeat
        while d[x]<k do inc(x);
        while d[y]>k do dec(y);
        if x<=y then
        begin
            swap(d[x],d[y]);
            swap(ti[x],ti[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;

procedure down(x:Int64);//ascend
var t:Int64;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(a[t]>a[t+1]) then inc(t);
    if a[t]<a[x] then
    begin
        swap(a[x],a[t]);
        swap(p[x],p[t]);
        down(t);
    end;
end;

procedure delete(x:Int64);
begin
    a[x]:=a[len];
    p[x]:=p[len];
    dec(len);
    down(x);
end;

begin
    //assign(input,'/Users/wangmengxi/Desktop/Pascal/data.in');
    //reset(input);
    readln(n,m);
    for i:=1 to n do
    readln(d[i],ti[i]);
    qs(1,n);
    max:=0;
    d[0]:=0;
    for len:=n downto 0 do
    if d[len]+ti[len]<=m then break;
    while (len>=1)and(len>max) do
    begin
        las:=1;
        cnt:=0;
        for i:=1 to len do//initiate
        begin
            p[i]:=i;
            a[i]:=ti[i];
        end;
        for i:=len shr 1 downto 1 do
        down(i);
        tot:=m-d[len]-a[1];//reset tot
        //write(d[len],' ');
        while (tot>=0)and(len>=1) do
        begin
            //write(a[1],' ');
            inc(cnt);
            if p[1]>las then las:=p[1];
            delete(1);
            dec(tot,a[1]);
        end;
        //writeln;
        //writeln('cnt:',cnt);
        if cnt>max then max:=cnt;
        len:=las-1;
    end;
    writeln(max);
    //close(input);
end.



const maxn=100000;
var n,i,max,len,cnt,las:longint;
    m,tot:Int64;
    d,ti,a,p:array[0..maxn]of Int64;

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
    k:=d[(l+r)shr 1];
    repeat
        while d[x]<k do inc(x);
        while d[y]>k do dec(y);
        if x<=y then
        begin
            swap(d[x],d[y]);
            swap(ti[x],ti[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;

procedure down(x:Int64);//ascend
var t:Int64;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(a[t]>a[t+1]) then inc(t);
    if a[t]<a[x] then
    begin
        swap(a[x],a[t]);
        swap(p[x],p[t]);
        down(t);
    end;
end;

procedure delete(x:Int64);
begin
    a[x]:=a[len];
    p[x]:=p[len];
    dec(len);
    down(x);
end;

begin
    //assign(input,'/Users/wangmengxi/Desktop/Pascal/data.in');
    //reset(input);
    readln(n,m);
    for i:=1 to n do
    readln(d[i],ti[i]);
    qs(1,n);
    max:=0;
    d[0]:=0;
    ti[0]:=0;
    for len:=n downto 0 do
    if d[len]+ti[len]<=m then break;
    for i:=1 to len do//initiate
    begin
        p[i]:=i;
        a[i]:=ti[i];
    end;
    for i:=len shr 1 downto 1 do
    down(i);
    tot:=m-d[len];//reset tot
    las:=0;
    cnt:=0;
    while (tot>=a[1])and(len>=1) do
    begin
        dec(tot,a[1]);
        //write(a[1],' ');
        inc(cnt);
        if p[1]>las then las:=p[1];
        //大概每次要delete的时候，把p[1]的值搞到一个求last的大根堆里
        delete(1);
    end;
    if cnt>max then max:=cnt;
    while (len>=1)and(las>=max) do
    begin
        inc(tot,d[las]-d[las-1]+ti[las]);
        dec(cnt);
        //每次循环要last了就去大根队搞mdzz不想写了
    end;
    writeln(max);
    //close(input);
end.