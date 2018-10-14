{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
const SIZE=2000010;
const BASE=51123987;
var p2,d1,d2:array[0..SIZE]of longint;
 p1:array[0..SIZE]of int64;
 a:array[0..SIZE]of char;
 n,x,l,r,i:longint;
 ans:int64;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 readln(n);
 for i:=1 to n do read(a[i]);
 
 // Find max length pod-palindrome odd length
 l:=-1; r:=-1;
 for i:=1 to n do begin
  if(i>r)then x:=0 else begin 
   if(d1[l+r-i]<r-i)then x:=d1[l+r-i] else x:=r-i;
  end;
  while(i-x>1)and(i+x<n)and(a[i-x-1]=a[i+x+1])do inc(x);
  d1[i] := x;
  if(i+x>r)then begin r:=i+x; l:=i-x; end;
 end;

 // Find max length pod-palindrome !odd length
 l:=-1; r:=-1;
 for i:=1 to n do begin
  if(i+1>r)then x:=-1 else begin
   if(d2[l+r-i-1]<r-i-1)then x:=d2[l+r-i-1] else x:=r-i-1;
  end;
  while(i-x>1)and(i+x+1<n)and(a[i-x-1]=a[i+x+2])do inc(x);
  d2[i] := x; 
  if(i+x+1>r)then begin r:=i+x+1; l:=i-x; end;
 end;

 // <---
 fillchar(p1,sizeof(p1),0);
 for i:=1 to n do begin
  inc(p1[i-d1[i]]); dec(p1[i+1]); // Odd palindrome
  if(d2[i]>=0)then begin inc(p1[i-d2[i]]); dec(p1[i+1]); end; // !Odd palindrome
 end;

 for i:=1 to n+1 do p1[i] := p1[i-1] + p1[i];
 for i:=n downto 1 do p1[i] := p1[i+1] + p1[i]; 

 // --->
 fillchar(p2,sizeof(p2),0);
 for i:=1 to n do begin
  inc(p2[i+d1[i]]); dec(p2[i-1]); // Odd palindrome
  if(d2[i]>=0)then begin inc(p2[i+d2[i]+1]); dec(p2[i]); end; // !Odd palindrome
 end;

 for i:=n downto 0 do p2[i] := p2[i+1] + p2[i];

 ans := 0;
 for i:=1 to n do begin
  ans := ans + d1[i] + 1;
  ans := ans + d2[i] + 1;
  if(ans > BASE)then ans := ans - BASE;
 end;

 if(ans mod 2 = 0)
  then ans := ((ans div 2) * (ans - 1)) mod BASE
  else ans := (ans * ((ans - 1) div 2)) mod BASE; 
 for i:=1 to n do ans := (ans - (p2[i] * p1[i+1])) mod BASE;

 writeln((ans + BASE) mod BASE);
 close(input);
 close(output);
end.