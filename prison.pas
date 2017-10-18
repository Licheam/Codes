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
		//writeln('color[',p^.data,']=',color[p^.data]);
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
	//writeln('checking l:',l,' r:',r);
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
	{assign(input,'prison.in');
	assign(output,'prison.out');
	reset(input);
	rewrite(output);}
	readln(n,m);
	for i:=1 to m do
	readln(a[i],b[i],c[i]);
	qs(1,m);
	//writeln('qs over');
	//for i:=1 to m do
	//writeln(a[i],' ',b[i],' ',c[i]);
	writeln(check(1,m));
	//close(input);
	//close(output);
end.




var n,m,i:longint;
	a,b,c:array[1..100000]of longint;
	father:array[1..40000]of longint;
	
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
	
function find(x:longint):longint;
begin
	
end;
	
	
begin
	readln(n,m);
	for i:=1 to m do
	readln(a[i],b[i],c[i]);
	qs(1,m);
	for i:=1 to n do father[i]:=i;
	for i:=1 to m do
	begin
		if (father[a[i]]=a[i])and(father[b[i]]=b[i]) then
		father[b[i]]=a[i]+n
		else if (find(a[i])<>a[i])and(father[b[i]])
	end;
end.


4 6
1 2 28351
3 4 12884
1 3 6618
2 3 3512
1 4 2534
2 4 1805
0 0 0