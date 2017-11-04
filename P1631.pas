var n,i,len:longint;
	a,b:array[1..100000]of longint;
	s:array[1..200000]of longint;
	
procedure swap(x,y:longint);
var k:longint;
begin
	k:=s[x];
	s[x]:=s[y];
	s[y]:=k;
end;

procedure up(x:longint);
begin
	if(x>1)and(s[x div 2]<s[x])then
	begin 
		swap(x div 2,x);
		up(x div 2);
	end;
end;

procedure down(x:longint);
begin
	if(2*x<=len)and(s[2*x]>s[x])and(s[2*x+1]<=s[2*x]) then
	begin
		swap(2*x,x);
		down(2*x);
	end
	else if(2*x+1<=len)and(s[2*x+1]>s[x])and(s[2*x+1]>s[2*x]) then
	begin
		swap(2*x+1,x);
		down(2*x+1);
	end;
end;

procedure insert(x:longint);
begin
	inc(len);
	s[len]:=x;
	up(len);
end;

procedure delete(x:longint);
begin
	s[x]:=s[len];
	dec(len);
	down(x);
end;
	
	
begin
	readln(n);
	for i:=1 to n do
	read(a[i]);
	for i:=1 to n do
	read(b[i]);
	len:=0;
	insert();
end;