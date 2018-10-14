// RMQ, Find Minimum FInd: ~~~~O(1), Build: ~~O(Nlog(n)), Memory: ~~O(Nlog(n)).
{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
uses math;
const Size=101000;
var l,r,testcase,len,i,lenSize,n,tmp:longint;
 pw:array[0..18]of longint;
 f:array[0..Size,0..18]of longint;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 for i:=1 to 300000000 do n:=n;
 halt;
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