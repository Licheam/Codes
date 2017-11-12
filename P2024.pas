const maxn=50000;
var n,m,i,c,t1,t2,cnt:longint;
    fa:array[1..3*maxn]of longint;//1->2,3->1

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
    readln(n,m);
    for i:=1 to 3*n do
    fa[i]:=i;
    cnt:=0;
    for i:=1 to m do
    begin
        readln(c,t1,t2);
        if (t1>n)or(t2>n) then inc(cnt)
        else if c=1 then
        begin
            if t1=t2 then continue;
            if (find(t1)=find(n+t2))or(find(t1)=find(2*n+t2)) then
            begin
                inc(cnt);
                continue;
            end;
            union(t1,t2);
            union(n+t1,n+t2);
            union(2*n+t1,2*n+t2);
        end
        else
        begin
            if (t1=t2)or(find(t1)=find(t2))or(find(t2)=find(n+t1)) then
            begin
                inc(cnt);
                continue;
            end;
            union(t1,n+t2);
            union(n+t1,2*n+t2);
            union(2*n+t1,t2);
        end;
    end;
    writeln(cnt);
end.