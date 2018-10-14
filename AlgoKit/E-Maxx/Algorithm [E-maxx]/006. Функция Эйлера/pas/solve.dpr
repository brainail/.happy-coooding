{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
var n,ans:int64;
 i:longint;
 m:extended;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 read(n);
 ans:=n;
 m:=n+1;
 for i:=2 to trunc(sqrt(m)) do begin
  if(i>n)then break;
  if(n mod i=0)then begin
   while(n mod i=0)do n:=n div i;
   dec(ans,ans div i);
  end;
 end;
 if(n>1)then dec(ans,ans div n);
 writeln(ans);
 close(input);
 close(output);
end.