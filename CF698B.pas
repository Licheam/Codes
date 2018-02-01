const maxn=200000;
var n,i,r1,r2,cnt,self:longint;
    a,fa:array[1..maxn]of longint;

function find(x:longint):longint;
begin
    if fa[x]=x then
        exit(x);
    fa[x]:=find(fa[x]);
    exit(fa[x]);
end;

begin
    readln(n);
    for i:=1 to n do
        fa[i]:=i;
    cnt:=0;
    self:=0;
    for i:=1 to n do
    begin
        read(a[i]);
        if a[i]=i then
        begin
            if self=0 then self:=i
            else
            inc(cnt);
            continue;
        end;
        r1:=find(i);
        r2:=find(a[i]);
        if r1=r2 then
        begin
            inc(cnt);
            a[i]:=i;
        end
        else fa[r1]:=r2;
    end;
    writeln(cnt);
    for i:=1 to n do
        if a[i]=i then
        begin
            if self=0 then
                self:=i;
            a[i]:=self;
        end;
    for i:=1 to n do
        write(a[i],' ');
end.