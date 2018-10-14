{$R+,S+,Q+,I+,O-}
var
  b,n,i,j,k,p: longint;
  t: array [0..9999] of byte;
begin
  read(n,k);
  fillchar(t,sizeof(t),0);
  p:=2;
  for i:=3 to n do
  begin
    b:=1;
    for j:=2 to i-1 do
      if i mod j = 0 then b:=0;
    dec(k,t[i]*b);
    t[i+p+1]:=b;
    if b = 1 then p:=i;
  end;
  if k <= 0 then writeln('YES')
  else writeln('NO');
end.