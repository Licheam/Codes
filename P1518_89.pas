var i,j,m,cnt:longint;
    s:string;
    a:array[1..10,1..10]of longint;
    fa,cow:array[1..2]of longint;
    b:array[1..10,1..10,1..10,1..10,0..3,0..3]of boolean;

begin
    for i:=1 to 10 do
    begin
        readln(s);
        for j:=1 to 10 do
        if s[j]='.' then a[i,j]:=-1
        else if s[j]='*' then a[i,j]:=-2
        else if s[j]='F' then 
        begin
            a[i,j]:=0;
            fa[1]:=i;
            fa[2]:=j;
        end
        else if s[j]='C' then
        begin
            a[i,j]:=0;
            cow[1]:=i;
            cow[2]:=j;
        end;
    end;
    fillchar(b,sizeof(b),false);
    b[fa[1],fa[2],cow[1],cow[2],0,0]:=true;
    cnt:=0;
    repeat
        if a[fa[1],fa[2]]=0 then//up
        begin
            if (fa[1]-1=0)or(a[fa[1]-1,fa[2]]=-2) then
            a[fa[1],fa[2]]:=1
            else
            begin
                if a[fa[1]-1,fa[2]]>=0 then
                m:=a[fa[1]-1,fa[2]];
                a[fa[1]-1,fa[2]]:=a[fa[1],fa[2]];
                a[fa[1],fa[2]]:=-1;
                fa[1]:=fa[1]-1;
            end;
        end
        else if a[fa[1],fa[2]]=1 then//right
        begin
            if (fa[2]+1=11)or(a[fa[1],fa[2]+1]=-2) then
            a[fa[1],fa[2]]:=2
            else
            begin
                if a[fa[1],fa[2]+1]>=0 then
                m:=a[fa[1],fa[2]+1];
                a[fa[1],fa[2]+1]:=a[fa[1],fa[2]];
                a[fa[1],fa[2]]:=-1;
                fa[2]:=fa[2]+1;
            end;
        end
        else if a[fa[1],fa[2]]=2 then//down
        begin
            if (fa[1]+1=11)or(a[fa[1]+1,fa[2]]=-2) then
            a[fa[1],fa[2]]:=3
            else
            begin
                if a[fa[1]+1,fa[2]]>=0 then
                m:=a[fa[1]+1,fa[2]];
                a[fa[1]+1,fa[2]]:=a[fa[1],fa[2]];
                a[fa[1],fa[2]]:=-1;
                fa[1]:=fa[1]+1;
            end;
        end
        else //left
        begin
            if (fa[2]-1=0)or(a[fa[1],fa[2]-1]=-2) then
            a[fa[1],fa[2]]:=0
            else
            begin
                if a[fa[1],fa[2]-1]>=0 then
                m:=a[fa[1],fa[2]-1];
                a[fa[1],fa[2]-1]:=a[fa[1],fa[2]];
                a[fa[1],fa[2]]:=-1;
                fa[2]:=fa[2]-1;
            end;
        end;
        if a[cow[1],cow[2]]<0 then a[cow[1],cow[2]]:=m;
        if a[cow[1],cow[2]]=0 then//up
        begin
            if (cow[1]-1=0)or(a[cow[1]-1,cow[2]]=-2) then
            a[cow[1],cow[2]]:=1
            else
            begin
                a[cow[1]-1,cow[2]]:=a[cow[1],cow[2]];
                a[cow[1],cow[2]]:=-1;
                cow[1]:=cow[1]-1;
            end;
        end
        else if a[cow[1],cow[2]]=1 then//right
        begin
            if (cow[2]+1=11)or(a[cow[1],cow[2]+1]=-2) then
            a[cow[1],cow[2]]:=2
            else
            begin
                a[cow[1],cow[2]+1]:=a[cow[1],cow[2]];
                a[cow[1],cow[2]]:=-1;
                cow[2]:=cow[2]+1;
            end;
        end
        else if a[cow[1],cow[2]]=2 then//down
        begin
            if (cow[1]+1=11)or(a[cow[1]+1,cow[2]]=-2) then
            a[cow[1],cow[2]]:=3
            else
            begin
                a[cow[1]+1,cow[2]]:=a[cow[1],cow[2]];
                a[cow[1],cow[2]]:=-1;
                cow[1]:=cow[1]+1;
            end;
        end
        else //left
        begin
            if (cow[2]-1=0)or(a[cow[1],cow[2]-1]=-2) then
            a[cow[1],cow[2]]:=0
            else
            begin
                a[cow[1],cow[2]-1]:=a[cow[1],cow[2]];
                a[cow[1],cow[2]]:=-1;
                cow[2]:=cow[2]-1;
            end;
        end;
        inc(cnt);
        if b[fa[1],fa[2],cow[1],cow[2],a[fa[1],fa[2]],a[cow[1],cow[2]]] then
        begin
            b[fa[1],fa[2],cow[1],cow[2],a[fa[1],fa[2]],a[cow[1],cow[2]]]:=false;
            break;
        end
        else b[fa[1],fa[2],cow[1],cow[2],a[fa[1],fa[2]],a[cow[1],cow[2]]]:=true;
    until (fa[1]=cow[1])and(fa[2]=cow[2]);
    if b[fa[1],fa[2],cow[1],cow[2],a[fa[1],fa[2]],a[cow[1],cow[2]]] then
    writeln(cnt)
    else
    writeln(0);
end.