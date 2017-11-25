const maxn=10000;
    maxm=100000;

type edge=record
    node:longint;
    next:longint;
    end;

var n,m,i,tot,f,g,cnt1,cnt2,ans:longint;
    e:array[1..2*maxm]of edge;
    head,color:array[1..maxn]of longint;

function min(x,y:longint):longint;
begin
    if x>y then exit(y)
    else exit(x);
end;

procedure add(x,y:longint);
begin
    inc(tot);
    e[tot].node:=y;
    e[tot].next:=head[x];
    head[x]:=tot;
end;

function dye(x:longint):boolean;
var q,col:longint;
begin
    q:=head[x];
    if color[x]=1 then col:=2
    else col:=1;
    while q<>0 do
    begin
        if color[e[q].node]=0 then
        begin
            color[e[q].node]:=col;
            if col=1 then
            inc(cnt1)
            else inc(cnt2);
            if not(dye(e[q].node)) then
            exit(false);
        end
        else if color[e[q].node]<>col then
        exit(false);
        q:=e[q].next;
    end;
    exit(true);
end;

begin
    readln(n,m);
    filldword(head,n,0);
    for i:=1 to m do
    begin
        readln(f,g);
        add(f,g);
        add(g,f);
    end;
    filldword(color,n,0);
    ans:=0;
    for i:=1 to n do
        if color[i]=0 then
        begin
            cnt1:=1;
            cnt2:=0;
            color[i]:=1;
            if not(dye(i)) then
            begin
                writeln('Impossible');
                halt;
            end;
            inc(ans,min(cnt1,cnt2));
        end;
    writeln(ans);
end.