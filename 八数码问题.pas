const dest=46686;//123804765

type
	node=^queue;
	queue=record
	data:longint;
	next:node;
	end;
	
var s:string;
	fac:array[0..9]of longint;
	cnt:array[1..362880]of longint;
	bool:array[1..362880]of boolean;
	rear:^node;
	head:node;
	
procedure facini();
var j:longint;
begin
	fac[0]:=1;
	for j:=1 to 8 do fac[j]:=fac[j-1]*j;
end;

function cantor(st:string):longint;
var j,k,temp,num:longint;
begin
	num:=1;
	for j:=1 to 8 do
	begin
		temp:=0;
		for k:=j+1 to 9 do
		if st[k]<st[j] then inc(temp);
		inc(num,fac[9-j]*temp);
	end;
	exit(num);
end;

function revcantor(x:longint):string;
var j,k,q,r:longint;
	st:string;
	temb:array[0..8]of boolean;
begin
	for j:=0 to 8 do temb[j]:=true;
	st:='000000000';
	r:=x-1;
	for j:=9 downto 1 do
	begin
		q:=r div fac[j-1];
		dec(r,q*fac[j-1]);
		for k:=0 to 8 do
		if temb[k] then
		begin
			if q=0 then break;
			dec(q);
		end;
		temb[k]:=false;
		inc(st[10-j],k);
	end;
	exit(st);
end;

procedure queini();
var p:node;
begin
	new(p);
	p^.next:=nil;
	head:=p;
	rear:=@head;
end;

procedure push(x:longint);//push x 入队
var p:node;
begin
	new(p);
	p^.next:=nil;
	p^.data:=x;
	rear^^.next:=p;
	rear:=@rear^^.next;
end;

procedure pop();
var p:node;
begin
	p:=head^.next;
	head^.next:=p^.next;
	dispose(p);
	if rear^=nil then//对于蜜汁错误的特判
	rear:=@head^.next;
end;

procedure bfs();
var t,p,temp:longint;
	st,ts:string;
begin
	t:=cantor(s);
	cnt[t]:=0;
	bool[t]:=true;
	while t<>dest do
	begin
		st:=revcantor(t);
		p:=pos('0',st);
		if (p mod 3)<>1 then//left
		begin
			ts:=copy(st,1,p-2)+'0'+st[p-1]+copy(st,p+1,9-p);
			temp:=cantor(ts);
			if not(bool[temp]) then
			begin
				//writeln('left:',ts,' ',temp);
				cnt[temp]:=cnt[t]+1;
				if temp=dest then exit;
				bool[temp]:=true;
				push(temp);
			end;
		end;
		if (p mod 3)<>0 then//right
		begin
			ts:=copy(st,1,p-1)+st[p+1]+'0'+copy(st,p+2,8-p);
			temp:=cantor(ts);
			if not(bool[temp]) then
			begin
				//writeln('right:',ts,' ',temp);
				cnt[temp]:=cnt[t]+1;
				if temp=dest then exit;
				bool[temp]:=true;
				push(temp);
			end;
		end;
		if p>3 then//up
		begin
			ts:=copy(st,1,p-4)+'0'+copy(st,p-2,2)+st[p-3]+copy(st,p+1,9-p);
			temp:=cantor(ts);
			if not(bool[temp]) then
			begin
				//writeln('up:',ts,' ',temp);
				cnt[temp]:=cnt[t]+1;
				if temp=dest then exit;
				bool[temp]:=true;
				push(temp);
			end;
		end;
		if p<7 then//down
		begin
			ts:=copy(st,1,p-1)+st[p+3]+copy(st,p+1,2)+'0'+copy(st,p+4,6-p);
			temp:=cantor(ts);
			if not(bool[temp]) then
			begin
				//writeln('down:',ts,' ',temp);
				cnt[temp]:=cnt[t]+1;
				if temp=dest then exit;
				bool[temp]:=true;
				push(temp);
			end;
		end;
		t:=head^.next^.data;
		//writeln('get:',revcantor(t),' ',t);
		pop;
	end;
end;

begin
	readln(s);
	fillchar(bool,sizeof(bool),false);
	facini;
	queini;
	bfs;
	writeln(cnt[dest]);
end.