{$R-,S-,Q-,I-,O+}
var
  cnt,c,cm,cr,tm,tr,n,m,i,t,x,s,u,r,j,phi,step: longint;
  md,rem: array [0..1010] of longint;
  a,b: array [0..1000010] of char;
  ch: char;
begin
  read(ch);
  while not (ch in ['0'..'9']) do read(ch);
  n:=0;
  while ch in ['0'..'9'] do
  begin
    inc(n);
    a[n]:=ch;
    read(ch);
  end;
  while not (ch in ['0'..'9']) do read(ch);
  m:=0;
  while ch in ['0'..'9'] do
  begin
    inc(m);
    b[m]:=ch;
    read(ch);
  end;
  read(c);
  t:=0;
  for i:=1 to n do t:=(int64(t)*10+Ord(a[i])-48) mod c;
  x:=c; i:=2; cnt:=0;
  while i <= x do
  begin
    if i*i > x then i:=x;
    if x mod i = 0 then
    begin
      s:=1;
      while x mod i = 0 do
      begin
        x:=x div i;
        s:=s*i;
      end;
      if t mod i = 0 then
      begin
        if m > 2 then r:=0 else
        begin
          u:=0;
          for j:=1 to m do u:=int64(u)*10+Ord(b[j])-48;
          r:=1;
          for j:=1 to u-1 do r:=(int64(r)*t) mod s;
        end;
      end else
      begin
        phi:=s div i*(i-1);
        u:=0;
        for j:=1 to m do u:=(int64(u)*10+Ord(b[j])-48) mod phi;
        if u = 0 then u:=phi;
        r:=1; step:=1 shl 30;
        while step > 0 do
        begin
          r:=(int64(r)*r) mod s;
          if step and (u-1) <> 0 then r:=(int64(r)*t) mod s;
          step:=step shr 1;
        end;
      end;
      inc(cnt);
      md[cnt]:=s;
      rem[cnt]:=r;
    end;
    inc(i);
  end;
  cm:=1; cr:=0;
  for i:=1 to cnt do
  begin
    tm:=md[i]; tr:=rem[i];
    if cm < tm then
    begin
      while tr mod cm <> cr do inc(tr,tm);
      cr:=tr;
    end else
      while cr mod tm <> tr do inc(cr,cm);
    cm:=cm*tm;
  end;
  if t = 0 then t:=c;
  cr:=(int64(cr)*(t-1)) mod c;
  if cr = 0 then cr:=c;
  writeln(cr);
end.