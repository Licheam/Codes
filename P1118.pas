const maxn=12;
var n,i,sum,a,b:longint;
    table,per:array[1..maxn]of longint;
    flag:array[1..maxn]of boolean;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure permulate(x,ans:longint);
var i,t:longint;
begin
    if x>n then
    begin
        if ans=sum then
        begin
            for i:=1 to n do
                write(per[i],' ');
            halt;
        end;
        {for i:=1 to n do
                write(per[i],' ');
        writeln;}
    end
    else
        for i:=1 to n do
        begin
            if flag[i] then continue;
            t:=ans+i*table[x];
            if t>sum then exit;
            per[x]:=i;
            flag[i]:=true;
            permulate(x+1,t);
            flag[i]:=false;
        end;
end;

begin
    readln(n,sum);
    a:=1;
    b:=1;
    for i:=1 to round(n/2+0.1) do
    begin
        table[i]:=a div b;
        table[n-i+1]:=table[i];
        a:=a*(n-i);
        b:=b*i;
    end;
    {for i:=1 to n do
    write(table[i],' ');
    writeln;}
    fillchar(flag,n,false);
    permulate(1,0);
end.