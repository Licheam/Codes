var i,j:longint;
    a:array[1..9,1..9]of longint;
    row,column,block:array[1..9,1..9]of boolean;

procedure print();
var i,j:longint;
begin
    for i:=1 to 9 do
    begin
        for j:=1 to 9 do
            write(a[i,j],' ');
        writeln;
    end;
end;

procedure dfs(x,y:longint);
var i:longint;
begin
    if x>9 then
    begin
        print;
        halt;
    end
    else if y>9 then
        dfs(x+1,1)
    else if a[x,y]=0 then
    begin
        for i:=1 to 9 do
            if not((row[x,i])or(column[y,i])or(block[((x-1)div 3)*3+((y-1)div 3)+1,i])) then
            begin
                row[x,i]:=true;
                column[y,i]:=true;
                block[((x-1)div 3)*3+((y-1)div 3)+1,i]:=true;
                a[x,y]:=i;
                dfs(x,y+1);
                row[x,i]:=false;
                column[y,i]:=false;
                block[((x-1)div 3)*3+((y-1)div 3)+1,i]:=false;
                a[x,y]:=0;
            end;
    end
    else dfs(x,y+1);
end;

begin
    fillchar(row,sizeof(row),false);
    fillchar(column,sizeof(column),false);
    fillchar(block,sizeof(block),false);
    for i:=1 to 9 do
    for j:=1 to 9 do
    begin
        read(a[i,j]);
        if a[i,j]<>0 then
        begin
            row[i,a[i,j]]:=true;
            column[j,a[i,j]]:=true;
            block[((i-1)div 3)*3+((j-1) div 3)+1,a[i,j]]:=true;
        end;
    end;
    dfs(1,1);
end.