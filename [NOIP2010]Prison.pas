//并查集
var n,m,i,ra,rb:longint;
	a,b,c:array[1..100000]of longint;
	fa:array[1..40000]of longint;
	
procedure swap(var x,y:longint);
var t:longint;
begin	
	t:=x;
	x:=y;
	y:=t;
end;
	
procedure qs(l,r:longint);//descend
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
	
function oppo(x:longint):longint;
begin
	if x>n then exit(x-n)
	else exit(x+n);
end;
	
function find(x:longint):longint;
begin
	if fa[x]=x then exit(x);
	fa[x]:=find(fa[x]);
	exit(fa[x]);
end;
	
begin
	readln(n,m);
	for i:=1 to m do
	readln(a[i],b[i],c[i]);
	qs(1,m);
	for i:=1 to 2*n do
	fa[i]:=i;
	for i:=1 to m do
	begin
		ra:=find(a[i]);
		rb:=find(b[i]);
		if ra=rb then break//a,b in same set
		else
		begin
			fa[rb]:=oppo(ra);
			fa[oppo(rb)]:=ra;
		end;
	end;
	if ra=rb then
	writeln(c[i])
	else writeln(0);
end.

//二分图
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
	bool:array[1..20000]of boolean;
	
procedure swap(var x,y:longint);
var t:longint;
begin	
	t:=x;
	x:=y;
	y:=t;
end;
	
procedure qs(l,r:longint);//descend
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
var p,q:node;
begin
	writeln('adding x:',x,' y:',y);
	new(p);
	p^.data:=y;
	p^.next:=bg[x];
	bg[x]:=p;
	new(q);
	q^.data:=x;
	q^.next:=bg[y];
	bg[y]:=q;
end;

function reverse(x:longint):longint;
begin
	if x=1 then exit(2)
	else exit(1);
end;

function dye(x:longint):boolean;
var p:node;
begin
	if bool[x] then exit(true)
	else bool[x]:=true;
	p:=bg[x];
	repeat
		if color[p^.data]=0 then
		color[p^.data]:=reverse(color[x])
		else if color[p^.data]<>reverse(color[x]) then exit(false);
		if not(dye(p^.data)) then exit(false);
		p:=p^.next;
	until p=nil;
	exit(true);
end;

function check(l,r:longint):longint;
var mid,j:longint;
begin
	for j:=1 to n do
	begin
		bg[j]:=nil;
		color[j]:=0;
		bool[j]:=false;
	end;
	mid:=(l+r)div 2;
	for j:=1 to mid do
	add(a[j],b[j]);
	for j:=1 to n do
	begin
		if (bg[j]=nil)or bool[j] then continue;
		if color[j]=0 then color[j]:=1;
		if not(dye(j)) then
		begin
			if l=mid then exit(c[l])
			else exit(check(l,mid));
		end;
	end;
	if l=r then exit(0)
	else exit(check(mid+1,r));
end;
	
begin
	readln(n,m);
	for i:=1 to m do
	readln(a[i],b[i],c[i]);
	qs(1,m);
	writeln(check(1,m));
end.