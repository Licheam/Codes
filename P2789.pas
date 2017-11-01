//luoguP2789
var n,cnt:longint;
	b:array[0..300]of boolean;//25*24/2 =300
	
procedure rec(x,y:longint);//x条未分析的直线 已经有y个交点
var k:longint;
begin
	if (x=0)and(not(b[y])) then
	begin
		inc(cnt);
		b[y]:=true;
	end
	else
	for k:=x downto 1 do//使k条直线平行
	rec(x-k,k*(x-k)+y);//k条直线与剩下直线的交点为k*(x-k)
end;

begin
	fillchar(b,sizeof(b),false);
	cnt:=0;
	readln(n);
	rec(n,0);
	writeln(cnt);
end.

//以下是没有写完的整数拆分优化= =
const s:array[1..25]of longint=(1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441,484,529,576,625);
// s[i]=i^2;
var n,cnt,i:longint;
	a:array[0..25]of longint;
	bool:array[1..300]of boolean;//max of n=25, max intersection point=300

procedure cal();
var tem:longint;
begin
	tem:=s[n];
	for i:=n downto 1 do
	begin
		if a[i]=0 then break;
		dec(tem,s[a[i]]);
	end;
	tem:=tem shr 1;
	if not(bool[tem]) then
	begin
		inc(cnt);
		bool[tem]:=true;
	end;
end;

procedure next(x:longint);
var 
begin
	//if a[x-1]=0 then cal;
	cal;
	if a[x]=1 then exit;
	
end;

begin
	readln(n);
	fillchar(bool,sizeof(bool),false);
	cnt:=0;
	fillchar(a,sizeof(a),0);
	a[n]:=n;
	next(n);
	writeln(cnt);
end.