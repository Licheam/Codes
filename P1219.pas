const maxn=13;
var n,i,cnt:longint;
    ans:array[1..maxn]of longint;
    column:array[1..maxn]of boolean;
    lr,rl:array[1..2*maxn]of boolean;
    
procedure print();
var i:longint;
begin
    for i:=1 to n do
    write(ans[i],' ');
    writeln;
end;

procedure check(x,y:longint);
var i:longint;
begin
    ans[y]:=x;
    if y=n then
    begin
        inc(cnt);
        if cnt<=3 then print;
    end
    else
    begin
        column[x]:=true;
        lr[x-y+n]:=true;
        rl[x+y]:=true;
        for i:=1 to n do//column:i;
            if not(column[i] or lr[i-y-1+n] or rl[i+y+1]) then
            check(i,y+1);
        column[x]:=false;
        lr[x-y+n]:=false;
        rl[x+y]:=false;
    end;
end;

begin
    readln(n);
    cnt:=0;
    fillchar(column,n,false);
    fillchar(lr,n,false);
    fillchar(rl,2*n,false);
    for i:=1 to n do
    check(i,1);
    writeln(cnt);
end.