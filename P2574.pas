const maxn=200000;
    maxt=524289;
type
    node=record
    left:longint;
    right:longint;
    cnt:longint;
    delta:boolean;
    end;
var n,m,i,c,le,ri:longint;
    s:ansistring;
    a:array[1..maxt]of node;

procedure update(cur:longint);
var left,right:longint;
begin
    left:=cur shl 1;
    right:=left+1;
    a[left].cnt:=(a[left].right-a[left].left)-a[left].cnt;
    a[right].cnt:=(a[right].right-a[right].left)-a[right].cnt;
    a[left].delta:=not(a[left].delta);
    a[right].delta:=not(a[right].delta);
    a[cur].delta:=false;
end;

procedure change(cur,l,r:longint);
var left,right,mid:longint;
begin
    if (l<=a[cur].left)and(a[cur].right<=r) then
    begin
        a[cur].cnt:=(a[cur].right-a[cur].left)-a[cur].cnt;
        a[cur].delta:=not(a[cur].delta);
    end
    else
    begin
        left:=cur shl 1;
        right:=left+1;
        mid:=(a[cur].left+a[cur].right)shr 1;
        if a[cur].delta then
        update(cur);
        if l<mid then
        change(left,l,r);
        if r>mid then
        change(right,l,r);
        a[cur].cnt:=a[left].cnt+a[right].cnt;
    end;
end;

function query(cur,l,r:longint):longint;
var left,right,mid:longint;
begin
    if (l<=a[cur].left)and(a[cur].right<=r) then
    query:=a[cur].cnt
    else
    begin
        left:=cur shl 1;
        right:=left+1;
        mid:=(a[cur].left+a[cur].right)shr 1;
        if a[cur].delta then
        update(cur);
        query:=0;
        if l<mid then
        query:=query+query(left,l,r);
        if r>mid then
        query:=query+query(right,l,r);
    end;
end;

procedure built(cur,l,r:longint);
var left,right,mid:longint;
begin
    a[cur].left:=l;
    a[cur].right:=r;
    a[cur].delta:=false;
    if l+1<r then
    begin
        left:=cur shl 1;
        right:=left+1;
        mid:=(l+r)shr 1;
        built(left,l,mid);
        built(right,mid,r);
        a[cur].cnt:=a[left].cnt+a[right].cnt;
    end
    else if s[l]='1' then
    a[cur].cnt:=1
    else a[cur].cnt:=0;
end;

begin
    readln(n,m);
    readln(s);
    built(1,1,n+1);
    for i:=1 to m do
    begin
        readln(c,le,ri);
        if c=0 then
        change(1,le,ri+1)
        else
        writeln(query(1,le,ri+1));
    end;
end.