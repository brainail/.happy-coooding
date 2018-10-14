{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
uses math;
const Size=200000;
var e:array[0..Size]of record ch,l,r:longint; end;
 doit,nz,n,_,i,value,l,r:longint;

function next(u:longint):longint; begin next:=(u or (u-1))+1; end;
function prev(u:longint):longint; begin prev:=u and (u-1); end;

function fMin(l,r:longint):longint;
 var res,u:longint;
 begin
  res:=min(e[l].ch,e[r].ch);
  u:=l;
  while(next(u)<=r)do begin
   res:=min(res,e[u].r);
   u:=next(u);
  end;
  u:=r;
  while(prev(u)>=l)do begin
   res:=min(res,e[u].l);
   u:=prev(u);
  end;
  fMin:=res;
 end;

procedure modify(i,value:longint);
 var u:longint;
 begin
  e[i].ch:=min(e[i].ch,value);
  u:=i+1;
  while(u<=n)do begin
   e[u].l:=min(e[u].l,value);
   u:=next(u);
  end;
  u:=i-1;
  while(u>0)do begin
   e[u].r:=min(e[u].r,value);
   u:=prev(u);
  end;
 end;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 read(nz,n);
 for i:=1 to n do begin
  e[i].ch:=maxlongint;
  e[i].l:=maxlongint;
  e[i].r:=maxlongint;
 end;
 for _:=1 to nz do begin
  read(doit);
  if(doit=1)then begin // * Find Min (L .. R) * //
   read(l,r);
   writeln(fMin(l,r));
  end else
  if(doit=2)then begin // * Add Value (I) * //
   read(l,value);
   modify(l,value);
  end else assert(0<>0);
 end;
 close(input);
 close(output);
end.