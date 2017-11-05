const maxm=30000;
var n,i,x1,x2,p:longint;
    c:string;
    fa,sum,dis:array[1..maxm]of longint;

function find(x:longint):longint;
var root:longint;
begin
    if x=fa[x] then exit(x);
    root:=find(fa[x]);
    inc(dis[x],dis[fa[x]]);
    fa[x]:=root;
    exit(root);
end;

procedure union(x,y:longint);
var rx,ry:longint;
begin
    rx:=find(x);
    ry:=find(y);
    fa[ry]:=rx;
    dis[ry]:=sum[rx];
    inc(sum[rx],sum[ry]);
end;

begin
    readln(n);
    for i:=1 to maxm do
    begin
        fa[i]:=i;
        sum[i]:=1;
        dis[i]:=0;
    end;
    for i:=1 to n do 
    begin
        readln(c);
        if c[1]='M' then
        begin
            delete(c,1,2);
            p:=pos(' ',c);
            val(copy(c,1,p-1),x1);
            val(copy(c,p+1,length(c)),x2);
            union(x1,x2);
        end
        else
        begin
            val(copy(c,3,length(c)),x1);
            p:=find(x1);
            //writeln('sum=',sum[p]);
            //writeln('dis[',x1,']=',dis[x1]);
            //write('ans=');
            writeln(sum[p]-dis[x1]-1);
        end;
    end;
end.