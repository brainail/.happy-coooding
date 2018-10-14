{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
const Size=200000;
var a:array[0..Size]of longint;
 min,sum,kmin,doit,_,nz,n,i,l,r,value:longint;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output0.txt');
 rewrite(output);
 read(nz,n);
 for i:=1 to n do a[i]:=0;
 for _:=1 to nz do begin
  if(_>2447)then begin
   doit:=doit;
  end;
  read(doit,l,r);
  if(doit=1)then begin
   min:=maxlongint;
   for i:=l to r do
    if(a[i]<min)then min:=a[i];
   writeln(min);
  end else
  if(doit=2)then begin
   sum:=0;
   for i:=l to r do inc(sum,a[i]);
   writeln(sum);
  end else
  if(doit=3)then begin
   kmin:=0; min:=maxlongint;
   for i:=l to r do begin
    if(a[i]<min)then begin min:=a[i]; kmin:=0; end;
    if(a[i]=min)then inc(kmin);
   end;
   writeln(kmin);
  end else
  if(doit=4)then begin
   read(value);
   for i:=l to r do inc(a[i],value);
  end else assert(0<>0);
 end;
 close(input);
 close(output);
end.