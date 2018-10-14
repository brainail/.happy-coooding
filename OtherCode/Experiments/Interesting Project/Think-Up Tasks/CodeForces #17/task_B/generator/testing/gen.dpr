{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
{$apptype console}

// parasmtr(1) - Left SIZE vers
// parasmtr(2) - Right SIZE vers
// parasmtr(3) - Left SIZE edges
// parasmtr(4) - Right SIZE edges
// parasmtr(5) - Up SIZE qualification
// parasmtr(6) - Up SIZE cost
// parasmtr(7) - SIZE randseed

var was:array[0..1000010]of boolean;
 q,id:array[0..10010]of longint;
 tmp,j,m,n,i,x,y,Lm,Rm,Ln,Rn,code,qS,qC,qR:longint;

begin
 val(paramstr(1),Lm,code);
 val(paramstr(2),Rm,code);
 val(paramstr(3),Ln,code);
 val(paramstr(4),Rn,code);
 val(paramstr(5),qS,code);
 val(paramstr(6),qC,code);
 val(paramstr(7),qR,code);
 randseed := qR;
 m := Lm + random(Rm - Lm + 1);
 n := Ln + random(Rn - Ln + 1);
 if(m = 1)then n := 0;
 writeln(m);
 fillchar(was,sizeof(was),0);
 for i:=1 to m do begin
  q[i] := random(qS+1)+1;
  while(was[q[i]])do q[i] := random(qS+1)+1;
  was[q[i]] := true;
  write(q[i]);
  if(i < m)then write(' ');
 end;
 writeln;
 if(n < m - 1)then n := m - 1;
 writeln(n);
 if(m > 100)then begin
  dec(n, m-1);
  for i:=1 to m do id[i] := i;
  for i:=1 to m do 
   for j:=i+1 to m do 
    if(q[id[i]] < q[id[j]])then begin
     tmp:=id[i]; id[i]:=id[j]; id[j]:=tmp;
    end;
  for i:=1 to m-1 do writeln(id[i],' ',id[i+1],' ',random(qC+1)+1);
 end;
 for i:=1 to n do begin
  x := random(m)+1;
  y := random(m)+1;
  while(q[x] <= q[y])do begin
   x := random(m)+1;
   y := random(m)+1;
  end;
  write(x,' ',y,' ',random(qC+1)+1);
  writeln;
 end;
end.