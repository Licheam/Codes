const maxn=10000;
    maxm=50000;
    maxlogn=14;
    maxcarry=100000;
type edge=record
    w:longint;
    node:longint;
    next:longint;
    end;
var n,m,i,tot,ques,a,b:longint;
    head,fa,depth:array[1..maxn]of longint;
    f,g,w:array[1..maxm]of longint;
    e:array[1..2*maxn]of edge;
    dist,carry:array[1..maxn,0..maxlogn]of longint;

procedure add(x,y,z:longint);
begin
    //writeln('add ',x,' ',y,' ',z);
    inc(tot);
    e[tot].w:=z;
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;

function min(x,y:longint):longint;
begin
    if x>y then exit(y)
    else exit(x);
end;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:longint);//descend
var x,y,key:longint;
begin
    x:=l;y:=r;
    key:=w[(l+r)shr 1];
    repeat
        while w[x]>key do inc(x);
        while w[y]<key do dec(y);
        if x<=y then
        begin
            swap(w[x],w[y]);
            swap(f[x],f[y]);
            swap(g[x],g[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if x<r then qs(x,r);
    if y>l then qs(l,y);
end;

function find(x:longint):longint;
begin
    if fa[x]=x then
        exit(x);
    fa[x]:=find(fa[x]);
    exit(fa[x]);
end;

procedure kruskal();
var i,rx,ry:longint;
begin
    for i:=1 to n do
        fa[i]:=i;
    filldword(head,n,0);
    tot:=0;
    for i:=1 to m do
    begin
        rx:=find(f[i]);
        ry:=find(g[i]);
        if rx=ry then
            continue;
        fa[rx]:=ry;
        add(f[i],g[i],w[i]);
        add(g[i],f[i],w[i]);//建树
    end;
end;

procedure dfs(x,last,w:longint);
var i:longint;
begin
    //writeln('dfsing:',x,' from ',last,' with ',w);
    depth[x]:=depth[last]+1;
    dist[x,0]:=last;
    carry[x,0]:=w;
    i:=1;
    while (1 shl i)<=depth[x] do
    begin
        dist[x,i]:=dist[dist[x,i-1],i-1];
        carry[x,i]:=min(carry[x,i-1],carry[dist[x,i-1],i-1]);
        inc(i);
    end;
    i:=head[x];
    while i<>0 do
    begin
        if e[i].node<>last then
            dfs(e[i].node,x,e[i].w);
        i:=e[i].next;
    end;
end;

function get_carry(x,y:longint):longint;
var ans,d,i,maxl:longint;
begin
    ans:=maxcarry;
    if depth[x]<depth[y] then
        swap(x,y);
    d:=depth[x]-depth[y];
    i:=0;
    while d>0 do
    begin
        if (d and 1)=1 then
        begin
            ans:=min(ans,carry[x,i]);
            x:=dist[x,i];
        end;
        d:=d shr 1;
        inc(i);
    end;
    maxl:=trunc(ln(depth[x])/ln(2));
    for i:=maxl downto 0 do
    begin
        if dist[x,i]<>dist[y,i] then
        begin
            ans:=min(ans,carry[x,i]);
            ans:=min(ans,carry[y,i]);
            x:=dist[x,i];
            y:=dist[y,i];
        end;
    end;
    if x<>y then
        ans:=min(min(ans,carry[x,0]),carry[y,0]);
    exit(ans);
end;

begin
    readln(n,m);
    for i:=1 to m do
        readln(f[i],g[i],w[i]);
    qs(1,m);
    kruskal;
    //writeln('kruskal finish');
    filldword(depth,n,0);
    for i:=1 to n do
        if depth[i]=0 then
            dfs(i,i,maxcarry);
    //writeln('dfs finish');
    readln(ques);
    for i:=1 to ques do
    begin
        readln(a,b);
        if find(a)=find(b) then
            writeln(get_carry(a,b))
        else writeln(-1);
    end;
end.