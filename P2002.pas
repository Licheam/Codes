const maxn=100000;
    maxm=500000;
type edge=record
    node:longint;
    next:longint;
    end;
var n,m,i,tot,dfn_i,scc_i,top,cnt:longint;
    dfn,low,scc,head,stack:array[1..maxn]of longint;//dfn时间戳，low最早的circle时间戳
    f,g:array[1..maxm]of longint;
    e:array[1..maxm]of edge;
    instack,flag:array[1..maxn]of boolean;

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
            scc[v]:=scc_i;
            instack[v]:=false;
            dec(top);
        end;
    end;
end;

begin
    readln(n,m);
    filldword(head,n,0);
    tot:=0;
    for i:=1 to m do
    begin
        readln(f[i],g[i]);
        add(f[i],g[i]);
    end;
    fillchar(instack,n,false);
    filldword(dfn,n,0);
    dfn_i:=0;
    scc_i:=0;
    top:=0;
    for i:=1 to n do
        if dfn[i]=0 then
            tarjan(i);
    tot:=0;
    fillchar(flag,scc_i,true);
    cnt:=scc_i;
    for i:=1 to m do
        if (scc[f[i]]<>scc[g[i]])and(flag[scc[g[i]]]) then
        begin
            flag[scc[g[i]]]:=false;
            dec(cnt);
        end;
    writeln(cnt);
end.