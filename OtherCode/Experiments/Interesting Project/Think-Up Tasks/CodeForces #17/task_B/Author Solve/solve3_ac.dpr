{$R+,S+,Q+,I+,O-}
var
  n,i,m,a,b,c: longint;
  d: array [0..1010] of longint;
begin
  read(n);
  for i:=1 to n do read(a);
  for i:=1 to n do d[i]:=maxlongint;
  read(m);
  for i:=1 to m do
  begin
    read(a,b,c);
    if c < d[b] then d[b]:=c;
  end;
  a:=0; b:=0;
  for i:=1 to n do
    if d[i] = maxlongint then inc(a)
    else inc(b,d[i]);
  if a > 1 then b:=-1;
  writeln(b);
end.