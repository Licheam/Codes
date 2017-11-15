const maxt=262145;
type
    node=record
    left:longint;
    right:longint;
    color:longint;
    delta:boolean;
    end;

var n,tot,m,i,le,ri,col:longint;
    c:char;
    a:array[1..maxt]of node;

function lowbit(x:longint):longint;
begin
    exit(x and (-x));
end;

function count(x:longint):longint;
begin
    count:=0;
    while x<>0 do
    begin
        inc(count);
        dec(x,lowbit(x));
    end;
end;

procedure update(cur:longint);
var left,right:longint;
begin
    left:=cur shl 1;
    right:=left+1;
    a[left].color:=a[cur].color;
    a[right].color:=a[cur].color;
    a[left].delta:=true;
    a[right].delta:=true;
    a[cur].delta:=false;
end;

procedure change(cur,l,r,delta:longint);
var left,right,mid:longint;
begin
    if (l<=a[cur].left)and(a[cur].right<=r) then
    begin
        a[cur].color:=1 shl (delta-1);
        a[cur].delta:=true;
    end
    else
    begin
        left:=cur shl 1;
        right:=left+1;
        mid:=(a[cur].left+a[cur].right)shr 1;
        if a[cur].delta then
        update(cur);
        if l<mid then
        change(left,l,r,delta);
        if r>mid then
        change(right,l,r,delta);
        a[cur].color:=a[left].color or a[right].color;
    end;
end;

function query(cur,l,r:longint):longint;
var left,right,mid:longint;
begin
    if ((l<=a[cur].left)and(a[cur].right<=r))or(a[cur].delta) then
    exit(a[cur].color)
    else
    begin
        left:=cur shl 1;
        right:=left+1;
        mid:=(a[cur].left+a[cur].right)shr 1;
        query:=0;
        if l<mid then
        query:=query or query(left,l,r);
        if r>mid then
        query:=query or query(right,l,r);
    end;
end;

procedure built(cur,l,r:longint);
var left,right,mid:longint;
begin
    a[cur].left:=l;
    a[cur].right:=r;
    a[cur].color:=1;
    a[cur].delta:=false;
    if l+1<r then
    begin
        left:=cur shl 1;
        right:=left+1;
        mid:=(l+r)shr 1;
        built(left,l,mid);
        built(right,mid,r);
    end;
end;

begin
    readln(n,tot,m);
    built(1,1,n+1);
    for i:=1 to m do
    begin
        read(c);
        if c='C' then
        begin
            readln(le,ri,col);
            if le<=ri then
            change(1,le,ri+1,col)
            else
            change(1,ri,le+1,col);
        end
        else
        begin
            readln(le,ri);
            if le>ri then
            writeln(count(query(1,ri,le+1)))
            else
            writeln(count(query(1,le,ri+1)));
        end;
    end;
end.