const maxn=1000;
    maxm=100000;

var n,m,i,ans:longint;
    fa,cnt:array[1..maxn]of longint;
    time,a,b:array[1..maxm]of longint;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:longint);
var x,y,mid:longint;
begin
    x:=l;y:=r;
    mid:=time[(l+r)shr 1];
    repeat
        while time[x]<mid do inc(x);
        while time[y]>mid do dec(y);
        if x<=y then
        begin
            swap(a[x],a[y]);
            swap(b[x],b[y]);
            swap(time[x],time[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;

function find(x:longint):longint;
begin
    if fa[x]=x then exit(x);
    fa[x]:=find(fa[x]);
    exit(fa[x]);
end;

procedure union(x,y:longint);
var rx,ry:longint;
begin
    rx:=find(x);ry:=find(y);
    if rx=ry then exit;
    if cnt[rx]<cnt[ry] then
    begin
        fa[rx]:=ry;
        inc(cnt[ry],cnt[rx]);
    end
    else
    begin
        fa[ry]:=rx;
        inc(cnt[rx],cnt[ry]);
    end;
end;

begin
    readln(n,m);
    for i:=1 to n do
    fa[i]:=i;
    filldword(cnt,n,1);
    for i:=1 to m do
    readln(a[i],b[i],time[i]);
    qs(1,m);
    ans:=-1;
    //writeln('------');
    for i:=1 to m do
    begin
        union(a[i],b[i]);
        //writeln(a[i],' ',b[i],' ',time[i]);
        if cnt[find(a[i])]=n then
        begin
            ans:=time[i];
            break;
        end;
    end;
    writeln(ans);
end.