const maxn=500;
var n,m,i,j,cnt,p,maxr:longint;
    h,l,r:array[1..maxn,1..maxn]of longint;
    flag:array[1..maxn,1..maxn]of boolean;

procedure dfs(x,y:longint);
begin
    flag[x,y]:=true;
    if (x>1)and(h[x,y]>h[x-1,y]) then
    begin
        if not(flag[x-1,y]) then
            dfs(x-1,y);
        if l[x,y]>l[x-1,y] then
            l[x,y]:=l[x-1,y];
        if r[x,y]<r[x-1,y] then
            r[x,y]:=r[x-1,y];
    end;
    if (y>1)and(h[x,y]>h[x,y-1]) then
    begin
        if not(flag[x,y-1]) then
            dfs(x,y-1);
        if l[x,y]>l[x,y-1] then
            l[x,y]:=l[x,y-1];
        if r[x,y]<r[x,y-1] then
            r[x,y]:=r[x,y-1];
    end;
    if (x<n)and(h[x,y]>h[x+1,y]) then
    begin
        if not(flag[x+1,y]) then
            dfs(x+1,y);
        if l[x,y]>l[x+1,y] then
            l[x,y]:=l[x+1,y];
        if r[x,y]<r[x+1,y] then
            r[x,y]:=r[x+1,y];
    end;
    if (y<m)and(h[x,y]>h[x,y+1]) then
    begin
        if not(flag[x,y+1]) then
            dfs(x,y+1);
        if l[x,y]>l[x,y+1] then
            l[x,y]:=l[x,y+1];
        if r[x,y]<r[x,y+1] then
            r[x,y]:=r[x,y+1];
    end;
end;

begin
    readln(n,m);
    for i:=1 to n do
    for j:=1 to m do
    begin
        read(h[i,j]);
        flag[i,j]:=false;
        if i=n then
        begin
            l[i,j]:=j;
            r[i,j]:=j;
        end
        else
        begin
            l[i,j]:=501;
            r[i,j]:=0;
        end;
    end;
    for i:=1 to m do
        if not(flag[1,i]) then
            dfs(1,i);
    cnt:=0;
    for i:=1 to m do
        if not(flag[n,i]) then
            inc(cnt);
    if cnt>0 then
    begin
        writeln(0);
        writeln(cnt);
    end
    else
    begin
        writeln(1);
        p:=1;
        //for i:=1 to m do
        //writeln(i,': l:',l[1,i],' r:',r[1,i]);
        while p<=m do
        begin
            maxr:=0;
            for i:=1 to m do
                if (l[1,i]<=p)and(maxr<r[1,i]) then
                    maxr:=r[1,i];
            inc(cnt);
            p:=maxr+1;
        end;
        writeln(cnt);
    end;
end.