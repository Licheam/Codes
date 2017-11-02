const maxn=25;
var n,i,j,h,tot,len,max:longint;
    f,d,ti,a,ad:array[1..maxn]of longint;

function gmax(x,y:longint):longint;
begin
    if a[x]<a[y] then exit(y)
    else exit(x);
end;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure up(x:longint);//great_root
var t:longint;
begin
    t:=x shr 1;
    if (x>1)and(a[x]>a[t]) then
    begin
        swap(a[x],a[t]);
        swap(ad[x],ad[t]);
        up(t);
    end;
end;

procedure down(x:longint);
var t,k:longint;
begin
    t:=x shl 1;
    if t>len then exit
    else if t=len then k:=t
    else k:=gmax(t,t+1);
    if a[k]>a[x] then
    begin
        swap(a[x],a[k]);
        swap(ad[x],ad[k]);
        down(k);
    end;
end;

procedure ini(x:longint);
var k:longint;
begin
    len:=x;
    for k:=1 to x do
    begin
        a[k]:=f[k];
        ad[k]:=d[k];
    end;
    for k:=len shr 1 downto 1 do down(k);
end;

begin
    readln(n);
    readln(h);
    h:=h*12;
    for i:=1 to n do read(f[i]);
    for i:=1 to n do read(d[i]);
    ti[1]:=0;
    for i:=2 to n do read(ti[i]);
    max:=0;
    for i:=1 to n do
    begin
        tot:=0;
        dec(h,ti[i]);
        ini(i);
        for j:=1 to h do
        begin
            inc(tot,a[1]);
            dec(a[1],ad[1]);
            down(1);
            //for temp:=1 to len do write(a[temp],' ');
            //writeln;
            if a[1]<=0 then break;
        end;
        if tot>max then max:=tot;
    end;
    writeln(max);
end.