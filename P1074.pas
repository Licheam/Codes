const multi:array[1..9,1..9]of longint=((6,6,6,6,6,6,6,6,6),           
                                        (6,7,7,7,7,7,7,7,6),
                                        (6,7,8,8,8,8,8,7,6),
                                        (6,7,8,9,9,9,8,7,6),
                                        (6,7,8,9,10,9,8,7,6),
                                        (6,7,8,9,9,9,8,7,6),
                                        (6,7,8,8,8,8,8,7,6),
                                        (6,7,7,7,7,7,7,7,6),
                                        (6,6,6,6,6,6,6,6,6));
    blk:array[1..9,1..9]of longint=((1,1,1,2,2,2,3,3,3),
                                    (1,1,1,2,2,2,3,3,3),
                                    (1,1,1,2,2,2,3,3,3),
                                    (4,4,4,5,5,5,6,6,6),
                                    (4,4,4,5,5,5,6,6,6),
                                    (4,4,4,5,5,5,6,6,6),
                                    (7,7,7,8,8,8,9,9,9),
                                    (7,7,7,8,8,8,9,9,9),
                                    (7,7,7,8,8,8,9,9,9));
var i,j,max:longint;
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

procedure cal();
var i,j,sum:longint;
begin
    //print;
    sum:=0;
    for i:=1 to 9 do//5,46,37,28,19
        for j:=1 to 9 do
            if a[i,j]=0 then exit
            else
            inc(sum,multi[i,j]*a[i,j]);
    if max<sum then max:=sum;
end;

procedure dfs(x,y:longint);
var i:longint;
begin
    if x=0 then
    begin
        cal;
        //if sum>max then max:=sum;
    end
    else if y=0 then
        dfs(x-1,9)
    else if a[x,y]=0 then
    begin
        for i:=1 to 9 do
            if not((row[x,i])or(column[y,i])or(block[blk[x,y],i])) then
            begin
                row[x,i]:=true;
                column[y,i]:=true;
                block[blk[x,y],i]:=true;
                a[x,y]:=i;
                //tem:=i*mul;
                //inc(sum,tem);
                dfs(x,y-1);
                row[x,i]:=false;
                column[y,i]:=false;
                block[blk[x,y],i]:=false;
                a[x,y]:=0;
                //dec(sum,tem);
            end;
    end
    else dfs(x,y-1);
end;

begin
    fillchar(row,sizeof(row),false);
    fillchar(column,sizeof(column),false);
    fillchar(block,sizeof(block),false);
    fillchar(a,sizeof(a),0);
    for i:=1 to 9 do
    for j:=1 to 9 do
    begin
        read(a[i,j]);
        if a[i,j]<>0 then
        begin
            row[i,a[i,j]]:=true;
            column[j,a[i,j]]:=true;
            block[blk[i,j],a[i,j]]:=true;
            //inc(sum,multi(i,j)*a[i,j]);
        end;
    end;
    max:=0;
    dfs(9,9);
    if max=0 then writeln(-1)
    else writeln(max);
end.