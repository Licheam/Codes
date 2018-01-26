const maxn=15;
var n,i,j:longint;
    min:double;
    dist:array[0..maxn,0..maxn]of double;
    flag:array[1..maxn]of boolean;
    x,y:array[0..maxn]of double;

procedure dfs(dep,last:longint;dis:double);
var i:longint;
begin
    //write(last,' ');
    if dep>n then
    begin
        //writeln(dis+dist[last,0]:0:2);
        if dis<min then min:=dis;
    end
    else
        for i:=1 to n do
        begin
            if (flag[i])or(min<dis+dist[last,i]) then continue;
            flag[i]:=true;
            dfs(dep+1,i,dis+dist[last,i]);
            flag[i]:=false;
        end;
end;

begin
    readln(n);
    x[0]:=0;y[0]:=0;
    for i:=1 to n do
        readln(x[i],y[i]);
    fillchar(flag,n,false);
    min:=0;
    for i:=0 to n-1 do
        for j:=i+1 to n do
        begin
            dist[i,j]:=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
            dist[j,i]:=dist[i,j];
            //writeln(i,'to',j,':',dist[i,j]:0:2);
            min:=min+dist[i,j];
        end;
    dfs(1,0,0);
    writeln(min:0:2);
end.