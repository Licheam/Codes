const maxn=6;
    maxq=10000;
    pri=520123;
type queue=record
    times:shortint;
    s:string;
    end;
var n,i,p,l,r,tt,lst,pt,ht:longint;
    s1,s2,st,temp:string;
    a,b:array[1..maxn]of string;
    la:array[1..maxn]of longint;
    que:array[1..maxq]of queue;
    flag:array[0..pri-1]of boolean;

function hash(s:string):longint;
var i,len,x:longint;
begin
    len:=length(s);
    hash:=0;
    x:=1;
    for i:=1 to len do
    begin
        hash:=(hash+ord(s[i])*x)mod pri;
        x:=x*31 mod pri;
    end;
end;

begin
    readln(s1);
    p:=pos(' ',s1);
    s2:=copy(s1,p+1,length(s1)-p);
    s1:=copy(s1,1,p-1);
    n:=0;
    while not(eof) do
    //for i:=1 to 3 do
    begin
        inc(n);
        readln(a[n]);
        p:=pos(' ',a[n]);
        b[n]:=copy(a[n],p+1,length(a[n])-p);
        a[n]:=copy(a[n],1,p-1);
        la[n]:=length(a[n]);
    end;
    //writeln('BFS..');
    //BFS
    fillchar(flag,pri,false);
    l:=1;r:=1;
    que[1].times:=0;
    que[1].s:=s1;
    while l-r<>1 do
    begin
        st:=que[l].s;
        tt:=que[l].times;
        lst:=length(st);
        inc(l);
        if l>maxq then l:=1;
        for i:=1 to n do
        begin
            p:=pos(a[i],st);
            pt:=p;
            while pt<>0 do
            begin
                temp:=copy(st,1,p-1)+b[i]+copy(st,p+la[i],lst-p-la[i]+1);
                if temp=s2 then
                begin
                    writeln(tt+1);
                    halt;
                end;
                ht:=hash(temp);
                if (tt<9)and(not flag[ht]) then
                begin
                    flag[ht]:=true;
                    inc(r);
                    if r>maxq then r:=1;
                    que[r].times:=tt+1;
                    que[r].s:=temp;
                    //writeln('l:',l,'r:',r,' times:',tt+1,' string:',temp);
                end;
                pt:=pos(a[i],copy(st,p+la[i],lst-p-la[i]+1));
                //writeln(pt);
                p:=p+la[i]+pt-1;
            end;
        end;
    end;
    writeln('NO ANSWER!');
end.