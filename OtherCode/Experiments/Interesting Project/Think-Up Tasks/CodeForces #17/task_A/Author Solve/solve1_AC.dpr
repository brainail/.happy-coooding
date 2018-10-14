{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
const SIZE=1010;
var col,ans,n,k,i,j:longint;
 p:array[0..SIZE]of boolean;
 ch:array[0..SIZE]of longint;

begin
 read(n,col);
 assert((n >= 2) and (n <= 1000));
 assert((col >= 0) and (col <= 1000));
 fillchar(p,sizeof(p),true);
 p[1]:=false;
 // Find primes number
 for i:=2 to n do 
  for j:=2 to trunc(sqrt(i+1)) do
   if(i mod j=0)then begin
     p[i] := false;
     break;
    end;
 k := 0; 
 for i:=2 to n do
  if(p[i])then begin
   inc(k);
   ch[k] := i;
  end;
 // Find Nol'dbax number
 ans := 0;
 for i:=2 to k do 
  if(ch[i] + ch[i-1] + 1 <= n)then
   if(p[ch[i] + ch[i-1] + 1])
    then inc(ans);
 if(ans >= col)
  then writeln('YES')
  else writeln('NO');
end.