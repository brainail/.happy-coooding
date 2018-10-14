{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
const Size=101000;
var min,l,r,i,testcase,n,tmp,j:longint;
 a:array[0..Size]of longint;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'coutput.txt');
 rewrite(output);
 read(n);
 for i:=1 to n do read(a[i]);
 read(testcase);
 for i:=1 to testcase do begin
  read(l,r);
  if(l>r)then begin tmp:=l; l:=r; r:=tmp; end;
  min:=a[l];
  for j:=l to r do
   if(a[j]<min)then min:=a[j];
  writeln(min);  
 end;
 close(input);
 close(output);
end.