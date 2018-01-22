const maxn=30;
    maxn2=900;
var n,i,j,cnt:longint;
    mtx:array[1..maxn,1..maxn]of longint;
    fa:array[0..maxn2]of longint;

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
    readln(n);
    cnt:=0;
    for i:=1 to n do
    for j:=1 to n do
    begin
        inc(cnt);
        read(mtx[i,j]);
        if mtx[i,j]=1 then continue;
        fa[cnt]:=cnt;
        if (i=1)or(j=1)or(i=n)or(j=n) then
        union(cnt,0);
        if (i>1)and(mtx[i,j]=mtx[i-1,j]) then
        union(cnt,cnt-n);
        if (j>1)and(mtx[i,j]=mtx[i,j-1]) then
        union(cnt,cnt-1);
    end;
    cnt:=0;
    for i:=1 to n do
    begin
        for j:=1 to n-1 do
        begin
            inc(cnt);
            if (mtx[i,j]=0)and(find(cnt)<>find(0)) then
            mtx[i,j]:=2;
            write(mtx[i,j],' ');
        end;
        inc(cnt);
        if (mtx[i,n]=0)and(find(cnt)<>find(0)) then
        mtx[i,n]:=2;
        writeln(mtx[i,n]);
    end;
end.