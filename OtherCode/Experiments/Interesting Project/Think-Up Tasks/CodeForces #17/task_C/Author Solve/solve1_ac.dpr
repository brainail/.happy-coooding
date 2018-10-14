{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
const SIZE=160;
const BASE=51123987;
var dp:array[0..1,0..SIZE div 3,0..SIZE div 3,0..SIZE]of longint;
 go:array[0..SIZE,0..3]of longint;
 a:array[0..SIZE]of longint;
 n,m,i,x,ans,j,ka,kb,kc,bk,ck,pp,p,g:longint;
 ch:char;

begin
 readln(n);
 assert((n >= 1) and (n <= 150)); 
 for i:=1 to n do begin
  read(ch);
  assert(ch in ['a'..'c']);
  a[i] := ord(ch)-ord('a')+1;
 end;
 // rar
 m := 1;
 for i:=2 to n do
  if(a[i] <> a[m])then begin
   inc(m);
   a[m] := a[i];
  end;
 for i:=m+1 to n do a[i] := 0;

 // find the nearest symbol
 for i:=1 to m do begin
  fillchar(go[i],sizeof(go[i]),0);
  for j:=i to m do
   if(go[i][a[j]] = 0)
    then go[i][a[j]] := j;
 end;

 // dp
 x := 0; dp[0][0][0][1] := 1; ans := 0; g := (n+2) div 3;
 for ka:=0 to g do begin
  for bk:=0 to g do
   for ck:=0 to g do
    for pp:=0 to m do dp[1-x][bk][ck][pp] := 0;
  for kb:=0 to g do
   for kc:=0 to g do
    if(ka+kb+kc <= n)then 
     for p:=1 to m do
      if(dp[x][kb][kc][p] > 0)then begin
       if(go[p][1]>0)then inc(dp[1-x][kb][kc][go[p][1]], dp[x][kb][kc][p]);
       if(dp[1-x][kb][kc][go[p][1]] > BASE)then dec(dp[1-x][kb][kc][go[p][1]], BASE);
       if(go[p][2]>0)then inc(dp[x][kb+1][kc][go[p][2]], dp[x][kb][kc][p]);
       if(dp[x][kb+1][kc][go[p][2]] > BASE)then dec(dp[x][kb+1][kc][go[p][2]], BASE);
       if(go[p][3]>0)then inc(dp[x][kb][kc+1][go[p][3]], dp[x][kb][kc][p]);
       if(dp[x][kb][kc+1][go[p][3]] > BASE)then dec(dp[x][kb][kc+1][go[p][3]], BASE);
      end;
  for bk:=ka-1 to ka+1 do
   for ck:=ka-1 to ka+1 do
    if(ka+bk+ck=n)and(abs(ka-bk)<=1)and(abs(ka-ck)<=1)and(abs(bk-ck)<=1)and(bk>=0)and(ck>=0)then
     for pp:=1 to m do begin
      ans := ans + dp[x][bk][ck][pp];
      if(ans > BASE)then dec(ans, BASE);
     end; 
  x := 1 - x;     
 end;
 writeln(ans);
 close(input);
 close(output);
end.