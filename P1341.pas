const maxn=2704;
var n,i,j,f,g,p,cnt:longint;
    am:array[1..52,1..52]of boolean;
    s:string;
    ans:array[1..maxn]of longint;
    dgr:array[1..52]of longint;

function ascii(c:char):longint;
begin
    if ord(c)<=90 then exit(ord(c)-64)
    else exit(ord(c)-70);
end;

function antiascii(x:longint):char;
begin
    if x<=26 then exit(chr(x+64))
    else exit(chr(x+70));
end;

procedure eular(x:longint);
var k:longint;
begin
    for k:=1 to 52 do
    if am[x,k] then
    begin
        am[x,k]:=false;
        am[k,x]:=false;
        eular(k);
    end;
    ans[cnt]:=x;
    dec(cnt);
end;

begin
    filldword(dgr,52,0);
    fillchar(am,sizeof(am),false);
    readln(n);
    for i:=1 to n do
    begin
        readln(s);
        f:=ascii(s[1]);
        g:=ascii(s[2]);
        //writeln(f,' ',g);
        inc(dgr[f]);
        inc(dgr[g]);
        am[f,g]:=true;
        am[g,f]:=true;
    end;
    p:=52;
    cnt:=0;
    for i:=1 to 52 do
        if (dgr[i] and 1)=1 then
        begin
            if p>i then
            p:=i;
            inc(cnt);
        end;
    if (cnt<>0)and(cnt<>2) then
    begin
        writeln('No Solution');
        halt;
    end
    else if cnt=0 then
    for p:=1 to 52 do
    if dgr[p]>0 then break;
    cnt:=n+1;
    eular(p);
    for i:=1 to n+1 do
    write(antiascii(ans[i]));
end.