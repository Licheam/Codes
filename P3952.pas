var m,i,j,p,l,w,cnt,f,deep,max,ac,x1,x2:longint;
    s:string;
    err:boolean;
    c:array[1..100]of char;
    sta:array[1..100]of longint;

function check(ch:char):boolean;
var k:longint;
begin
    for k:=1 to cnt do
    if ch=c[k] then exit(false);
    exit(true);
end;

begin
    readln(m);
    for i:=1 to m do
    begin
        readln(s);
        p:=pos(' ',s);
        val(copy(s,1,p-1),l);
        p:=pos('^',s);
        if p=0 then w:=0
        else val(copy(s,p+1,pos(')',s)-p-1),w);
        //writeln(w);
        cnt:=0;f:=0;max:=0;deep:=0;
        err:=false;ac:=0;
        for j:=1 to l do
        begin
            readln(s);
            if err then continue;
            if s[1]='F' then
            begin
                inc(f);
                if f>(l shr 1) then
                begin
                    err:=true;
                    continue;
                end;
                delete(s,1,2);
                if not(check(s[1])) then
                begin
                    err:=true;
                    continue;
                end;
                inc(cnt);
                c[cnt]:=s[1];
                delete(s,1,2);
                if ac=0 then
                if pos('n',s)=0 then//num to num
                begin
                    p:=pos(' ',s);
                    val(copy(s,1,p-1),x1);
                    val(copy(s,p+1,length(s)-p),x2);
                    //writeln(x1,' ',x2,' ',p);
                    if x1>x2 then
                    ac:=f;
                end
                else if (s[1]='n')and(pos('n',copy(s,2,length(s)-1))=0) then//n to num
                ac:=f
                else if s[1]<>'n' then//num to n
                begin
                    inc(deep);
                    sta[deep]:=f;
                    //writeln(deep,' ',f);
                end;
                //writeln('s:',s,'ac:',ac);
            end
            else if s[1]='E' then
            begin
                dec(f);
                dec(cnt);
                if f<0 then
                begin
                    err:=true;
                    continue;
                end;
                if (ac=0)and(deep>0)and(sta[deep]=f+1) then
                begin 
                    if deep>max then max:=deep;
                    dec(deep);
                end
                else if ac=f+1 then ac:=0;
                //if f=0 then writeln(j,' ',max,' ',deep);
            end;
        end;
        if (err)or(f<>0) then writeln('ERR')
        else if max=w then writeln('Yes')
        else writeln('No');
        //writeln(max);
    end;
end.