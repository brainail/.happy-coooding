// RMQ, Find Minimum FInd: ~~~~O(1), Build: ~~O(N), Memory: ~~O(N).
{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
uses math;
const Size=1001000;
var mL,mR,a:array[0..Size]of longint;
 f:array[0..Size div 19,0..19]of longint;
 pw:array[0..22]of longint;
 n,i,len,lenSize,k,testcase,l,r,ll,rr,minL,minR,tmp,j:longint;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 read(n);
 for i:=1 to n do read(a[i]);
 lenSize:=trunc(ln(n)/ln(2));
 k:=(n div lenSize)+ord(n mod lenSize>0);
 minL:=a[1]; minR:=a[n];
 for i:=1 to n do begin
  minL:=min(minL,a[i]); minR:=min(minR,a[n-i+1]);
  mL[i]:=minL; mR[n-i+1]:=minR;
  if(i mod lenSize=0)then minL:=a[i+1];
  if((n-i+1) mod lenSize=1)then minR:=a[n-i];
 end;
 for i:=1 to k do f[i][0]:=mR[(i-1)*lenSize+1];
 pw[0]:=1; for i:=1 to lenSize do pw[i]:=pw[i-1]*2;
 for len:=1 to lenSize do
 for i:=1 to k-pw[len]+1 do f[i][len]:=min(f[i][len-1],f[i+pw[len-1]][len-1]);
 read(testcase);
 for i:=1 to testcase do begin
  read(l,r);
  if(l>r)then begin tmp:=l; l:=r; r:=tmp; end;
  ll:=(l div lenSize)+ord(l mod lenSize>0);
  rr:=(r div lenSize)+ord(r mod lenSize>0);
  if(ll=rr)and(l mod lenSize=1)then writeln(mL[r]) else
  if(ll=rr)and(r mod lenSize=0)then writeln(mR[l]) else
  if(ll=rr)then begin minL:=a[l];
   for j:=l to r do minL:=min(minL,a[j]);
   writeln(minL);
  end else begin
   inc(ll); dec(rr); minL:=min(mR[l],mL[r]);
   if(ll<=rr)then len:=trunc(ln(rr-ll+1)/ln(2));
   if(ll<=rr)then minL:=min(minL,min(f[ll][len],f[rr-pw[len]+1][len]));
   writeln(minL);
  end; 
 end;
 close(input);
 close(output);
end.