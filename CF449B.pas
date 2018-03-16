const maxn=100000;
    maxm=300000;
    maxk=100000;
    maxe=700000;
    maxw=maxn*1000000000;
type edge=record
    w:Int64;
    node:Int64;
    next:Int64;
    end;
var n,m,m2,k,tot,f,g,v,p,q,cnt:Int64;
    i:longint;
    head,dist,que:array[1..maxn]of Int64;
    e:array[1..maxe]of edge;
    inque,vis:array[1..maxn]of boolean;

procedure add(x,y,z:Int64);
begin
    inc(tot);
    e[tot].w:=z;
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;

procedure spfa(s:Int64);
var l,r,u,p,sum,len:Int64;
begin
    filldword(dist,n shl 1,maxw);
    fillchar(inque,n,false);
    l:=1;r:=2;
    que[l]:=s;
    dist[s]:=0;
    inque[s]:=true;
    sum:=0;
    len:=1;
    while l<>r do
    begin
        while len*dist[que[l]]>sum do//LLL优化(large label last)
        begin
            que[r]:=que[l];
            inc(r);
            if r>maxn then
                r:=1;
            inc(l);
            if l>maxn then
                l:=1;
        end;
        u:=que[l];
        inc(l);
        if l>maxn then
            l:=1;
        inque[u]:=false;
        dec(sum,dist[u]);
        dec(len);
        p:=head[u];
        while p<>0 do
        begin
            v:=e[p].node;
            if dist[u]+e[p].w<dist[v] then
            begin
                dist[v]:=dist[u]+e[p].w;
                if not(inque[v]) then
                begin
                    if (l<>r)and(dist[v]<dist[que[l]]) then//SLF
                    begin
                        dec(l);
                        if l=0 then
                            l:=maxn;
                        que[l]:=v;
                    end
                    else
                    begin
                        que[r]:=v;
                        inc(r);
                        if r>maxn then
                            r:=1;
                    end;
                    inc(sum,dist[v]);
                    inc(len);
                    inque[v]:=true;
                end;
            end;
            p:=e[p].next;
        end;
    end;
end;

begin
    readln(n,m,k);
    tot:=0;
    filldword(head,n,0);
    for i:=1 to m do
    begin
        readln(f,g,v);
        add(f,g,v);
        add(g,f,v);
    end;
    for i:=1 to k do
    begin
        readln(g,v);
        add(1,g,v);
    end;
    spfa(1);
    
    {for i:=1 to n do
        writeln(dist[i]);}
    
    cnt:=0;
    fillchar(vis,n,false);
    m2:=m shl 1;
    p:=head[1];
    while p<>0 do
    begin
        if p<=m2 then
        begin
            p:=e[p].next;
            continue;
        end;
        v:=e[p].node;
        if (dist[v]<e[p].w)or(vis[v]) then
            inc(cnt)
        else
        begin
            q:=head[v];
            while q<>0 do
            begin
                if (q<=m2)and(dist[v]=dist[e[q].node]+e[q].w) then
                begin
                    inc(cnt);
                    break;
                end;
                q:=e[q].next;
            end;
            vis[v]:=true;
        end;
        p:=e[p].next;
    end;
    writeln(cnt);
end.