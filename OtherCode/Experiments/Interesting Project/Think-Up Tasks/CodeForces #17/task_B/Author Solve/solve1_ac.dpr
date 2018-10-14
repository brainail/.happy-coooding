{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
const vSIZE=1010;
const eSIZE=10010;
const Inf=1000000000;
var v,ans,i,x,y,c,m,n:longint;
 d,s,q:array[0..vSIZE]of longint;
 g:record n:longint;
  hd:array[0..vSIZE]of longint;
  pr,f:array[0..eSIZE]of longint;
 end;
 was:array[0..vSIZE]of boolean;

procedure outing(ans:longint);
 begin
  writeln(ans);
  close(input);
  close(output);
  halt;
 end;

procedure addEdge(x,y:longint);
 begin
  inc(g.n);
  g.pr[g.n]:=g.hd[x];
  g.hd[x]:=g.n;
  g.f[g.n]:=y;
 end;

procedure dfs(u:longint);
 var i:longint;
 begin
  was[u]:=true; i:=g.hd[u];
  while(i>0)do begin
   assert(not was[g.f[i]]);
   dfs(g.f[i]);
   i:=g.pr[i];
  end;
 end;

begin
 readln(m);
 assert((m >= 1) and (m <= 1000));
 for i:=1 to m do begin
  read(q[i]);
  assert((q[i] <= 1000000) and (q[i] >= 0));
 end;
 readln(n);
 assert((n >= 0) and (n <= 10000));
 for i:=1 to m do begin
  d[i] := Inf;
  s[i] := -1;
 end;
 for i:=1 to n do begin
  readln(x,y,c);
  assert((x >= 1) and (x <= m));
  assert((y >= 1) and (y <= m));
  assert((c >= 0) and (c <= 1000000));
  assert(q[x] > q[y]);
  if(c < d[y])then begin
   d[y] := c;
   s[y] := x;
  end;
 end;
 fillchar(g,sizeof(g),0);
 ans := 0; v := -1;
 for i:=1 to m do
  if(s[i] <> -1)then begin
   inc(ans, d[i]);
   addEdge(s[i], i);
  end else begin
   if(v <> -1)then outing(-1); 
   v := i;
  end;
 fillchar(was,sizeof(was),0);
 dfs(v);
 for i:=1 to m do assert(was[i]);
end.
