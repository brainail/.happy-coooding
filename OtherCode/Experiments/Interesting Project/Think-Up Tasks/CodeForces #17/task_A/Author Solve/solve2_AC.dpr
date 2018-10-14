{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
const SIZE=1010;
var col,ans,n,i,j:longint;

function isPrime(x:longint):boolean;
 var i:longint;
 begin
  isPrime:=false;
  for i:=2 to trunc(sqrt(x+1)) do
   if(x mod i = 0)then exit;
  isPrime:=true; 
 end;

begin
 read(n,col);
 assert((n >= 2) and (n <= 1000));
 assert((col >= 0) and (col <= 1000));
 ans := 0;
 // Find primes number & check
 for i:=2 to n do
  if(isPrime(i))then
   for j:=i+1 to n do
    if(isPrime(j))then begin
     if(i+j+1 <= n)then 
      if(isPrime(i+j+1))then inc(ans);
     break;
    end;
 if(ans >= col)
  then writeln('YES')
  else writeln('NO');   
end.