const maxn=1000;
var n,m,stn,i,j,k,l,max,p,u,cnt:longint;
    e:array[1..maxn,1..maxn]of boolean;
    list,stack,indgr,pre,dp:array[1..maxn]of longint;
    flag:array[1..maxn]of boolean;

begin
    readln(n,m);
    for i:=1 to n do
    for j:=1 to n do
    e[i,j]:=false;
    filldword(indgr,n,0);
    for i:=1 to m do
    begin
        read(stn);//stations
        for j:=1 to stn do
        read(pre[j]);
        p:=2;
            for k:=pre[1]+1 to pre[stn]-1 do
            begin
                if k=pre[p] then
                begin
                    inc(p);
                    continue;
                end;
                for l:=1 to stn do
                    if not e[pre[l],k] then
                    begin
                        e[pre[l],k]:=true;
                        //write(pre[l],'>',k,' ');
                        inc(indgr[k]);
                    end;
            end;
        //writeln;
    end;
    p:=0;
    cnt:=0;
    fillchar(flag,n,false);
    for i:=1 to n do
    begin
        if (flag[i])or(indgr[i]<>0) then continue;
        inc(p);
        stack[p]:=i;
        while p>0 do
        begin
            u:=stack[p];
            inc(cnt);
            list[cnt]:=u;
            dec(p);
            flag[u]:=true;
            for j:=1 to n do
                if e[u,j] then
                begin
                    dec(indgr[j]);
                    if indgr[j]=0 then
                    begin
                        inc(p);
                        stack[p]:=j;
                    end;
                end;
        end;
    end;
    filldword(dp,n,1);
    max:=1;
    for i:=1 to n do
    begin
        if dp[list[i]]>max then
        max:=dp[list[i]];
        for j:=1 to n do
        begin
            if (e[list[i],list[j]])and(dp[list[j]]<dp[list[i]]+1) then
            dp[list[j]]:=dp[list[i]]+1;
        end;
    end;
    {for i:=1 to n do
    write(list[i],' ');
    writeln;
    for i:=1 to n do
    write(dp[list[i]],' ');
    writeln;}
    writeln(max);
end.