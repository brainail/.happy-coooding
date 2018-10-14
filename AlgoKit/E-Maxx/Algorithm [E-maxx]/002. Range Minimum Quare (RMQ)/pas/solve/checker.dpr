{$r+,s+,q+,i+,o-}
{$apptype console}
const Size=1010000;
var a,b:array[0..Size]of longint;
 n,x,i:longint;

begin
 assign(input,'input.txt');
 reset(input);
 read(n);
 for i:=1 to n do read(x);
 read(n);
 close(input);

 assign(input,'output.txt');
 reset(input);
 for i:=1 to n do read(a[i]);
 close(input);

 assign(input,'coutput.txt');
 reset(input);
 for i:=1 to n do read(b[i]);
 close(input);

 for i:=1 to n do 
  if(a[i]<>b[i])then begin
   writeln('Wrong Answer');
   writeln('[',i,']');
   writeln;
   while(true) do x:=x; 
  end;
 writeln('Accept Answer');
 writeln;
end.