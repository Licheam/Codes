const maxn=45;
var n,j,len,tem,cnt:longint;
    i:char;
    row,des:array[1..maxn]of char;

procedure move(num:longint;r2:char);
var r1,r3,i:char;
    j:longint;
begin
    r1:=row[num];
    for i:='A' to 'C' do
        if (i<>r1)and(i<>r2) then
            break;
    r3:=i;
    for j:=num-1 downto 1 do
        if row[j]<>r3 then
            move(j,r3);
    row[num]:=r2;
    inc(cnt);
    writeln('move ',num,' from ',r1,' to ',r2);
end;

begin
    readln(n);
    for i:='A' to 'C' do
    begin
        read(len);
        for j:=1 to len do
        begin
            read(tem);
            row[tem]:=i;
        end;
    end;
    for i:='A' to 'C' do
    begin
        read(len);
        for j:=1 to len do
        begin
            read(tem);
            des[tem]:=i;
        end;
    end;
    cnt:=0;
    for j:=n downto 1 do
        if row[j]<>des[j] then
            move(j,des[j]);
    writeln(cnt);
end.