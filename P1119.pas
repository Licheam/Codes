const maxn=200;
    maxm=19900;
    maxq=50000;

var n,m,i,j,k,qur,cur,f,g,w,time:longint;
    a,ma:array[0..maxn-1,0..maxn-1]of longint;
    ti:array[0..maxn-1]of longint;

begin
    readln(n,m);
    for i:=0 to n-1 do
    read(ti[i]);
    ti[n]:=100001;
    for i:=0 to n-1 do
    begin
        for j:=0 to n-1 do
        if i=j then ma[i,j]:=0
        else ma[i,j]:=100001;
    end;
    for i:=1 to m do
    begin
        readln(f,g,w);
        ma[f,g]:=w;
        ma[g,f]:=w;
    end;
    readln(qur);
    cur:=0;
    for i:=1 to qur do
    begin
        readln(f,g,time);
        //writeln('qur:',i);
        while ti[cur]<=time do//find current time
        begin
            for j:=0 to cur do
            begin
                a[cur,j]:=ma[cur,j];
                a[j,cur]:=ma[j,cur];
            end;
            //writeln(cur,' added');
            for j:=0 to cur-1 do
            begin
                for k:=0 to cur-1 do
                begin
                    if a[cur,k]>a[cur,j]+a[j,k] then
                    begin
                        a[cur,k]:=a[cur,j]+a[j,k];
                        a[k,cur]:=a[cur,k];
                    end;
                end;
            end;
            for j:=0 to cur-1 do
            begin
                for k:=0 to cur-1 do
                begin
                    if a[j,k]>a[j,cur]+a[cur,k] then
                    begin
                        a[j,k]:=a[j,cur]+a[cur,k];
                        a[k,j]:=a[j,k];
                    end;
                end;
            end;
            inc(cur);
        end;
        if (f<cur)and(g<cur)and(a[f,g]<>100001) then
        writeln(a[f,g])
        else writeln(-1);
        {for j:=0 to cur-1 do
        for k:=0 to cur-1 do
        writeln(j,' to ',k,':',a[j,k]);}
    end;
end.