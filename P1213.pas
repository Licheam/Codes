type
	clock=array[1..9]of longint;
	node=^queue;
	queue=record
	data:clock;
	cnt:string;
	next:node;
	end;
	
var t,i:longint;
	head,tail:node;
	cl:clock;
	b:array[1..4,1..4,1..4,1..4,1..4,1..4,1..4,1..4,1..4]of boolean;
	
function check(x:clock):boolean;
var k:longint;
begin
	for k:=1 to 9 do 
	if x[k]<>4 then exit(false);
	exit(true);
end;
	
procedure queini();//head node means nothing but front pointer.
var p:node;
begin
	new(p);
	p^.next:=nil;
	head:=p;
	tail:=p;
end;

procedure push(x:clock;y:string);
var p:node;
begin
	new(p);
	p^.next:=nil;
	p^.data:=x;
	p^.cnt:=y;
	tail^.next:=p;
	tail:=p;
end;

procedure pop();
var p:node;
begin
	if tail=head then exit;
	p:=head^.next;
	if tail=p then tail:=head;
	head^.next:=p^.next;
	dispose(p);
end;

procedure rot(var x:longint);
begin
	if x<4 then
	inc(x)
	else x:=1;
end;

function command(x:clock;y:longint):clock;
begin
	if y=1 then
	begin
		rot(x[1]);
		rot(x[2]);
		rot(x[4]);
		rot(x[5]);
	end
	else if y=2 then
	begin
		rot(x[1]);
		rot(x[2]);
		rot(x[3]);
	end
	else if y=3 then
	begin
		rot(x[2]);
		rot(x[3]);
		rot(x[5]);
		rot(x[6]);
	end
	else if y=4 then
	begin
		rot(x[1]);
		rot(x[4]);
		rot(x[7]);
	end
	else if y=5 then
	begin
		rot(x[2]);
		rot(x[4]);
		rot(x[5]);
		rot(x[6]);
		rot(x[8]);
	end
	else if y=6 then
	begin
		rot(x[3]);
		rot(x[6]);
		rot(x[9]);
	end
	else if y=7 then
	begin
		rot(x[4]);
		rot(x[5]);
		rot(x[7]);
		rot(x[8]);
	end
	else if y=8 then
	begin
		rot(x[7]);
		rot(x[8]);
		rot(x[9]);
	end
	else if y=9 then
	begin
		rot(x[5]);
		rot(x[6]);
		rot(x[8]);
		rot(x[9]);
	end;
	exit(x);
end;//A1 B2 C3 D4 E5 F6 G7 H8 I9

procedure bfs();
var p:node;
	c:clock;
	i,j:longint;
	t:string;
	ct:char;
begin
	if check(cl) then exit;
	repeat
		p:=head^.next;
		for i:=1 to 9 do
		begin
			c:=command(p^.data,i);
			if check(c) then
			begin
				t:=p^.cnt;
				ct:='0';
				inc(ct,i);
				t:=t+ct;
				for j:=1 to length(t) do
				write(t[j],' ');
				exit;
			end;
			if not(b[c[1],c[2],c[3],c[4],c[5],c[6],c[7],c[8],c[9]]) then
			begin
				b[c[1],c[2],c[3],c[4],c[5],c[6],c[7],c[8],c[9]]:=true;
				t:=p^.cnt;
				ct:='0';
				inc(ct,i);
				t:=t+ct;
				push(c,t);
			end;
		end;
		pop;
	until tail=head;
end;

begin
	queini;
	fillchar(b,sizeof(b),false);
	for i:=0 to 2 do
	readln(cl[i*3+1],cl[i*3+2],cl[i*3+3]);
	for i:=1 to 9 do cl[i]:=cl[i] div 3;
	push(cl,'');
	bfs;
end.