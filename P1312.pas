type matrix=array[1..5,1..7]of longint;
var times,i,j:longint;
    mtx:matrix;
    a,b,c:array[1..5]of longint;//x y g

procedure print();
var i,j:longint;
begin
    for j:=7 downto 1 do
    begin
        for i:=1 to 5 do
            write(mtx[i,j],' ');
        writeln;
    end;
end;

procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;

procedure move(x,y,g:longint);
var i,j,k:longint;
    loop:boolean;
    flag:array[1..5,1..7]of boolean;

    function clean(x,y,di,ti:longint):boolean;
    begin
        if ti>=3 then
        begin
            flag[x,y]:=true;
            clean:=true;
        end
        else clean:=false;
        if di=1 then//right
            if (x<5)and(mtx[x+1,y]=mtx[x,y]) then
                if clean(x+1,y,di,ti+1) then
                begin
                    flag[x,y]:=true;
                    clean:=true;
                end;
        if di=2 then//up
            if (y>1)and(mtx[x,y-1]=mtx[x,y]) then
                if clean(x,y-1,di,ti+1) then
                begin
                    flag[x,y]:=true;
                    clean:=true;
                end;
    end;

begin
    if g=1 then
    begin
        swap(mtx[x+1,y],mtx[x,y]);
        if mtx[x,y]=0 then
        begin
            for i:=1 to y-1 do
                if mtx[x+1,i]=0 then
                begin
                    swap(mtx[x+1,y],mtx[x+1,i]);
                    break;
                end;
            for i:=y+1 to 7 do
                if mtx[x,i]>0 then
                    swap(mtx[x,i],mtx[x,i-1])
                else break;
        end;
    end
    else
    begin
        swap(mtx[x-1,y],mtx[x,y]);
        if mtx[x,y]=0 then
        begin
            for i:=1 to y-1 do
                if mtx[x-1,i]=0 then
                begin
                    swap(mtx[x-1,y],mtx[x-1,i]);
                    break;
                end;
            for i:=y+1 to 7 do
                if mtx[x,i]>0 then
                    swap(mtx[x,i],mtx[x,i-1])
                else break;
        end;
    end;

    repeat
        loop:=false;
        fillchar(flag,sizeof(flag),false);
        for i:=1 to 5 do
        for j:=1 to 7 do
            if (mtx[i,j]>0) then
            begin
                if (i<=3)and(not((i>1)and(mtx[i-1,j]=mtx[i,j]))) then
                    if clean(i,j,1,1) then//1 right
                        loop:=true;
                if (j<=5)and(not((j<7)and(mtx[i,j+1]=mtx[i,j]))) then
                    if clean(i,j,2,1) then//2 up
                        loop:=true;
            end
            else break;
        if loop then
        begin
            for j:=7 downto 1 do
            for i:=1 to 5 do
                if flag[i,j] then
                begin
                    mtx[i,j]:=0;
                    for k:=j+1 to 7 do
                        if mtx[i,k]>0 then
                            swap(mtx[i,k],mtx[i,k-1]);
                end;
        end;
    until (not loop);
end;

procedure dfs(x:longint);
var i,j:longint;
    complete:boolean;
    tem:matrix;
begin
    //writeln('dfs:',x);
    //print(mtx);
    if x>times then
    begin
        complete:=true;
        for i:=1 to 5 do
            if mtx[i,1]>0 then
            begin
                complete:=false;
                break;
            end;
        if complete then
        begin
            for i:=1 to times do
                writeln(a[i]-1,' ',b[i]-1,' ',c[i]);
            halt;
        end;
        exit;
    end;
    tem:=mtx;
    for i:=1 to 5 do
    for j:=1 to 7 do
    begin
        if mtx[i,j]<>0 then
        begin
            if (i<5)and(mtx[i+1,j]<>mtx[i,j]) then
            begin
                a[x]:=i;
                b[x]:=j;
                c[x]:=1;
                move(i,j,1);
                dfs(x+1);
                mtx:=tem;
            end;
            if (i>1)and(mtx[i-1,j]<>mtx[i,j])and(mtx[i-1,j]=0) then
            begin
                a[x]:=i;
                b[x]:=j;
                c[x]:=-1;
                move(i,j,-1);
                dfs(x+1);
                mtx:=tem;
            end;
        end
        else break;
    end;
end;

begin
    readln(times);
    fillchar(mtx,sizeof(mtx),0);
    for i:=1 to 5 do
    begin
        j:=1;
        read(mtx[i,j]);
        while mtx[i,j]<>0 do
        begin
            inc(j);
            read(mtx[i,j]);
        end;
    end;
    dfs(1);
    writeln(-1);
    //play mode
    {print;
    readln(a[1],b[1],c[1]);
    while a[1]<>0 do
    begin
        move(a[1],b[1],c[1]);
        print;
        readln(a[1],b[1],c[1]);
    end;}
end.