const maxn=100000;
var n,k,i,max,l,r,mid,cnt,t:longint;
    c:array[0..maxn]of char;
begin
    readln(n,k);
    max:=1;
    cnt:=0;
    c[0]:='0';
    for i:=1 to n do//NNNNFFFNNNFFFNNFFF
    begin
        read(c[i]);
        if c[i]<>c[i-1] then
        begin
            if cnt>max then max:=cnt;
            cnt:=1;
        end
        else inc(cnt);
    end;
    if cnt>max then max:=cnt;
    l:=1;r:=max;
    while l<r do
    begin
        mid:=(l+r)div 2;
        cnt:=0;
        t:=k;
        if mid<>1 then
        for i:=1 to n do//NNFN
        begin
            if c[i]<>c[i-1] then cnt:=1
            else if cnt=mid then
            begin
                dec(t);
                if t<0 then break;
                if (i<>n)and(c[i]=c[i+1]) then
                cnt:=0
                else
                cnt:=1;
            end
            else inc(cnt);
        end
        else
        begin
            cnt:=k;//odd=N
            t:=k;//odd=F
            for i:=1 to n do
            begin
                if i mod 2=1 then//odd
                begin
                    if c[i]='N' then dec(cnt)
                    else dec(t);
                end
                else
                begin
                    if c[i]='N' then dec(t)
                    else dec(cnt);
                end;
                if (t<0)and(cnt<0) then
                begin
                    l:=2;
                    break;
                end;
            end;
            break;
        end;
        if t<0 then l:=mid+1
        else r:=mid;
    end;
    writeln(l);
end.