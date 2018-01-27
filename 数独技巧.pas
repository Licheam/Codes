var i,j:longint;
    flag:array[1..9,1..9,1..9]of boolean;
    a:array[1..9,1..9]of longint;
    row,column,block:array[1..9,1..9]of longint;
    complete:boolean;

procedure check(x,y:longint);forward;

procedure unslv();
begin
    writeln(-1);
    halt;
end;

procedure falsen(x,y,z:longint);
var dx,dy:longint;
begin
    if flag[x,y,z]=false then exit;
    flag[x,y,z]:=false;
    dx:=((x-1)div 3)*3;
    dy:=((y-1)div 3);
    dec(row[x,z]);
    dec(column[y,z]);
    dec(block[dx+dy+1,z]);
    {if row[x,z]=1 then
        for k:=1 to 9 do
            check(x,k);
    if column[y,z]=1 then
        for k:=1 to 9 do
            check(k,y);
    dy:=dy*3;
    if block[dx+dy+1,z]=1 then
        for k:=1 to 3 do
        for q:=1 to 3 do
            check(dx+k,dy+q);}
    if (row[x,z]=0)or(column[y,z]=0)or(block[dx+dy+1,z]=0) then
        unslv;
end;

procedure dye(x,y:longint);
var dx,dy,k,q:longint;
begin
    dx:=((x-1)div 3)*3;
    dy:=((y-1)div 3);
    for k:=1 to 9 do
    begin
        if k<>a[x,y] then
            falsen(i,j,k);
        if k<>x then
            falsen(k,y,a[x,y]);
        if k<>y then
            falsen(x,k,a[x,y]);
    end;
    dy:=dy*3;
    for k:=1 to 3 do
    for q:=1 to 3 do
        if (dx+k<>x)or(dy+q<>y) then
            falsen(dx+k,dy+q,a[x,y]);
end;

procedure check(x,y:longint);
var k,q,dx,dy,tem:longint;
begin
    dx:=((x-1)div 3)*3;
    dy:=((y-1)div 3);
    tem:=0;
    for k:=1 to 9 do
        if flag[x,y,k] then
        begin
            if (row[x,k]=1)or(column[y,k]=1)or(block[dx+dy+1,k]=1)then
            begin
                tem:=k;
                break;
            end;
            if tem=0 then
                tem:=k
            else
                tem:=-1;
        end;
    if tem=0 then
        unslv
    else if tem<>-1 then
    begin
        a[x,y]:=tem;
        dye(x,y);
        for k:=1 to 9 do
        begin
            if a[x,k]=0 then check(x,k);
            if a[k,y]=0 then check(k,y);
        end;
        dy:=dy*3;
        for k:=1 to 3 do
        for q:=1 to 3 do
            if a[dx+k,dy+q]=0 then check(dx+k,dy+q);
    end;
end;

begin
    fillchar(a,sizeof(a),0);
    fillchar(flag,sizeof(flag),true);
    fillchar(row,sizeof(row),9);
    fillchar(column,sizeof(column),9);
    fillchar(block,sizeof(block),9);
    for i:=1 to 9 do
    for j:=1 to 9 do
    begin
        read(a[i,j]);
        if a[i,j]>0 then
            dye(i,j);
    end;
    repeat
    complete:=true;
    for i:=1 to 9 do
    for j:=1 to 9 do
        if a[i,j]=0 then
        begin
            check(i,j);
            complete:=false;
        end;
    until complete;
    for i:=1 to 9 do
    begin
        for j:=1 to 9 do
        write(a[i,j],' ');
        writeln;
    end;
end.