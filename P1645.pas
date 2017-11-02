const maxn=1000;
var n,i,j,cnt:longint;
    l,r,c:array[1..maxn]of longint;
    a:array[1..maxn]of boolean;

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
    k:=r[(left+right)shr 1];
    repeat
        while r[x]<k do inc(x);
        while r[y]>k do dec(y);
        if x<=y then
        begin
            swap(r[x],r[y]);
            swap(l[x],l[y]);
            swap(c[x],c[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if left<y then qs(left,y);
    if right>x then qs(x,right);
end;

begin
    readln(n);
    fillchar(a,sizeof(a),false);
    for i:=1 to n do
    readln(l[i],r[i],c[i]);
    qs(1,n);
    for i:=1 to n do
    begin
        cnt:=c[i];
        for j:=l[i] to r[i] do
        if a[j] then dec(cnt);
        for j:=r[i] downto l[i] do
        begin
            if cnt<=0 then break
            else if not(a[j]) then
            begin
                a[j]:=true;
                dec(cnt);
            end;
        end;
    end;
    cnt:=0;
    for i:=1 to 1000 do
    if a[i] then inc(cnt);
    writeln(cnt);
end.