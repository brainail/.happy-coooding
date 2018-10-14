{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
const Size=40000000;
var k,i,j,n:longint;
 p:array[0..Size div 10]of longint;
 us:array[0..Size]of boolean;
begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 read(n);
 k:=0;
 for i:=2 to n do if(not us[i])then begin
  inc(k); p[k]:=i;
  if(i>n div i)then continue;
  j:=i*i;
  while(j<=n)do begin us[j]:=true; inc(j,i); end;
 end;
 close(input);
 close(output);
end.