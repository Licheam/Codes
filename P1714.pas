const maxn=500000;
var n,m,i,l,r:longint;
    max:Int64;
    sum,q:array[0..maxn]of Int64;

begin
    readln(n,m);
    sum[0]:=0;
    l:=0;r:=0;q[0]:=0;
    max:=0;
    for i:=1 to n do
    begin
        read(sum[i]);
        inc(sum[i],sum[i-1]);
        while (l<=r)and(q[l]<i-m) do inc(l);
        while (l<=r)and(sum[q[r]]>sum[i]) do dec(r);
        inc(r);q[r]:=i;
        if max<sum[i]-sum[q[l]] then max:=sum[i]-sum[q[l]];
    end;
    writeln(max);
end.