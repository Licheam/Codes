const maxn=100000;
    maxm=200000;
type edge=record
    next:longint;
    node:longint;
    end;

var n,m,i,tot,f,g,cnt,top:longint;
    head,indgr,list,stack,vis:array[1..maxn]of longint;
    e:array[1..maxm]of edge;
    flag:array[1..maxn]of boolean;

procedure add(x,y:longint);
begin
    inc(tot);
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;

procedure khan();
var i,p,u,v:longint;
begin
    cnt:=0;
    top:=0;
    fillchar(flag,n,false);
    for i:=1 to n do
    begin
        if (flag[i])or(indgr[i]<>0) then continue;
        inc(top);
        stack[top]:=i;
        flag[i]:=true;
        while top>0 do
        begin
            u:=stack[top];
            inc(cnt);
            list[cnt]:=u;
            flag[u]:=true;
            dec(top);
            p:=head[u];
            while p<>0 do
            begin
                v:=e[p].node;
                dec(indgr[v]);
                if indgr[v]=0 then
                begin
                    inc(top);
                    stack[top]:=v;
                end;
                p:=e[p].next;
            end;
        end;
    end;
end;

procedure dp();
var i,p,u,v:longint;
begin
    filldword(vis,n,1);
    for i:=1 to n do
    begin
        u:=list[i];
        p:=head[u];
        while p<>0 do
        begin
            v:=e[p].node;
            if vis[v]<vis[u]+1 then
                vis[v]:=vis[u]+1;
            p:=e[p].next;
        end;
    end;
end;

begin
    readln(n,m);
    filldword(head,n,0);
    filldword(indgr,n,0);
    tot:=0;
    for i:=1 to m do
    begin
        readln(f,g);
        add(f,g);
        inc(indgr[g])
    end;
    khan;
    dp;
    for i:=1 to n do
        writeln(vis[i]);
end.