{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
uses math;
const nSize=10000;
const nzSize=10000;
const valSize=1000000000;
var l,r,doit,value,i:longint;

begin
 randomize;
 assign(output,'input.txt');
 rewrite(output);
 writeln(nzSize,' ',nSize);
 for i:=1 to nzSize do begin
  doit:=random(2);
  l:=random(nSize)+1;
  r:=random(nSize)+1;
  value:=random(valSize)-random(valSize);
  if(doit=0)then
   writeln('1 ',min(l,r),' ',max(l,r)) else
   writeln('2 ',l,' ',value);
 end;
 close(output);
end.