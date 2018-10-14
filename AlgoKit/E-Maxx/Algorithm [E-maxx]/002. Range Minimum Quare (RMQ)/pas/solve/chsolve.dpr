{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
uses math;
const Size=1010000;
var l,r,testcase,len,i,lenSize,n,tmp:longint;
 pw:array[0..20]of longint;
 f:array[0..Size,0..19]of longint;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'coutput.txt');
 rewrite(output);
 readln(n);
 for i:=1 to n do read(f[i][0]);
 lenSize:=trunc(ln(n)/ln(2)); pw[0]:=1;
 for i:=1 to lenSize do pw[i]:=pw[i-1]*2;

 for len:=1 to lenSize do
 for i:=1 to n-pw[len]+1 do
  f[i][len]:=min(f[i][len-1],f[i+pw[len-1]][len-1]);

 read(testcase);
 for i:=1 to testcase do begin
  read(l,r);
  if(l>r)then begin tmp:=l; l:=r; r:=tmp; end;
  len:=trunc(ln(r-l+1)/ln(2));
  writeln(min(f[l][len],f[r-pw[len]+1][len]));
 end;
 close(input);
 close(output);
end.