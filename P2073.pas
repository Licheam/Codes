const maxn=100000;
    maxc=1000000;
var c,beau,cost,i,sumb,sumc,len1,len2:longint;
    smab,smac,bigb,bigc:array[1..maxn]of longint;
    cob:array[1..maxc]of longint;
procedure swap(var x,y:longint);
var t:longint;
begin
    t:=x;
    x:=y;
    y:=t;
end;
    
procedure up1(x:longint);//小根
var t:longint;
begin
    t:=x shr 1;
    if (x>1)and(smac[x]<smac[t]) then
    begin
        swap(smac[x],smac[t]);
        swap(smab[x],smab[t]);
        up1(t);
    end;
end;
    
procedure down1(x:longint);
var t:longint;
begin
    t:=x shl 1;
    if t>len1 then exit
    else if (t<len1)and(smac[t]>smac[t+1]) then inc(t);
    if smac[t]<smac[x] then
    begin
        swap(smac[x],smac[t]);
        swap(smab[x],smab[t]);
        down1(t);
    end;
end;

procedure delete1(x:longint);
begin
    if len1=0 then
    begin
        len2:=0;
        exit;
    end;
    while cob[smac[x]]<>smab[x] do
    begin
        smac[x]:=smac[len1];
        smab[x]:=smab[len1];
        dec(len1);
        down1(x);
        if len1=0 then
        begin
            len2:=0;
            exit;
        end;
    end;
    cob[smac[x]]:=0;
    smac[x]:=smac[len1];
    smab[x]:=smab[len1];
    dec(len1);
    down1(x);
end;

procedure insert1(x,y:longint);
begin
    inc(len1);
    smac[len1]:=x;
    smab[len1]:=y;
    up1(len1);
end;

procedure up2(x:longint);//大根
var t:longint;
begin
    t:=x shr 1;
    if (x>1)and(bigc[x]>bigc[t]) then
    begin
        swap(bigc[x],bigc[t]);
        swap(bigb[x],bigb[t]);
        up2(t);
    end;
end;

procedure down2(x:longint);
var t:longint;
begin
    t:=x shl 1;
    if t>len2 then exit
    else if (t<len2)and(bigc[t]<bigc[t+1]) then inc(t);
    if bigc[t]>bigc[x] then
    begin
        swap(bigc[x],bigc[t]);
        swap(bigb[x],bigb[t]);
        down2(t);
    end;
end;

procedure insert2(x,y:longint);
begin
    inc(len2);
    bigc[len2]:=x;
    bigb[len2]:=y;
    up2(len2);
end;

procedure delete2(x:longint);
begin
    if len2=0 then
    begin
        len1:=0;
        exit;
    end;
    while cob[bigc[x]]<>bigb[x] do
    begin
        bigc[x]:=bigc[len2];
        bigb[x]:=bigb[len2];
        dec(len2);
        down2(x);
        if len2=0 then
        begin
            len1:=0;
            exit;
        end;
    end;
    cob[bigc[x]]:=0;
    bigc[x]:=bigc[len2];
    bigb[x]:=bigb[len2];
    dec(len2);
    down2(x);
end;

begin
    len1:=0;
    len2:=0;
    filldword(cob,maxc,0);
    read(c);
    while c<>-1 do
    begin
        if c=1 then
        begin
            readln(beau,cost);
            if cob[cost]=0 then
            begin
                cob[cost]:=beau;
                //if sm[cost]<>beau then
                insert1(cost,beau);
                //if bi[cost]<>beau then
                insert2(cost,beau);
            end;
        end
        else if c=2 then//del big
        delete2(1)
        else if c=3 then//del small
        delete1(1);
        read(c);
    end;
    sumb:=0;sumc:=0;
    for i:=1 to len2 do
    begin
        if cob[bigc[i]]=bigb[i] then
        begin
            inc(sumc,bigc[i]);
            inc(sumb,bigb[i]);
            cob[bigc[i]]:=0;
        end;
    end;
    writeln(sumb,' ',sumc);
end.