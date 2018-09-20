const maxn=1000;
	maxm=10000;
var n,m,i,k,ans:longint;
	fa:array[1..maxn]of longint;
	a,b,c:array[1..maxm]of longint;

procedure swap(var x,y:longint);
var t:longint;
begin
	t:=x;
	x:=y;
	y:=t;
end;

function find(x:longint):longint;
begin
	if fa[x]=x then exit(x);
	fa[x]:=find(fa[x]);
	exit(fa[x]);
end;

procedure qsort(l,r:longint);
var x,y,t:longint;
begin
	x:=l;y:=r;
	t:=c[(l+r)shr 1];
	repeat
		while c[x]<t do inc(x);
		while c[y]>t do dec(y);
		if x<=y then
		begin
			swap(a[x],a[y]);
			swap(b[x],b[y]);
			swap(c[x],c[y]);
			inc(x);
			dec(y);
		end;
	until x>y;
	if l<y then qsort(l,y);
	if x<r then qsort(x,r);
end;

begin
	readln(n,m,k);
	for i:=1 to m do
		readln(a[i],b[i],c[i]);
	ans:=0;
	qsort(1,m);
	for i:=1 to n do
		fa[i]:=i;
	dec(k,n);
	for i:=1 to m do
	begin
		if k>=0 then break;
		if find(a[i])=find(b[i]) then continue;
		inc(ans,c[i]);
		fa[fa[a[i]]]:=fa[b[i]];
		inc(k);
	end;
	if k>=0 then writeln(ans)
	else writeln('No Answer');
end.