{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
const Size=200000;
var l,value,doit,r,_,n,nz,i,min:longint;
 a:array[0..Size]of longint;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output0.txt');
 rewrite(output);
 read(nz,n);
 for i:=1 to n do a[i]:=maxlongint;
 for _:=1 to nz do begin
  read(doit);
  if(doit=1)then begin
   read(l,r);
   min:=maxlongint;
   for i:=l to r do
    if(a[i]<min)then min:=a[i];
   writeln(min);
  end else
  if(doit=2)then begin
   read(l,value);
   if(value<a[l])then a[l]:=value;
  end else assert(0<>0);
 end;
 close(input);
 close(output);
end.