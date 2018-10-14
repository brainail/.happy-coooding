{r+,s+,q+,i+,o-}
{$r-,s-,q-,i-,o+}
const oSize=10000000;
const lenSize=7;
const Size=500000;
var c,a,b:array[0..Size]of int64;
 n,n1,n2,i,j:longint;
 w:int64;
 ch:ansistring;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output0.txt');
 rewrite(output);
 read(n1);
 for i:=1 to n1 do read(c[i]);
 fillchar(a,sizeof(a),0);
 i:=n1; n1:=0;
 while(i>0)do begin
  inc(n1);
  for j:=i-lenSize+1 to i do
   if(j>0)then a[n1]:=a[n1]*10+c[j];
  dec(i,lenSize);
 end;
 read(n2);
 for i:=1 to n2 do read(c[i]);
 fillchar(b,sizeof(b),0);
 i:=n2; n2:=0;
 while(i>0)do begin
  inc(n2);
  for j:=i-lenSize+1 to i do
   if(j>0)then b[n2]:=b[n2]*10+c[j];
  dec(i,lenSize);
 end;
 fillchar(c,sizeof(c),0);
 for i:=1 to n1 do
 for j:=1 to n2 do
  inc(c[i+j-1],a[i]*b[j]);
 n:=n1+n2+5;
 for i:=1 to n do
  if(c[i]>=oSize)then begin
   w:=c[i] div oSize;
   inc(c[i+1],w);
   dec(c[i],w*oSize);
  end;
 while(n>0)and(c[n]=0)do dec(n);
 write(c[n]);
 for i:=n-1 downto 1 do begin
  str(c[i],ch);
  while(length(ch)<lenSize)do ch:='0'+ch;
  write(ch);
 end; 
 close(input);
 close(output);
end.