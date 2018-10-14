{$r-,s-,q-,i-,o+}
{$apptype console}
var ch1,ch2:ansistring;
 f0,len1,len2,i:longint;

begin
 assign(input,'output.txt');
 reset(input);
 readln(ch1);
 close(input);

 assign(input,'output0.txt');
 reset(input);
 readln(ch2);
 close(input);

 len1:=length(ch1);
 len2:=length(ch2);
 f0:=0;
 if(len1<>len2)then f0:=-1 else
 for i:=1 to len1 do
  if(ch1[i]<>ch2[i])then begin
   f0:=i;
   break;
  end;
 if(f0=0)then writeln('Equal 100%') else begin
  writeln('Wrong Ans');
  if(f0<0)then writeln('Len1 <> Len2') else
  writeln('Different Char in Position = ',f0);
  writeln;
  while(true)do begin end;
 end;
end.