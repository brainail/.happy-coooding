{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
const SIZE=1000010;
type Tlong=record n:longint; a:array[0..SIZE]of shortint; end;
var BASE,n,phi,i,wb,pow,res:longint;
 p,b:Tlong;
 ch:char;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 // Reading
 read(ch);
 b.n := 0;
 while(ch in ['0'..'9'])do begin
  inc(b.n); b.a[b.n] := ord(ch)-ord('0');
  read(ch);
 end;
 read(ch);
 p.n := 0;
 while(ch in ['0'..'9'])do begin
  inc(p.n); p.a[p.n] := ord(ch)-ord('0');
  read(ch);
 end;
 read(BASE);

 // Count phi
 n := BASE; phi := n;
 for i:=2 to trunc(sqrt(BASE+1)) do
  if(n mod i = 0)then begin
   while(n mod i = 0)do n := n div i;
   phi := phi - (phi div i);
  end;
 if(n > 1)then phi := phi - (phi div n); 

 // P --
 p.a[p.n] := p.a[p.n] - 1;
 for i:=p.n downto 1 do
  if(p.a[i] < 0)then begin
   inc(p.a[i], 10); dec(p.a[i-1]);
  end;

 // If Step not big -> brute pow = p
 if(p.n < 7)then begin
  pow := 0;
  for i:=1 to p.n do pow := pow * 10 + p.a[i];
 end else begin 

  // Step % phi
  pow := 0;
  for i:=1+ord(p.a[1]=0) to p.n do pow := (int64(pow) * 10 + p.a[i]) mod phi;
  while(pow < 50)do pow := pow + phi;
 end;

 // B^pow % BASE = (B % BASE)^pow % BASE
 wb := 0;
 for i:=1 to b.n do wb := (int64(wb) * 10 + b.a[i]) mod BASE;

 res := 1;
 while(pow > 0)do
  if(pow and 1 = 1)then begin
   res := (int64(res) * wb) mod BASE;
   dec(pow);
  end else begin
   wb := (int64(wb) * wb) mod BASE;
   pow := pow shr 1;
  end;

 // B --
 b.a[b.n] := b.a[b.n] - 1;
 for i:=b.n downto 1 do
  if(b.a[i] < 0)then begin
   inc(b.a[i], 10); dec(b.a[i-1]);
  end;

 // B % BASE
 wb := 0;
 for i:=1+ord(b.a[1]=0) to b.n do wb := (int64(wb) * 10 + b.a[i]) mod BASE;

 res := (int64(res) * wb) mod BASE;

 if(res = 0)then res := BASE;
 writeln(res);
 close(input);
 close(output);
end.