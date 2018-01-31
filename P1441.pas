const maxn=20;
    maxa=2000;
var n,m,i,max,cnt,maxw,tot:longint;
    a:array[1..maxn]of longint;
    flag:array[1..maxn]of boolean;
    map:array[0..maxa]of boolean;

procedure cal();
var i,j:longint;
begin
    fillchar(map,maxw,false);
    map[0]:=true;
    cnt:=0;tot:=0;
    for i:=1 to n do
        if not(flag[i]) then
        begin
            for j:=tot downto 0 do
                if(map[j])and(not map[j+a[i]])then
                begin
                    map[j+a[i]]:=true;
                    inc(cnt);
                end;
            inc(tot,a[i]);
        end;
    if cnt>max then
        max:=cnt;
end;

procedure dfs(dep,last:longint);
var i:longint;
begin
    if dep>m then
    begin
        cal;
        exit;
    end;
    for i:=last+1 to n-m+dep do
        if not(flag[i]) then
        begin
            flag[i]:=true;
            dfs(dep+1,i);
            flag[i]:=false;
        end;
end;

begin
    readln(n,m);
    maxw:=0;
    for i:=1 to n do
    begin
        read(a[i]);
        inc(maxw,a[i]);
    end;
    fillchar(flag,n,false);
    max:=0;
    dfs(1,0);
    writeln(max);
end.