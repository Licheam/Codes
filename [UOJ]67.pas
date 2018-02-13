const maxn=100000;
    maxm=100000;
type edge=record
    node:longint;
    next:longint;
    end;
var n,m,i,f,g,tot,dfn_i,cnt:longint;
    dfn,low,head:array[1..maxn]of longint;//dfn时间戳，low最早的circle时间戳
    e:array[1..2*maxm]of edge;
    cv,flag:array[1..maxn]of boolean;

procedure add(x,y:longint);
begin
    inc(tot);
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;

procedure tarjan(x,y:longint);//cut-vertex
var p,u,dgr:longint;
begin
    inc(dfn_i);
    dfn[x]:=dfn_i;
    low[x]:=dfn_i;
    p:=head[x];
    dgr:=0;
    while p<>0 do
    begin
        inc(dgr);
        u:=e[p].node;
        if u<>y then
        begin
            if dfn[u]=0 then
            begin
                tarjan(u,x);
                if dfn[x]<=low[u] then
                    cv[x]:=true;
            end;
            if low[u]<low[x] then //back
                low[x]:=low[u];
        end;
        p:=e[p].next;
    end;
    if dgr=m-n+2 then
    begin
        flag[x]:=true;
        if not(cv[x]) then
            inc(cnt);
    end;
end;

procedure getcv(x:longint);
var p,u,dgr,son:longint;
begin
    dfn_i:=1;
    dfn[x]:=1;
    low[x]:=1;
    p:=head[x];
    dgr:=0;
    son:=0;
    while p<>0 do
    begin
        inc(dgr);
        u:=e[p].node;
        if dfn[u]=0 then
        begin
            tarjan(u,x);
            inc(son);
        end;
        p:=e[p].next;
    end;
    if dgr=m-n+2 then
        flag[x]:=true;
    //writeln('son:',son);
    if son>1 then
        cv[x]:=true
    else if flag[x] then
        inc(cnt);
end;

begin
    readln(n,m);
    filldword(head,n,0);
    tot:=0;
    for i:=1 to m do
    begin
        readln(f,g);
        add(f,g);
        add(g,f);
    end;
    cnt:=0;
    fillchar(cv,n,false);
    fillchar(flag,n,false);//度=m-n+2
    filldword(dfn,n,0);
    for i:=1 to n do
        if dfn[i]=0 then
            getcv(i);
    writeln(cnt);
    for i:=1 to n do
        if (flag[i])and(not cv[i]) then
            write(i,' ');
end.