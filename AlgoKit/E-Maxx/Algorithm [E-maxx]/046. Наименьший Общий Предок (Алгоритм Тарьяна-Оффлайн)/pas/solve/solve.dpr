{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
const Size=201000;
type dataGraph=record n:longint;
 hd,f,pr:array[0..Size]of longint;
end;
var idz,ra,p,acr,ans:array[0..Size]of longint;
 us:array[0..Size]of boolean;
 i,m,nz,x,y:longint;
 g,gz:dataGraph;

procedure addEdge(x,y:longint);
 begin
  inc(g.n);
  g.pr[g.n]:=g.hd[x];
  g.hd[x]:=g.n;
  g.f[g.n]:=y;
 end;

procedure addEdge2(x,y,iz:longint);
 begin
  inc(gz.n);
  gz.pr[gz.n]:=gz.hd[x];
  gz.hd[x]:=gz.n;
  gz.f[gz.n]:=y;
  idz[gz.n]:=iz;
 end;

function fset(u:longint):longint;
 begin
  if(u<>p[u])then p[u]:=fset(p[u]);
  fset:=p[u];
 end;

procedure union(x,y,newp:longint);
 begin
  x:=fset(x); y:=fset(y);
  if(ra[x]>ra[y])then begin
   p[y]:=x; acr[x]:=newp;
  end else begin
   p[x]:=y; acr[y]:=newp;
   inc(ra[y],ord(ra[x]=ra[y]));
  end;
 end;

procedure dfs(u:longint);
 var i,j:longint;
 begin
  p[u]:=u; acr[u]:=u; us[u]:=true; i:=g.hd[u];
  while(i>0)do begin
   if(not us[g.f[i]])then begin
    dfs(g.f[i]);
    union(u,g.f[i],u);
   end;
   i:=g.pr[i];
  end;
  j:=gz.hd[u];
  while(j>0)do begin
   if(us[gz.f[j]])
    then ans[idz[j]]:=acr[fset(gz.f[j])];
   j:=gz.pr[j];
  end;
 end;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 read(m);
 fillchar(g,sizeof(g),0);
 for i:=1 to m-1 do begin
  read(x,y);
  addEdge(x,y);
  addEdge(y,x);
 end;
 fillchar(ra,sizeof(ra),0);
 fillchar(gz,sizeof(gz),0);
 read(nz);
 for i:=1 to nz do begin
  read(x,y);
  addEdge2(x,y,i);
  addEdge2(y,x,i);
 end;
 dfs(1);
 for i:=1 to nz do
  writeln(gz.f[i*2],' , ',gz.f[i*2-1],' ===> ',ans[i]);
 close(input);
 close(output);
end.