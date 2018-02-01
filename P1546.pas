const maxn=100;
    maxkey=100000;
var n,i,j,ans:longint;
    key:array[1..maxn]of longint;
    mtx:array[1..maxn,1..maxn]of longint;
    flag:array[1..maxn]of boolean;

procedure prim();
var i,j,min,p:longint;
begin
    fillchar(flag,n,false);
    flag[1]:=true;
    for i:=2 to n do
        key[i]:=mtx[1,i];
    for i:=1 to n-1 do
    begin
        min:=maxkey;
        for j:=1 to n do
            if (not flag[j])and(min>key[j]) then
            begin
                min:=key[j];
                p:=j;
            end;
        inc(ans,min);
        flag[p]:=true;
        for j:=1 to n do
            if (not flag[j])and(mtx[p,j]<key[j]) then
                key[j]:=mtx[p,j];
    end;
end;

begin
    readln(n);
    for i:=1 to n do
    for j:=1 to n do
        read(mtx[i,j]);
    ans:=0;
    prim;
    writeln(ans);
end.