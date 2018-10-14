{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
var x,y,a,b,gcd:int64;

function euclid(a,b:int64; var x,y:int64):int64;
 var _x,_y:int64;
 begin
  if(a=0)then begin x:=0; y:=1; euclid:=b; exit; end;
  euclid:=euclid(b mod a,a,_x,_y);
  x:=_y-(b div a)*_x;
  y:=_x;
 end;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 read(a,b);
 gcd:=euclid(a,b,x,y);
 writeln(a,' * ',x,' + ',b,' * ',y,' = ',gcd);
 close(input);
 close(output);
end.