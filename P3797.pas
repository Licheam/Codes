const maxn=200000;
    maxt=524289;
type
    node=record
    left:longint;
    right:longint;
    cnt:longint;
    lnx:shortint;//0'X',1'(',2')'
    rnx:shortint;
    pl:longint;
    pr:longint;
    end;

var n,m,i,le,ri,p:longint;
    c:string;
    a:array[1..maxt]of node;

function tran(x:char):shortint;
begin
    if x='X' then exit(0)
    else if x='(' then exit(1)
    else exit(2);
end;

procedure built(cur,l,r:longint);
var left,right,mid:longint;
begin
    a[cur].left:=l;
    a[cur].right:=r;
    a[cur].cnt:=0;
    if l+1<r then
    begin
        left:=cur shl 1;
        right:=left+1;
        mid:=(a[cur].left+a[cur].right)shr 1;
        built(left,l,mid);
        built(right,mid,r);
        if a[right].rnx=0 then
        a[cur].rnx:=a[left].rnx
        else
        a[cur].rnx:=a[right].rnx;
        if a[left].lnx=0 then
        a[cur].lnx:=a[right].lnx
        else
        a[cur].lnx:=a[left].lnx;
        if a[cur].lnx=0 then a[cur].pl:=0
        else if a[cur].lnx=1 then a[cur].pl:=1
        else a[cur].pl:=n;
        if a[cur].rnx=0 then a[cur].pr:=0
        else if a[cur].rnx=1 then a[cur].pr:=1
        else a[cur].pr:=n;
    end
    else
    with a[cur] do
    begin
        if l=1 then
        begin
            lnx:=1;
            rnx:=1;
            pl:=1;
            pr:=1;
        end
        else if l=n then
        begin
            lnx:=2;
            rnx:=2;
            pl:=n;
            pr:=n;
        end
        else
        begin
            lnx:=0;
            rnx:=0;
            pl:=0;
            pr:=0;//
        end;
        
    end;
end;

procedure change(cur,l,k:longint);
var left,right,mid:longint;
begin
    if (a[cur].left=l)and(a[cur].right=l+1) then
    with a[cur] do
    begin
        lnx:=k;
        rnx:=k;
        if k=0 then
        begin
            pl:=0;
            pr:=0;
        end
        else
        begin
            pl:=l;
            pr:=l;
        end;
    end
    else
    begin
        left:=cur shl 1;
        right:=left+1;
        mid:=(a[cur].left+a[cur].right)shr 1;
        if l<mid then
        change(left,l,k)
        else change(right,l,k);
        a[cur].cnt:=a[left].cnt+a[right].cnt;
        if (a[left].rnx=1)and(a[right].lnx=2) then
        inc(a[cur].cnt);
        if a[right].rnx=0 then
        begin
            a[cur].rnx:=a[left].rnx;
            a[cur].pr:=a[left].pr;
        end
        else
        begin
            a[cur].rnx:=a[right].rnx;
            a[cur].pr:=a[right].pr;
        end;
        if a[left].lnx=0 then
        begin
            a[cur].lnx:=a[right].lnx;
            a[cur].pl:=a[right].pl;
        end
        else
        begin
            a[cur].lnx:=a[left].lnx;
            a[cur].pl:=a[left].pl;
        end;
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
        if (l<mid)and(r>mid)and(a[left].rnx=1)and(a[left].pr>=l)and(a[right].lnx=2)and(a[right].pl<r) then
        query:=1
        else query:=0;
        if l<mid then
        query:=query+query(left,l,r);
        if r>mid then
        query:=query+query(right,l,r);
    end;
    //writeln('query:',a[cur].left,' ',a[cur].right,':',query);
end;

begin
    readln(n,m);
    built(1,1,n+1);
    a[1].cnt:=1;
    {for i:=1 to 8 do
    with a[i] do
    begin
        writeln('l:',left,' r:',right);
        writeln('lnx:',lnx);
        writeln('rnx:',rnx);
        writeln('pl:',pl);
        writeln('pr:',pr);
    end;}
    for i:=1 to m do
    begin
        readln(c);
        if c[1]='2' then 
        begin
            delete(c,1,2);
            p:=pos(' ',c);
            val(copy(c,1,p-1),le);
            val(copy(c,p+1,length(c)-p),ri);
            writeln(query(1,le,ri+1));
        end
        else
        begin
            delete(c,1,2);
            p:=pos(' ',c);
            val(copy(c,1,p-1),le);
            change(1,le,tran(c[p+1]));
        end;
    end;
end.