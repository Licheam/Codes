const maxn=150;
    maxn3t2=6772500;
    inf=1000000000;
    tabx:array[1..5]of longint=(0,1,-1,0,0);
    taby:array[1..5]of longint=(0,0,0,1,-1);

var n,m,mx,x1,y1,x2,y2,x3,y3,a1,a2,b1,b2,c1,c2,len:longint;
    i,j:longint;
    ans:Int64;
    ansc:char;
    a,b:array[1..maxn,1..maxn]of longint;
    cost:array[1..maxn,1..maxn,0..2*maxn]of longint;
    po:array[1..maxn,1..maxn,0..2*maxn]of longint;
    hx,hy,hs:array[1..maxn3t2] of longint;

function min(x,y:longint):longint;
begin
    if x>y then exit(y)
    else exit(x);
end;

function max(x,y:longint):longint;
begin
    if x>y then exit(x)
    else exit(y);
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
    if (x>1)and(cost[hx[t],hy[t],hs[t]]>cost[hx[x],hy[x],hs[x]]) then
    begin
        swap(po[hx[x],hy[x],hs[x]],po[hx[t],hy[t],hs[t]]);
        swap(hx[x],hx[t]);
        swap(hy[x],hy[t]);
        swap(hs[x],hs[t]);
        up(t);
    end;
end;

procedure down(x:longint);
var t:longint;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(cost[hx[t],hy[t],hs[t]]>cost[hx[t+1],hy[t+1],hs[t+1]]) then inc(t);
    if cost[hx[t],hy[t],hs[t]]<cost[hx[x],hy[x],hs[x]] then
    begin
        swap(po[hx[x],hy[x],hs[x]],po[hx[t],hy[t],hs[t]]);
        swap(hx[x],hx[t]);
        swap(hy[x],hy[t]);
        swap(hs[x],hs[t]);
        down(t);
    end;
end;

procedure insert(x,y,s:longint);
begin
    inc(len);
    hx[len]:=x;
    hy[len]:=y;
    hs[len]:=s;
    po[x,y,s]:=len;
    up(len);
end;

procedure delete(x:longint);
begin
    po[hx[len],hy[len],hs[len]]:=x;
    hx[x]:=hx[len];
    hy[x]:=hy[len];
    hs[x]:=hs[len];
    dec(len);
    down(x);
end;

procedure dijkstra(x,y:longint);
var i,j,k:longint;
    tx,ty,ts,ttx,tty:longint;
begin
    for i:=1 to n do
        for j:=1 to m do
            for k:=0 to mx do
            begin
                po[i,j,k]:=0;//haven't visited
                cost[i,j,k]:=inf;
            end;
    len:=0;
    po[x,y,0]:=-1;//visited
    cost[x,y,0]:=0;
    cost[x,y,a[x,y]]:=b[x,y];
    insert(x,y,a[x,y]);
    while (len>0)and(not((po[x1,y1,0]=-1)and(po[x2,y2,0]=-1)and(po[x3,y3,0]=-1))) do
    begin
        tx:=hx[1];ty:=hy[1];ts:=hs[1];
        delete(1);
        po[tx,ty,ts]:=-1;
        if ts>0 then
        begin
            for i:=1 to 5 do
            begin
                ttx:=tx+tabx[i];tty:=ty+taby[i];
                if (ttx<1)or(tty<1)or(ttx>n)or(tty>m) then
                    continue;
                if cost[tx,ty,ts]<cost[ttx,tty,ts-1] then
                begin
                    cost[ttx,tty,ts-1]:=cost[tx,ty,ts];
                    if po[ttx,tty,ts-1]=0 then
                        insert(ttx,tty,ts-1)
                    else up(po[ttx,tty,ts-1]);
                end;
            end;
        end
        else
        begin
            if cost[tx,ty,a[tx,ty]]>cost[tx,ty,0]+b[tx,ty] then
            begin
                cost[tx,ty,a[tx,ty]]:=cost[tx,ty,0]+b[tx,ty];
                if po[tx,ty,a[tx,ty]]=0 then
                    insert(tx,ty,a[tx,ty])
                else up(po[tx,ty,a[tx,ty]]);
            end;
        end;
    end;
end;

begin
    readln(n,m);
    mx:=n+m-2;
    for i:=1 to n do
        for j:=1 to m do
        begin
            read(a[i,j]);
            a[i,j]:=min(a[i,j],max(mx-i-j,i+j-2));
        end;
    for i:=1 to n do
        for j:=1 to m do
            read(b[i,j]);
    readln(x1,y1,x2,y2,x3,y3);
    dijkstra(x1,y1);
    a1:=cost[x2,y2,0];a2:=cost[x3,y3,0];
    dijkstra(x2,y2);
    b1:=cost[x1,y1,0];b2:=cost[x3,y3,0];
    dijkstra(x3,y3);
    c1:=cost[x1,y1,0];c2:=cost[x2,y2,0];
    ans:=inf;
    if b1+c1<ans then
    begin
        ans:=b1+c1;
        ansc:='X';
    end;
    if a1+c2<ans then
    begin
        ans:=a1+c2;
        ansc:='Y';
    end;
    if a2+b2<ans then
    begin
        ans:=a2+b2;
        ansc:='Z';
    end;
    if ans=inf then
    writeln('NO')
    else
    begin
        writeln(ansc);
        writeln(ans);
    end;
end.