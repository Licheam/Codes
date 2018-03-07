const maxn=100000;
    maxm=500000;
type edge=record
    node:longint;
    next:longint;
    end;
var n,m,i,tot,f,g,c,he,ta,ans:longint;
    head,head2,price,que,min,max:array[1..maxn]of longint;
    e:array[1..4*maxm]of edge;
    inque:array[1..maxn]of boolean;
    
procedure add(x,y:longint);
begin
    inc(tot);
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;

procedure add2(x,y:longint);
begin
    inc(tot);
    e[tot].node:=y;
    e[tot].next:=head2[x];
    head2[x]:=tot;
end;

procedure spfamin();
var u,p,v,tmin:longint;
begin
    he:=1;ta:=2;
    que[1]:=1;
    filldword(min,n,101);
    fillchar(inque,n,false);
    inque[1]:=true;
    min[1]:=price[1];
    while he<>ta do
    begin
        u:=que[he];
        inque[u]:=false;
        inc(he);
        if he>maxn then
            he:=1;
        p:=head[u];
        while p<>0 do
        begin
            v:=e[p].node;
            if min[u]>price[v] then
                tmin:=price[v]
            else tmin:=min[u];
            if min[v]>tmin then
            begin
                min[v]:=tmin;
                if not(inque[v]) then
                begin
                    que[ta]:=v;
                    inc(ta);
                    if ta>maxn then
                        ta:=1;
                end;
            end;
            p:=e[p].next;
        end;
    end;
end;

procedure spfamax();
var u,p,v,tmax:longint;
begin
    he:=1;ta:=2;
    que[1]:=n;
    filldword(max,n,0);
    fillchar(inque,n,false);
    inque[n]:=true;
    max[n]:=price[n];
    while he<>ta do
    begin
        u:=que[he];
        inque[u]:=false;
        inc(he);
        if he>maxn then
            he:=1;
        p:=head2[u];
        while p<>0 do
        begin
            v:=e[p].node;
            if max[u]<price[v] then
                tmax:=price[v]
            else tmax:=max[u];
            if max[v]<tmax then
            begin
                max[v]:=tmax;
                if not(inque[v]) then
                begin
                    que[ta]:=v;
                    inque[v]:=true;
                    inc(ta);
                    if ta>maxn then
                        ta:=1;
                end;
            end;
            p:=e[p].next;
        end;
    end;
end;

begin
    readln(n,m);
    for i:=1 to n do
        read(price[i]);
    filldword(head,n,0);
    filldword(head2,n,0);
    tot:=0;
    for i:=1 to m do
    begin
        readln(f,g,c);
        add(f,g);
        add2(g,f);
        if c=2 then
        begin
            add(g,f);
            add2(f,g);
        end;
    end;
    spfamin();
    spfamax();
    ans:=0;
    for i:=1 to n do
        if max[i]-min[i]>ans then
            ans:=max[i]-min[i];
    writeln(ans);
end.