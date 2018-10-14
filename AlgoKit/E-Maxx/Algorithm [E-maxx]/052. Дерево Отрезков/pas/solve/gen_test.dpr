{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
uses math;
const nSize=10000;
const nzSize=10000;
const valSize=99;
var doit,i,l,r:longint;

begin
 randomize;
 assign(output,'input.txt');
 rewrite(output);
 writeln(nzSize,' ',nSize);
 for i:=1 to nzSize do begin
  doit:=random(5);
  if(doit=0)then doit:=4;
  l:=random(nSize)+1;
  r:=random(nSize)+1;
  write(doit,' ',min(l,r),' ',max(l,r));
  if(doit=4)then write(' ',random(valSize)-random(valSize));
  writeln;
 end;
 close(output);
end.