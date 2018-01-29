var n,i,a,min,max,sum,times:longint;
    stick:array[1..50]of longint;

procedure dfs(x,y,last:longint);
var k:longint;
begin
    if x=0 then
    begin
        inc(y);
        if y=times then
        begin
            writeln(i);
            halt;
        end;
        x:=i;
        last:=max;
    end;
    //writeln(x,' ',y);
    for k:=last downto 1 do
    begin
        if (k<=x)and(stick[k]>0) then
        begin
            dec(stick[k]);
            //write(k,' ');
            dfs(x-k,y,k);
            inc(stick[k]);
            //write(' -',k,'- ')
            if (x=i)or(x=k) then
                break;
        end;
    end;
end;

begin
    readln(i);
    filldword(stick,50,0);
    n:=0;
    min:=50;max:=0;sum:=0;
    while i>0 do
    begin
        inc(n);
        read(a);
        if a>50 then
            dec(n)
        else 
        begin
            inc(stick[a]);
            if max<a then max:=a;
            if min>a then min:=a;
            inc(sum,a);
        end;
        dec(i);
    end;

    {for i:=1 to 50 do
    writeln(i,':',stick[i]);

    writeln(min,' ',max);}

    for i:=max to sum do
    begin
        if (sum mod i)<>0 then
            continue;
        times:=sum div i;
        dfs(i,0,max);
        //writeln(i);
    end;
end.