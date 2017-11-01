//luoguP2201
const maxn=1000000;
type
    node=^link;
    link=record
    data:longint;
    sum:longint;
    max:longint;
    prev:node;
    next:node;
    end;
    
var n,i,t,cnt:longint;
    head,cur:node;
    a:array[1..maxn]of node;
    c:char;

function getmax(x,y:longint):longint;
begin
    if x>y then exit(x)
    else exit(y);
end;
    
procedure ini();
var p:node;
begin
    cnt:=0;
    new(p);
    p^.next:=p;
    p^.prev:=p;
    p^.sum:=0;
    p^.data:=0;
    p^.max:=-1000;
    head:=p;
    cur:=head;
end;

{function search(x:longint):node;
var p:node;
begin
    p:=head;
    while p^.next<>head do
    begin
        p:=p^.next;
        if p^.data=x then exit(p);
    end;
    exit(head);
end;}

procedure insert(x:longint);//insert x to y's left/right
var p:node;
begin
    inc(cnt);
    new(p);
    p^.data:=x;
    p^.next:=cur;
    p^.prev:=cur^.prev;
    cur^.prev^.next:=p;
    cur^.prev:=p;
    p^.sum:=p^.prev^.sum+x;
    p^.max:=getmax(p^.prev^.max,p^.sum);
    a[cnt]:=p;
end;

procedure delete();
var p:node;
begin
    dec(cnt);
    p:=cur^.prev;
    if p=head then exit;
    p^.prev^.next:=p^.next;
    p^.next^.prev:=p^.prev;
    dispose(p);
    readln;
end;

procedure move(b:boolean);
begin
    if (b)and(cur^.prev<>head) then
    begin
        cur:=cur^.prev;
        dec(cnt);
    end
    else if (not(b))and(cur<>head) then
    begin
        inc(cnt);
        cur^.sum:=cur^.prev^.sum+cur^.data;
        a[cnt]:=cur;
        cur^.max:=getmax(cur^.prev^.max,cur^.sum);
        cur:=cur^.next;
    end;
    readln;
end;

begin
    readln(n);
    ini;
    for i:=1 to n do
    begin
        read(c);
        if c='I' then
        begin
            readln(t);
            insert(t);
        end
        else if c='D' then delete
        else if c='Q' then
        begin
            readln(t);
            writeln(a[t]^.max);
        end
        else move(c='L');
    end;
end.