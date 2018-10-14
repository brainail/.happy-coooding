{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
var res,b,n,c,bb:int64;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'ok.txt');
 rewrite(output);
 read(b,n,c);
 res:=1; dec(n); bb:=(b-1) mod c; b:=b mod c;
 while(n>0)do 
  if(n mod 2=1)then begin
   res:=(res*b) mod c;
   dec(n);
  end else begin
   b:=(b*b) mod c;
   n:=n div 2;
  end;
 res:=(res*bb) mod c;
 if(res=0)then res:=c;
 writeln(res);
 close(input);
 close(output);
end.