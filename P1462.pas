const maxn=10000;
    maxm=500000;

type edge=record
    v:longint;
    next:longint;
    node:longint;
    end;

var n,m,hp,i,f,g,w,len,tot:longint;
    e:array[1..2*maxm]of edge;
    dam,head,cost,bi:array[1..maxn]of longint;
    h,hash:array[1..2*maxm]of longint;
    b:array[1..maxn]of boolean;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure add(x,y,z:longint);
begin
    inc(tot);
    e[tot].v:=z;
    e[tot].next:=head[x];
    e[tot].node:=y;
    head[x]:=tot;
end;

procedure qs(l,r:longint);//ascend
var x,y,k:longint;
begin
    x:=l;y:=r;
    k:=bi[(l+r)shr 1];
    repeat
        while bi[x]<k do inc(x);
        while bi[y]>k do dec(y);
        if x<=y then
        begin
            swap(bi[x],bi[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
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

function checkdij(x:longint):boolean;//交费最多x
var i,q:longint;
    t:Int64;
begin
    if (e[1].v>x)or(e[n].v>x) then
    exit(false);
    b[1]:=true;
    for i:=2 to n do
    begin
        dam[i]:=maxlongint;
        hash[i]:=i;
        if cost[i]>x then
        b[i]:=false
        else
        b[i]:=true;
    end;
    len:=0;
    dam[1]:=0;
    insert(0,1);
    while len>0 do
    begin
        if dam[hash[1]]>=h[1] then
        begin
            q:=head[hash[1]];//取hash1的邻接表
            while q<>0 do
            begin
                if b[e[q].node] then
                begin
                    t:=h[1]+e[q].v;
                    if t<dam[e[q].node] then 
                    begin
                        //writeln('add ',hash[1],' to ',e[q].node,' to ',t);
                        dam[e[q].node]:=t;
                        insert(t,e[q].node);
                    end;
                end;
                q:=e[q].next;
            end;
        end;
        delete(1);
    end;
    if dam[n]>=hp then exit(false)
    else exit(true);
end;

function bis(l,r:longint):longint;
var mid:longint;
begin
    while l<r do
    begin
        mid:=(l+r)shr 1;
        if checkdij(bi[mid]) then
        r:=mid
        else l:=mid+1;
    end;
    exit(bi[l]);
end;

begin
    readln(n,m,hp);
    for i:=1 to n do
    begin
        readln(cost[i]);
        bi[i]:=cost[i];
    end;
    qs(1,n);
    tot:=0;
    filldword(head,n,0);
    for i:=1 to m do
    begin
        readln(f,g,w);
        add(f,g,w);
        add(g,f,w);
    end;
    if not(checkdij(bi[n])) then
    writeln('AFK')
    else
    writeln(bis(1,n));
end.