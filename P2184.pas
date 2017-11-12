const maxn=100005;
var n,m,i,c,left,right:longint;
    le,ri:array[1..maxn]of longint;

function lowbit(x:longint):longint;
begin
    exit(x and (-x));
end;

procedure changel(x:longint);
begin
    while x<=n do
    begin
        inc(le[x]);
        inc(x,lowbit(x));
    end;
end;

function suml(x:longint):longint;
begin
    suml:=0;
    while x>0 do
    begin
        inc(suml,le[x]);
        dec(x,lowbit(x));
    end;
end;

procedure changer(x:longint);
begin
    while x<=n do
    begin
        inc(ri[x]);
        inc(x,lowbit(x));
    end;
end;

function sumr(x:longint):longint;
begin
    sumr:=0;
    while x>0 do
    begin
        inc(sumr,ri[x]);
        dec(x,lowbit(x));
    end;
end;

begin
    readln(n,m);
    filldword(le,n,0);
    filldword(ri,n,0);
    for i:=1 to m do
    begin
        readln(c,left,right);
        if c=1 then
        begin
            changel(left);
            changer(right+1);
        end
        else
        writeln(suml(right)-sumr(left));
    end;
end.