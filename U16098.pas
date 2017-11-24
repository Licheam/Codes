const maxn=100000000;
    maxp=45000;
var n,p,i,j,t1,t2:longint;
    ans:Int64;
    pre,del:array[0..maxp]of longint;

function binpow(x,y,m:Int64):Int64;
var r:Int64;
begin
    r:=1;
    while y<>0 do
    begin
        if (y and 1)=1 then r:=r*x mod m;//当i位为1时,r*=x^(2^i)
        x:=x*x mod m;//x^(2^i)*x^(2^i)=x^(2^(i+1)); same as i++ for x;
        y:=y shr 1;//i++ for y
    end;
    exit(r);
end;

begin
    assign(input,'question.in');
    assign(output,'question.out');
    reset(input);
    rewrite(output);
    readln(n,p);//n>p
    ans:=0;
    del[p]:=0;
    for i:=1 to p-1 do
    begin
        del[i]:=binpow(i,p,p);
        //writeln(del[i]);
    end;
    for i:=1 to p-1 do
    begin
        pre[i]:=binpow(i,i,p);
        ans:=(ans+pre[i]);
        if i=n then break;
        //writeln(pre[i]);
    end;
    ans:=ans mod p;
    if i<>n then
    begin
        t1:=n div p;
        for i:=2 to t1 do
        begin
            for j:=1 to p-1 do
            begin
                pre[j]:=pre[j]*del[j] mod p;
                ans:=(ans+pre[j]);
            end;
            ans:=ans mod p;
        end;
        t1:=n mod p;
        for j:=1 to t1 do
        begin
            pre[j]:=pre[j]*del[j] mod p;
            ans:=(ans+pre[j])mod p;
        end;
    end;
    writeln(ans);
    close(input);
    close(output);
end.