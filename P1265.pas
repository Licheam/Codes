const maxn=5000;
    maxkey=30000000;
var n,i:longint;
    key:array[1..maxn]of double;
    a,b:array[1..maxn]of longint;
    flag:array[1..maxn]of boolean;
    ans:double;

procedure prim();
var i,j,p:longint;
    min,tem:double;
begin
    fillchar(flag,n,false);
    flag[1]:=true;
    for i:=2 to n do
        key[i]:=sqrt((a[1]-a[i])*(a[1]-a[i])+(b[1]-b[i])*(b[1]-b[i]));
    for i:=1 to n-1 do
    begin
        min:=maxkey;
        for j:=1 to n do
            if (not flag[j])and(min>key[j]) then
            begin
                min:=key[j];
                p:=j;
            end;
        ans:=ans+min;
        flag[p]:=true;
        for j:=1 to n do
            if not(flag[j]) then
            begin
                tem:=sqrt((a[p]-a[j])*(a[p]-a[j])+(b[p]-b[j])*(b[p]-b[j]));
                if tem<key[j] then
                    key[j]:=tem;
            end;
    end;
end;

begin
    readln(n);
    for i:=1 to n do
        readln(a[i],b[i]);
    ans:=0;
    prim;
    writeln(ans:0:2);
end.