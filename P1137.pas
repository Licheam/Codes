const maxn=100000;
    maxm=200000;
type edge=record
    next:longint;
    node:longint;
    end;
var n,m,tot,i,u,v,q,cnt,top:longint;
    head,indgr,list,stack,dp:array[1..maxn]of longint;
    flag:array[1..maxn]of boolean;
    e:array[1..maxm]of edge;

procedure add(x,y:longint);
begin
    inc(tot);
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;

begin
    readln(n,m);
    filldword(head,n,0);
    filldword(indgr,n,0);//入度
    tot:=0;
    for i:=1 to m do
    begin
        readln(u,v);
        add(v,u);
        inc(indgr[u]);
    end;
    cnt:=0;
    top:=0;
    fillchar(flag,n,false);
    for i:=1 to n do
    begin
        if (flag[i])or(indgr[i]<>0) then continue;
        inc(top);
        stack[top]:=i;
        while p<>0 do
        begin
            u:=stack[top];
            inc(cnt);
            list[cnt]:=u;
            dec(top);
            flag[u]:=true;
            q:=head[u];
            while q<>0 do
            begin
                dec(indgr[e[q].node]);
                if indgr[e[q].node]=0 then
                begin
                    inc(top);
                    stack[top]:=e[q].node;
                end;
                q:=e[q].next;
            end;
        end;
    end;
    //if cnt<>n then writeln('ERROR');
    for i:=cnt downto 1 do
    begin
        //write(list[i],' ');
        dp[list[i]]:=1;
        q:=head[list[i]];
        while q<>0 do
        begin
            if dp[list[i]]<dp[e[q].node]+1 then
            dp[list[i]]:=dp[e[q].node]+1;
            q:=e[q].next;
        end;
    end;
    //writeln;
    for i:=1 to n do
    writeln(dp[i]);
end.