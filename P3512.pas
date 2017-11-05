var n,k,i,l1,l2,r1,r2,t,ans:longint;
	a,q1,q2:array[1..3000005]of longint;
begin
	readln(k,n);
	for i:=1 to n do read(a[i]);
	l1:=1;l2:=1;r1:=1;r2:=1;t:=1;
	ans:=0;q1[r1]:=1;q2[r2]:=1;
	for i:=1 to n do
	begin
		while(l1<=r1)and(a[i]<=a[q1[r1]])do//ascend
		dec(r1);
		while(l2<=r2)and(a[i]>=a[q2[r2]])do//descend
		dec(r2);
		inc(r1);inc(r2);
		q1[r1]:=i;q2[r2]:=i;
		while a[q2[l2]]-a[q1[l1]]>k do
		begin
			if q2[l2]<q1[l1] then
			begin
				inc(l2);
				t:=q2[l2];
			end
			else
			begin
				inc(l1);
				t:=q1[l1];
			end;
		end;
		if i-t+1>ans then ans:=i-t+1;
	end;
	writeln(ans);
end.