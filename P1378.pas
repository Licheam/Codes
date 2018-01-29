const maxn=6;
var n,i,x1,y1,x2,y2,s:longint;
    ans:double;
    x,y:array[1..maxn]of longint;
    r:array[1..maxn]of double;

function min(a,b:longint):longint;
begin
    if a>b then exit(b)
    else exit(a);
end;

procedure swap(var a,b:longint);
var t:longint;
begin
    t:=a;
    a:=b;
    b:=t;
end;

procedure permulate(cnt:longint);
var i,j:longint;
    t:double;
begin
    if cnt>n then
    begin
        t:=0;
        for i:=1 to n do
            t:=t+pi*r[i]*r[i];
        //writeln('temp:',t:0:2);
        t:=s-t;
        if t<ans then ans:=t;
        exit;
    end;
    for i:=1 to n do
        if r[i]=-1 then
        begin
            r[i]:=min(min(x[i]-x1,x2-x[i]),min(y[i]-y1,y2-y[i]));
            for j:=1 to n do
                if (r[j]<>-1)and(i<>j) then
                begin
                    t:=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                    if r[j]>=t then
                        t:=0
                    else t:=t-r[j];
                    if t<r[i] then
                        r[i]:=t;
                end;
            //writeln('r',i,':',r[i]:0:2);
            permulate(cnt+1);
            r[i]:=-1;
        end;
end;

begin
    readln(n);
    readln(x1,y1,x2,y2);
    if x1>x2 then swap(x1,x2);//x1<x2
    if y1>y2 then swap(y1,y2);//y1<y2
    s:=(y2-y1)*(x2-x1);
    ans:=s;
    for i:=1 to n do
    begin
        readln(x[i],y[i]);
        r[i]:=-1;
    end;
    permulate(1);
    writeln(round(ans));
end.