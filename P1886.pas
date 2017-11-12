const maxn=1000000;
var n,k,i,l,r:longint;
    a,q:array[1..maxn]of longint;

begin
    readln(n,k);
    l:=1;r:=0;
    for i:=1 to n do//min,ascend
    begin
        read(a[i]);
        while (l<=r)and(a[i]<a[q[r]])do dec(r);
        while (l<=r)and(i-q[l]>k-1)do inc(l);
        inc(r);
        q[r]:=i;
        if i>=k then write(a[q[l]],' ');
    end;
    writeln;
    l:=1;r:=0;
    for i:=1 to n do//max,descend
    begin
        while (l<=r)and(a[i]>a[q[r]])do dec(r);
        while (l<=r)and(i-q[l]>k-1)do inc(l);
        inc(r);
        q[r]:=i;
        if i>=k then write(a[q[l]],' ');
    end;
end.