const maxn=1001;
var n,m,i,j,k,h,r:longint;
    a,b,c,fa:array[0..maxn]of longint;

function find(x:longint):longint;
begin
    if fa[x]=x then exit(x);
    fa[x]:=find(fa[x]);
    exit(fa[x]);
end;

procedure union(x,y:longint);
begin
    fa[find(x)]:=find(y);
end;

begin
    readln(m);
    for i:=1 to m do
    begin
        readln(n,h,r);
        for j:=1 to n do
        begin
            readln(a[j],b[j],c[j]);
            fa[j]:=j;
        end;
        fa[0]:=0;
        fa[n+1]:=n+1;
        for j:=1 to n-1 do
        for k:=j+1 to n do
        begin
            if (a[j]-a[k])*(a[j]-a[k])+(b[j]-b[k])*(b[j]-b[k])+(c[j]-c[k])*(c[j]-c[k])<=4*r*r then
            union(j,k);
        end;
        for k:=1 to n do
        begin
            if abs(c[k]-0)<=r then
            union(0,k);
            if abs(h-c[k])<=r then
            union(n+1,k);
        end;
        //for j:=0 to n+1 do writeln(find(j));
        if find(0)=find(n+1) then
        writeln('Yes')
        else writeln('No');
    end;
end.