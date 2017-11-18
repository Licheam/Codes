const maxn=100000;
    p=1000000007;
var n,m,i,j,l1,r1,l2,r2,cnt:longint;
    fa:array[1..maxn,0..16]of longint;

function find(x,y:longint):longint;
begin
    if fa[x,y]=x then exit(x);
    fa[x,y]:=find(fa[x,y],y);
    exit(fa[x,y]);
end;

procedure union(x1,x2,t:longint);
begin
    fa[find(x1,t),t]:=find(x2,t);
end;

function binpow(x,y:longint):longint;
begin
    binpow:=1;
    while y<>0 do
    begin
        if (y and 1)=1 then binpow:=binpow*x mod p;
        x:=x*x mod p;
        y:=y shr 1;
    end;
end;

begin
    readln(n,m);
    for i:=1 to n do
        fa[i,0]:=i;
    for j:=1 to trunc(ln(n)/ln(2)) do
        for i:=1 to n-(1 shl j)+1 do
            fa[i,j]:=i;
    for i:=1 to m do
    begin
        readln(l1,r1,l2,r2);
        for j:=trunc(ln(r1-l1+1)/ln(2)) downto 0 do
            if l1+(1 shl j)-1<=r1 then
            begin
                union(l1,l2,j);
                //writeln('union(',l1,'to',l1+(1 shl j)-1,',',l2,'to',l2+(1 shl j)-1,')');
                inc(l1,1 shl j);
                inc(l2,1 shl j);
            end;
    end;
    for j:=trunc(ln(n)/ln(2)) downto 1 do
        for i:=1 to n-(1 shl j)+1 do
        begin
            union(i,fa[i,j],j-1);
            union(i+(1 shl (j-1)),fa[i,j]+(1 shl (j-1)),j-1);//fa[i,j]+(1 shl (j-1))精髓啊！
        end;
    cnt:=0;
    for i:=1 to n do
        if fa[i,0]=i then
            inc(cnt);
    //writeln('f[i,0]:');
    //for i:=1 to n do
    //write(fa[i,0],' ');
    //writeln('cnt:',cnt);
    writeln(9*binpow(10,cnt-1) mod p);
end.