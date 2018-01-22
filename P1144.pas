const maxn=1000000;
    maxm=2000000;
    pri=100003;
type edge=record
    node:longint;//to
    next:longint;
    end;

var n,m,i,tot,f,g,l,r,p:longint;
    e:array[1..maxm]of edge;
    head,ans,v,que:array[1..maxn]of longint;
    flag:array[1..maxn]of boolean;

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
    tot:=0;
    for i:=1 to m do//input
    begin
        readln(f,g);
        if f<>g then
        begin
            add(f,g);
            add(g,f);
        end;
    end;
    fillchar(flag,n,false);
    filldword(v,n,n);
    filldword(ans,n,0);
    ans[1]:=1;
    v[1]:=0;
    l:=1;r:=1;
    que[l]:=1;
    while l-r<>1 do
    begin
        p:=head[que[l]];
        while p<>0 do
        begin
            if v[e[p].node]=n then
            begin
                v[e[p].node]:=v[que[l]]+1;
                ans[e[p].node]:=ans[que[l]];
                if not(flag[e[p].node]) then
                begin
                    if r=maxm then r:=1
                    else inc(r);
                    que[r]:=e[p].node;
                    flag[e[p].node]:=true;
                end;
            end
            else if v[e[p].node]=v[que[l]]+1 then
            begin
                ans[e[p].node]:=(ans[e[p].node]+ans[que[l]])mod pri;
                if not(flag[e[p].node]) then
                begin
                    if r=maxm then r:=1
                    else inc(r);
                    que[r]:=e[p].node;
                    flag[e[p].node]:=true;
                end;
            end;
            p:=e[p].next;
        end;
        inc(l);
    end;
    for i:=1 to n do
    writeln(ans[i]);
end.