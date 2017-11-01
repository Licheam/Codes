const c=ln(10);
var n,mid,l,r:longint;
begin
	readln(n);
	dec(n);
	l:=1;r:=n;mid:=(l+r)div 2;
	while l<r do
	begin
		if mid*ln(mid)/c>=n then
		r:=mid
		else
		l:=mid+1;
		mid:=(l+r)div 2;
	end;
	writeln(l);
end.//对于小的数，r的上界有问题。（不过懒得管了