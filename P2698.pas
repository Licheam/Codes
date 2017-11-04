const maxn=100000;
var n,d,i,l,r,mid:longint;
    nx,ny:array[1..maxn]of longint;

procedure swap(var x,y:longint);
var t:longint;
begin   
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(left,right:longint);//ascend
var x,y,k:longint;
begin
    x:=left;y:=right;
    k:=nx[(left+right)shr 1];
    repeat
        while nx[x]<k do inc(x);
        while nx[y]>k do dec(y);
        if x<=y then
        begin
            swap(nx[x],nx[y]);
            swap(ny[x],ny[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if left<y then qs(left,y);
    if right>x then qs(x,right);
end;

function check(x:longint):boolean;
var l1,l2,r1,r2,k:longint;//1:max,2:min
    q1,q2:array[1..maxn]of longint;
begin
    //writeln('checking ',x);
    check:=false;
    l1:=1;l2:=1;r1:=0;r2:=0;
    for k:=1 to n do
    begin
        while (l1<=r1)and(nx[q1[l1]]+x<nx[k]) do inc(l1);
        while (l2<=r2)and(nx[q2[l2]]+x<nx[k]) do inc(l2);
        while (l1<=r1)and(ny[q1[r1]]>ny[k]) do dec(r1);//ascend
        while (l2<=r2)and(ny[q2[r2]]<ny[k]) do dec(r2);//descend
        inc(r1);inc(r2);
        q1[r1]:=k;q2[r2]:=k;
        if ny[q2[l2]]-ny[q1[l1]]>=d then exit(true);
    end;
end;

begin
    readln(n,d);
    for i:=1 to n do
    readln(nx[i],ny[i]);
    qs(1,n);
    //for i:=1 to n do
    //writeln(nx[i],' ',ny[i]);
    l:=0;r:=nx[n];
    while l<r do
    begin
        mid:=(l+r)div 2;
        //writeln(l,' ',r);
        if check(mid) then r:=mid
        else l:=mid+1;
    end;
    if check(l) then writeln(l)
    else writeln(-1);
end.