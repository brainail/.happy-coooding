{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
const SIZE=2000010;
var s,ans,si:int64;
 f:array[0..SIZE]of longint;
 n,i,l,r:longint;
 st:ansistring;
 a:array[0..SIZE]of longint;
begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 readln(n);
 readln(st);
 for i:=1 to n do begin
  a[i] := ord(st[i]);
 end;
 fillchar(f,sizeof(f),0);
 ans := 0; si := 0;
 for i:=1 to n do begin
  l:=i+1; r:=i-1; s := si;
  while(l > 1)and(r < n)and(a[l-1] = a[r+1])do begin
   dec(l); inc(r); inc(s,f[l]); inc(ans,s); inc(f[r]); inc(s); inc(si,ord(r>i));
  end;
  l:=i+1; r:=i; s := si;
  while(l > 1)and(r < n)and(a[l-1] = a[r+1])do begin
   dec(l); inc(r); inc(s,f[l]); inc(ans,s); inc(f[r]); inc(s); inc(si,ord(r>i));
  end;
  dec(si,f[i+1]);
  if(ans > 51123987)then ans := ans - 51123987;
 end;
 writeln(ans mod 51123987);
 close(output);
end.
