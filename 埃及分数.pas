//理解1:个数相同，只看最小的分数最大;vijos
const maxa=1000;
var a,b,c,min,i:longint;
	ans,v:array[1..maxa]of longint;
	sble:boolean;

function max(x,y:longint):longint;
begin
	if x>y then exit(x);
	exit(y);
end;

function getfir(x,y:longint):longint;
begin
	if y mod x=0 then exit(y div x)
	else exit((y div x)+1);
end;

function gcd(x,y:longint):longint;//x<y
begin
	if x=0 then exit(y);
	exit(gcd(y mod x,x));
end;

procedure better(x:longint);
var k:longint;
begin
	for k:=x downto 1 do
	ans[k]:=v[k];
end;

function dfs(d,time,x,y:longint):boolean;
var t:longint;
	b:boolean;
begin
	if time>min then exit(false);
	v[time]:=d;
	x:=x*d-y;
	y:=y*d;
	if time=min then
	begin
		if x=0 then
		begin
			if (ans[time]=0)or(ans[time]>v[time]) then better(time);
			exit(true);
		end;
		exit(false);
	end;
	t:=gcd(x,y);
	x:=x div t;y:=y div t;
	b:=false;
	t:=max(getfir(x,y),d+1);
	p:=(min-time)*y div x;
	for t:=max(getfir(x,y),d+1) to (min-time)*y div x do
	if dfs(t,time+1,x,y) then b:=true;
	exit(b);
end;

begin
	readln(a,b);
	c:=getfir(a,b);
	fillchar(ans,sizeof(ans),0);
	sble:=false;
	for min:=1 to maxa do
	begin
		for i:=c to min*b div a do
		if dfs(i,1,a,b) then sble:=true;
		if sble then break;
	end;
	if sble then
	for i:=1 to min do write(ans[i],' ')
	else writeln('indecomposable in ',maxa);
end.


//理解2:个数相同，从最小的开始看起，较小分数的越大越好;RQNOJ
const maxa=1000;
var a,b,c,min,i:longint;
	ans,v:array[1..maxa]of longint;
	sble:boolean;

function max(x,y:longint):longint;
begin
	if x>y then exit(x);
	exit(y);
end;

function getfir(x,y:longint):longint;
begin
	if y mod x=0 then exit(y div x)
	else exit((y div x)+1);
end;

function gcd(x,y:longint):longint;//x<y
begin
	if x=0 then exit(y);
	exit(gcd(y mod x,x));
end;

function better(x:longint):boolean;
var k:longint;
begin
	for k:=x downto 1 do
	if (ans[k]=0)or(ans[k]>v[k]) then exit(true)
	else if ans[k]<v[k] then exit(false);
	exit(false);
end;

function dfs(d,time,x,y:longint):boolean;
var t:longint;
	b:boolean;
begin
	if time>min then exit(false);
	v[time]:=d;
	x:=x*d-y;
	y:=y*d;
	if time=min then
	begin
		if x=0 then
		begin
			if better(time) then
			for t:=1 to time do
			ans[t]:=v[t];
			exit(true);
		end;
		exit(false);
	end;
	t:=gcd(x,y);
	x:=x div t;y:=y div t;
	b:=false;
	for t:=max(getfir(x,y),d+1) to (min-time)*y div x do
	if dfs(t,time+1,x,y) then b:=true;
	exit(b);
end;

begin
	readln(a,b);
	c:=getfir(a,b);
	fillchar(ans,sizeof(ans),0);
	sble:=false;
	for min:=1 to maxa do
	begin
		for i:=c to min*b div a do
		if dfs(i,1,a,b) then sble:=true;
		if sble then break;
	end;
	if sble then
	for i:=1 to min do write(ans[i],' ')
	else writeln('indecomposable in ',maxa);
end.