type
	node=^link;
	link=record
	data:longint;
	next:node;
	end;
	
var n,m,i:longint;
	a,b,c:array[1..100000]of longint;
	color:array[1..20000]of longint;
	bg:array[1..20000]of node;
	
procedure swap(var x,y:longint);
var t:longint;
begin	
	t:=x;
	x:=y;
	y:=t;
end;
	
procedure qs(l,r:longint);//降序
var x,y,k:longint;
begin
	x:=l;y:=r;
	k:=c[(l+r)div 2];
	repeat
		while c[x]>k do inc(x);
		while c[y]<k do dec(y);
		if x<=y then
		begin
			swap(c[x],c[y]);
			swap(a[x],a[y]);
			swap(b[x],b[y]);
			inc(x);
			dec(y);
		end;
	until x>y;
	if l<y then qs(l,y);
	if r>x then qs(x,r);
end;
	
procedure add(x,y:longint);
var p:node;
begin
	writeln('adding x:',x,' y:',y);
	new(p);
	p^.data:=y;
	p^.next:=bg[x];
	dispose(p);
	new(p);
	p^.data:=x;
	p^.next:=bg[y];
	dispose(p);
end;

function dye(x:longint):longint;
begin
	if x=1 then exit(2)
	else exit(1);
end;

function check(l,r:longint):longint;
var mid,j,k:longint;
begin
	writeln('checking l:',l,' r:',r);
	if l=r then exit(c[l]);
	for j:=1 to n do bg[j]:=nil;
	mid:=(l+r)div 2;
	for j:=1 to mid do
	add(a[j],b[j]);
	fillchar(color,sizeof(color),0);
	for j:=1 to n do
	begin
		if color[j]=0 then
		color[j]:=1;
		k:=j;
		while bg[k]^.next<>nil do
		begin
			writeln('ok');
			if color[bg[k]^.data]=0 then
			color[bg[k]^.data]:=dye(color[k])
			else if color[bg[k]^.data]<>dye(color[k]) then exit(check(l,mid));
			k:=bg[k]^.data;
		end;
	end;
	exit(check(mid+1,r));
end;
	
begin
	readln(n,m);
	for i:=1 to m do
	readln(a[i],b[i],c[i]);
	qs(1,m);
	writeln('qs over');
	for i:=1 to m do
	writeln(a[i],' ',b[i],' ',c[i]);
	writeln(c[check(1,m)]);
end.
4 6
1 2 28351
3 4 12884
1 3 6618
2 3 3512
1 4 2534
2 4 1805
0 0 0