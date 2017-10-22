const maxn=100000;
type
	player=record
	s:longint;
	w:longint;
	h:longint;
	end;
	
var n,r,q,i,j:longint;
	p:array[1..2*maxn]of player;
	win,lose:array[1..maxn]of player;
	
function greater(x,y:player):boolean;
begin
	if (x.s>y.s)or((x.s=y.s)and(x.h<y.h)) then exit(true)
	else exit(false);
end;
	
function max(x,y:longint):longint;
begin
	if p[x].w>p[y].w then exit(x)
	else exit(y);
end;

function min(x,y:longint):longint;
begin
	if p[x].w<p[y].w then exit(x)
	else exit(y);
end;

procedure swap(var x,y:player);
var t:player;
begin	
	t:=x;
	x:=y;
	y:=t;
end;

procedure qs(l,r:longint);//descend
var x,y:longint;
	k:player;
begin
	x:=l;y:=r;
	k:=p[(l+r)div 2];
	repeat
		while greater(p[x],k) do inc(x);
		while greater(k,p[y]) do dec(y);
		if x<=y then
		begin
			swap(p[x],p[y]);
			inc(x);
			dec(y);
		end;
	until x>y;
	if l<y then qs(l,y);
	if r>x then qs(x,r);
end;

procedure merge();//descend
var mid,e,x,y:longint;
begin
	e:=2*n;x:=n;y:=n;
	repeat
		if greater(lose[y],win[x]) then
		begin
			p[e]:=win[x];
			dec(x);
		end
		else
		begin
			p[e]:=lose[y];
			dec(y);
		end;
		dec(e);
	until(x<1)or(y<1);
	while x>0 do
	begin
		p[e]:=win[x];
		dec(x);
		dec(e);
	end;
	while y>0 do
	begin
		p[e]:=lose[y];
		dec(y);
		dec(e);
	end;
end;

begin
	readln(n,r,q);
	for i:=1 to 2*n do p[i].h:=i;
	for i:=1 to 2*n do read(p[i].s);
	for i:=1 to 2*n do read(p[i].w);
	qs(1,2*n);
	for i:=1 to r do
	begin
		for j:=1 to n do
		begin
			win[j]:=p[max(2*j-1,2*j)];
			lose[j]:=p[min(2*j-1,2*j)];
			inc(win[j].s);
		end;
		merge();
	end;
	writeln(p[q].h);
end.