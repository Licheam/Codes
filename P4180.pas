program Strict_Second_Best_Minimum_Spanning_Tree;
const maxn=100000;
    maxm=300000;
    maxlogn=17;
    maxmst=100000000000000;
type edge=record
    w:Int64;
    node:Int64;
    next:Int64;
    end;
var n,m,tot,mst,sbmst,tem:Int64;
    i:longint;
    head,fa,depth:array[1..maxn]of Int64;
    f,g,w:array[1..maxm]of Int64;
    e:array[1..2*maxn]of edge;
    dist,bneck,sbneck:array[1..maxn,0..maxlogn]of Int64;
    flag:array[1..maxm]of boolean;

procedure add(x,y,z:Int64);
begin
    //writeln('add ',x,' ',y,' ',z);
    inc(tot);
    e[tot].w:=z;
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;

function max(x,y:Int64):Int64;
begin
    if x>y then exit(x)
    else exit(y);
end;

procedure swap(var x,y:Int64);
var t:Int64;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:Int64);//ascend
var x,y,key:Int64;
begin
    x:=l;y:=r;
    key:=w[(l+r)shr 1];
    repeat
        while w[x]<key do inc(x);
        while w[y]>key do dec(y);
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

function find(x:Int64):Int64;
begin
    if fa[x]=x then
        exit(x);
    fa[x]:=find(fa[x]);
    exit(fa[x]);
end;

procedure kruskal();
var rx,ry:Int64;
    i:longint;
begin
    mst:=0;
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
        inc(mst,w[i]);
        flag[i]:=true;
        add(f[i],g[i],w[i]);
        add(g[i],f[i],w[i]);//建树
    end;
end;

procedure dfs(x,last,w:Int64);
var i:longint;
begin
    //writeln('dfsing:',x,' from ',last,' with ',w);
    depth[x]:=depth[last]+1;
    dist[x,0]:=last;
    bneck[x,0]:=w;
    sbneck[x,0]:=0;
    i:=1;
    while (1 shl i)<=depth[x] do
    begin
        dist[x,i]:=dist[dist[x,i-1],i-1];
        bneck[x,i]:=max(bneck[x,i-1],bneck[dist[x,i-1],i-1]);
        if bneck[x,i-1]>bneck[dist[x,i-1],i-1] then
            sbneck[x,i]:=max(sbneck[x,i-1],bneck[dist[x,i-1],i-1])
        else if bneck[x,i-1]<bneck[dist[x,i-1],i-1] then
            sbneck[x,i]:=max(sbneck[dist[x,i-1],i-1],bneck[x,i-1])
        else sbneck[x,i]:=max(sbneck[x,i-1],sbneck[dist[x,i-1],i-1]);
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

function get_bneck(x,y:Int64):Int64;//最长瓶颈路
var ans,d,maxl:Int64;
    i:longint;
begin
    ans:=0;
    if depth[x]<depth[y] then
        swap(x,y);
    d:=depth[x]-depth[y];
    i:=0;
    while d>0 do
    begin
        if (d and 1)=1 then
        begin
            ans:=max(ans,bneck[x,i]);
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
            ans:=max(ans,bneck[x,i]);
            ans:=max(ans,bneck[y,i]);
            x:=dist[x,i];
            y:=dist[y,i];
        end;
    end;
    if x<>y then
        ans:=max(max(ans,bneck[x,0]),bneck[y,0]);
    exit(ans);
end;

function get_sbneck(x,y:Int64):Int64;//严格次长瓶颈路
var ans,d,maxl,sbans:Int64;
    i:longint;
begin
    ans:=0;
    sbans:=0;
    if depth[x]<depth[y] then
        swap(x,y);
    d:=depth[x]-depth[y];
    i:=0;
    while d>0 do
    begin
        if (d and 1)=1 then
        begin
            if ans>bneck[x,i] then
                sbans:=max(sbans,bneck[x,i])
            else if ans<bneck[x,i] then
                sbans:=max(ans,sbneck[x,i])
            else sbans:=max(sbans,sbneck[x,i]);
            ans:=max(ans,bneck[x,i]);
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
            if ans>bneck[x,i] then
                sbans:=max(sbans,bneck[x,i])
            else if ans<bneck[x,i] then
                sbans:=max(ans,sbneck[x,i])
            else sbans:=max(sbans,sbneck[x,i]);
            ans:=max(ans,bneck[x,i]);
            if ans>bneck[y,i] then
                sbans:=max(sbans,bneck[y,i])
            else if ans<bneck[y,i] then
                sbans:=max(ans,sbneck[y,i])
            else sbans:=max(sbans,sbneck[y,i]);
            ans:=max(ans,bneck[y,i]);
            x:=dist[x,i];
            y:=dist[y,i];
        end;
    end;
    if x<>y then
    begin
        if ans>bneck[x,0] then
            sbans:=max(sbans,bneck[x,0])
        else if ans<bneck[x,i] then
            sbans:=max(ans,sbneck[x,i])
        else sbans:=max(sbans,sbneck[x,i]);
        ans:=max(ans,bneck[x,0]);
        if ans>bneck[y,0] then
            sbans:=max(sbans,bneck[y,0])
        else if ans<bneck[y,i] then
            sbans:=max(ans,sbneck[y,i])
        else sbans:=max(sbans,sbneck[y,i]);
    end;
    exit(sbans);
end;

begin
    readln(n,m);
    for i:=1 to m do
        readln(f[i],g[i],w[i]);
    fillchar(flag,m,false);
    qs(1,m);
    kruskal;
    //writeln('kruskal finish');
    filldword(depth,n,0);
    for i:=1 to n do
        if depth[i]=0 then
            dfs(i,i,0);
    //writeln('dfs finish');
    //for i:=1 to n do
    //    writeln(sbneck[i,0],' ',sbneck[i,1]);
    sbmst:=maxmst;
    for i:=1 to m do
        if not(flag[i]) then
        begin
            tem:=get_bneck(f[i],g[i]);
            if tem=w[i] then
                tem:=get_sbneck(f[i],g[i]);
            //writeln('tem',tem);
            if tem=0 then continue;
            tem:=mst+w[i]-tem;
            if tem<sbmst then
                sbmst:=tem;
        end;
    writeln(sbmst);
end.