const maxn=10000;
    maxm=100000;
type edge=record
    node:longint;
    next:longint;
    end;
var n,m,i,f,g,tot,dfn_i,scc_i,top:longint;
    dfn,low,head,stack:array[1..maxn]of longint;//dfn时间戳，low最早的circle时间戳
    e:array[1..maxm]of edge;
    instack:array[1..maxn]of boolean;

procedure add(x,y:longint);
begin
    inc(tot);
    e[tot].next:=head[x];
    e[tot].node:=y;
    head[x]:=tot;
end;

procedure tarjan(x:longint);//scc
var p,v:longint;
begin
    inc(dfn_i);
    dfn[x]:=dfn_i;
    low[x]:=dfn_i;
    instack[x]:=true;
    inc(top);
    stack[top]:=x;
    p:=head[x];
    while p<>0 do
    begin
        v:=e[p].node;
        if dfn[v]=0 then
        begin
            tarjan(v);
            if low[v]<low[x] then
                low[x]:=low[v];
        end
        else if (instack[v])and(dfn[v]<low[x]) then //cross or back
            low[x]:=dfn[v];
        p:=e[p].next;
    end;
    if low[x]=dfn[x] then
    begin
        inc(scc_i);
        v:=0;
        while v<>x do
        begin
            v:=stack[top];
            //scc[v]:=scc_i;
            instack[v]:=false;
            dec(top);
        end;
    end;
end;

begin
    readln(n,m);
    while (n<>0)or(m<>0) do
    begin
        filldword(head,n,0);
        tot:=0;
        for i:=1 to m do
        begin
            readln(f,g);
            add(f,g);
        end;
        fillchar(instack,n,false);
        filldword(dfn,n,0);
        dfn_i:=0;
        scc_i:=0;
        top:=0;
        for i:=1 to n do
            if dfn[i]=0 then
                tarjan(i);
        if scc_i=1 then
            writeln('Yes')
        else writeln('No');
        readln(n,m);
    end;
end.