const maxn=50000;
var n,m,i,j,le,ri,p:longint;
    stmin,stmax:array[1..maxn,0..15]of longint;

function min(x,y:longint):longint;
begin
    if x>y then exit(y)
    else exit(x);
end;

function max(x,y:longint):longint;
begin
    if x>y then exit(x)
    else exit(y);
end;

begin
    readln(n,m);
    for i:=1 to n do
    begin
        readln(stmin[i,0]);
        stmax[i,0]:=stmin[i,0];
    end;
    for j:=1 to trunc(ln(n)/ln(2)) do
        for i:=1 to n-(1 shl j)+1 do
        begin
            stmin[i,j]:=min(stmin[i,j-1],stmin[i+(1 shl (j-1)),j-1]);
            stmax[i,j]:=max(stmax[i,j-1],stmax[i+(1 shl (j-1)),j-1]);
        end;
    for i:=1 to m do
    begin
        readln(le,ri);
        p:=trunc(ln(ri-le+1)/ln(2));
        writeln(max(stmax[le,p],stmax[ri-(1 shl p)+1,p])-min(stmin[le,p],stmin[ri-(1 shl p)+1,p]));
    end;
end.