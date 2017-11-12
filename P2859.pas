const maxn=50000;
var n,i,len,cnt,em:longint;
    le,ri,lm,rm,st,cow:array[1..maxn]of longint;

procedure swap(var x,y:longint);//swap number
var t:longint;
begin   
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:longint);//ascend quicksort
var x,y,k:longint;
begin
    x:=l;y:=r;
    k:=le[(l+r)shr 1];
    repeat
        while le[x]<k do inc(x);
        while le[y]>k do dec(y);
        if x<=y then
        begin
            swap(le[x],le[y]);
            swap(lm[x],lm[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;
//小根堆
procedure down(x:longint);
var t:longint;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(ri[t]>ri[t+1]) then inc(t);
    if ri[t]<ri[x] then
    begin
        swap(ri[x],ri[t]);
        swap(rm[x],rm[t]);
        down(t);
    end;
end;

procedure delete(x:longint);
begin
    ri[x]:=ri[len];
    rm[x]:=rm[len];
    dec(len);
    down(x);
end;
//小根堆
//BIT for stalls
function lowbit(x:longint):longint;
begin
    exit(x and (-x));
end;

procedure change(x,y:longint);
begin
    while x<=cnt do
    begin
        inc(st[x],y);
        inc(x,lowbit(x));
    end;
end;

function sum(x:longint):longint;
begin
    sum:=0;
    while x>0 do
    begin
        inc(sum,st[x]);
        dec(x,lowbit(x));
    end;
end;
//BIT for stalls
//Binary Search for the empty stall
function check(l,r:longint):longint;
var mid:longint;
begin
    while l<r do
    begin
        mid:=(l+r)shr 1;
        if sum(mid)=mid then l:=mid+1
        else r:=mid;
    end;
    exit(r);
end;

//main
begin
    readln(n);
    for i:=1 to n do
    begin
        readln(le[i],ri[i]);
        lm[i]:=i;
        rm[i]:=i;
    end;
    qs(1,n);//左端点排序
    len:=n;//len for heap
    for i:=n shr 1 downto 1 do//右端点入堆
    down(i);
    cnt:=0;//cnt for BIT
    for i:=1 to n do
    begin
        while ri[1]<le[i] do//need to empty stall first
        begin
            change(cow[rm[1]],-1);//empty stall
            delete(1);
        end;
        if sum(cnt)=cnt then
        begin
            inc(cnt);
            st[cnt]:=sum(cnt-1)-sum(cnt-lowbit(cnt))+1;
            cow[lm[i]]:=cnt;
        end//stall is full
        else
        begin
            em:=check(1,cnt);//find the smallest empty stall;
            cow[lm[i]]:=em;
            change(em,1);//fill the empty stall;
        end;
    end;
    writeln(cnt);
    for i:=1 to n do
    writeln(cow[i]);
end.