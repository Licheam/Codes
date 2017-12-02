const maxm=12400;
    maxn=2500;
    maxc=62000001;
    
type edge=record
    cost:longint;
    next:longint;
    node:longint;
    end;
    
var n,m,i,ts,te,tot,rs,re,co,len:longint;
    a,head:array[1..maxn]of longint;
    h,hash:array[1..maxm]of longint;
    e:array[1..maxm]of edge;
    flag:array[1..maxn]of boolean;
    
procedure add(x,y,z:longint);
begin
    inc(tot);
    e[tot].cost:=z;
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;
    
procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;
    
procedure up(x:longint);
var t:longint;
begin
    t:=x shr 1;
    if (t>0)and(h[x]<h[t]) then
    begin
        swap(h[x],h[t]);
        swap(hash[x],hash[t]);
        up(t);
    end;
end;
    
procedure down(x:longint);//small root
var t:longint;
begin
    t:=x shl 1;
    if (t<len)and(h[t]>h[t+1]) then inc(t)
    else if t>len then exit;
    if h[x]>h[t] then
    begin
        swap(h[x],h[t]);
        swap(hash[x],hash[t]);
        down(t);
    end;
end;

procedure insert(x,y:longint);
begin
    inc(len);
    h[len]:=x;
    hash[len]:=y;
    up(len);
end;

procedure delete(x:longint);
begin
    h[x]:=h[len];
    hash[x]:=hash[len];
    dec(len);
    down(x);
end;
    
procedure dijkstra(x,y:longint);
var q,i,u:longint;
begin
    filldword(a,n,maxc);
    fillchar(flag,n,false);
    len:=0;
    a[x]:=0;
    insert(0,x);
    for i:=1 to n do
    begin
        u:=hash[1];
        if u=y then exit;
        flag[u]:=true;
        q:=head[u];
        while q<>0 do
        begin
            if (not flag[e[q].node])and(a[e[q].node]>e[q].cost+a[u]) then
            begin
                a[e[q].node]:=e[q].cost+a[u];
                insert(a[e[q].node],e[q].node);
            end;
            q:=e[q].next;
        end;
        while flag[hash[1]] do delete(1);
    end;
end;
    
begin
    readln(n,m,ts,te);
    tot:=0;
    filldword(head,n,0);
    for i:=1 to m do
    begin
        read(rs,re,co);
        add(rs,re,co);
        add(re,rs,co);
    end;
    dijkstra(ts,te);
    writeln(a[te]);
end.