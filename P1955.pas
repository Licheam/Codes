{//Least Prime 最近质数
var a,i:longint;

function prime(x:longint):boolean;
var k:longint;
begin
    for k:=2 to trunc(sqrt(x)) do
    if x mod k=0 then exit(false);
    exit(true);
end;

begin
    readln(a);
    i:=0;
    while not((prime(a-i))or(prime(a+i))) do
    inc(i);
    if prime(a+i) then writeln(a+i)
    else writeln(a-i);
end.}
//没用离散，用hash随便搞了下。
const maxn=100000;
    pri=520123;
var q,n,i,j,e,cnt:longint;
    fa:array[1..pri]of longint;
    x1,x2:array[1..maxn]of longint;

function find(x:longint):longint;
begin
    if x=fa[x] then exit(x);
    fa[x]:=find(fa[x]);
    exit(fa[x]);
end;

procedure union(x,y:longint);
begin
    fa[find(y)]:=find(x);
end;

begin
    readln(q);
    for i:=1 to q do
    begin
        readln(n);
        for j:=1 to pri do
        fa[j]:=j;
        cnt:=1;
        for j:=1 to n do
        begin
            readln(x1[cnt],x2[cnt],e);
            x1[cnt]:=(x1[cnt] mod pri)+1;
            x2[cnt]:=(x2[cnt] mod pri)+1;
            if e=0 then inc(cnt)
            else
            union(x1[cnt],x2[cnt]);
        end;
        dec(cnt);
        for j:=1 to cnt do
        if find(x1[j])=find(x2[j]) then break;
        if cnt=0 then writeln('YES')
        else if (j<cnt)or(find(x1[j])=find(x2[j])) then writeln('NO')
        else writeln('YES');
    end;
end.