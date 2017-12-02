const maxn=100;
    maxm=9900;
var n,m,ts,te,i,j,len:longint;
    e:array[1..maxn,1..maxn]of longint;
    h,hash:array[1..maxm]of longint;
    times,outdgr:array[1..maxn]of longint;
    flag:array[1..maxn]of boolean;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure up(x:longint);//small root.
var t:longint;
begin
    t:=x shr 1;
    if (x>1)and(h[x]<h[t]) then
    begin
        swap(h[x],h[t]);
        swap(hash[x],hash[t]);
        up(t);
    end;
end;

procedure down(x:longint);
var t:longint;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(h[t]>h[t+1]) then inc(t);
    if h[t]<h[x] then
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

procedure dijkstra(ps,pe:longint);
var i,u:longint;
begin
    filldword(times,n,maxlongint);
    fillchar(flag,n,false);
    len:=0;
    times[ps]:=0;
    insert(0,ps);
    while len>0 do
    begin
        u:=hash[1];
        flag[u]:=true;
        if u=pe then exit;
        if h[1]<times[e[u,1]] then
        begin
            times[e[u,1]]:=h[1];
            insert(h[1],e[u,1]);
        end;
        inc(h[1]);
        for i:=2 to outdgr[u] do
            if (not flag[e[u,i]])and(h[1]<times[e[u,i]]) then
            begin
                times[e[u,i]]:=h[1];
                insert(h[1],e[u,i]);
            end;
        while (flag[hash[1]])and(len>0) do delete(1);
    end;
end;

begin
    readln(n,ts,te);
    for i:=1 to n do
    begin
        read(m);
        outdgr[i]:=m;
        for j:=1 to m do
        read(e[i,j]);
    end;
    dijkstra(ts,te);
    if flag[te] then
    writeln(times[te])
    else writeln(-1);
end.