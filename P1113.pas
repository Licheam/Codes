const maxn=10000;
var n,i,se,q,max,ans:longint;
    dp:array[1..maxn]of longint;
begin
    readln(n);
    filldword(dp,n,0);
    ans:=0;
    for i:=1 to n do
    begin
        read(se);read(dp[i]);read(q);
        max:=0;
        while q<>0 do
        begin
            if max<dp[q] then max:=dp[q];
            read(q);
        end;
        inc(dp[i],max);
        if ans<dp[i] then
            ans:=dp[i];
    end;
    writeln(ans);
end.