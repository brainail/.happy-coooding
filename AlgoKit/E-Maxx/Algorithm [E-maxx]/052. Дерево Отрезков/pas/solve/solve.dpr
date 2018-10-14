{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
uses math;
const Size=200000;
type dataTree=record l,r,a,min,s,c:longint; end;
var t:array[0..Size*3]of dataTree;
 nz,n,_,minV,value,doit,l,r:longint;

procedure gen_tree(u,l,r:longint);
 begin
  t[u].l:=l; t[u].r:=r; t[u].min:=0;
  t[u].a:=0; t[u].s:=0; t[u].c:=r-l+1;
  if(l<r)then begin
   gen_tree(u+u,l,(l+r) shr 1);
   gen_tree(u+u+1,((l+r) shr 1)+1,r);
  end;
 end;

procedure modify(u,l,r:longint);
 var x,y:longint;
 begin
  if(t[u].l=l)and(t[u].r=r)then inc(t[u].a,value) else begin
   if(l<=t[u+u].r)then modify(u+u,l,min(t[u+u].r,r));
   if(r>=t[u+u+1].l)then modify(u+u+1,max(l,t[u+u+1].l),r);
   t[u].min:=min(t[u+u].min+t[u+u].a,t[u+u+1].min+t[u+u+1].a);
   t[u].c:=0; x:=t[u+u].r-t[u+u].l+1; y:=t[u+u+1].r-t[u+u+1].l+1;
   if(t[u].min=t[u+u].min+t[u+u].a)then inc(t[u].c,t[u+u].c);
   if(t[u].min=t[u+u+1].min+t[u+u+1].a)then inc(t[u].c,t[u+u+1].c);
   t[u].s:=t[u+u].a*x+t[u+u].s+t[u+u+1].a*y+t[u+u+1].s;
  end;
 end;

function fMin(u,l,r,w:longint):longint;
 var res:longint;
 begin
  if(t[u].l=l)and(t[u].r=r)then begin
   fMin:=w+t[u].min; exit;
  end else begin
   res:=maxlongint;
   if(l<=t[u+u].r)then res:=min(res,fMin(u+u,l,min(t[u+u].r,r),w+t[u+u].a));
   if(r>=t[u+u+1].l)then res:=min(res,fMin(u+u+1,max(l,t[u+u+1].l),r,w+t[u+u+1].a));
   fMin:=res;
  end;
 end;

function fCout(u,l,r,w:longint):longint;
 var res:longint;
 begin
  if(t[u].l=l)and(t[u].r=r)then begin
   if(w+t[u].min=minV)then fCout:=t[u].c else fCout:=0;
   exit;
  end else begin
   res:=0;
   if(l<=t[u+u].r)then res:=res+fCout(u+u,l,min(t[u+u].r,r),w+t[u+u].a);
   if(r>=t[u+u+1].l)then res:=res+fCout(u+u+1,max(l,t[u+u+1].l),r,w+t[u+u+1].a);
   fCout:=res;
  end;
 end;

function fSum(u,l,r,w:longint):longint;
 var res:longint;
 begin
  if(t[u].l=l)and(t[u].r=r)then begin
   fSum:=(r-l+1)*w+t[u].s; exit;
  end else begin
   res:=0;
   if(l<=t[u+u].r)then res:=res+fSum(u+u,l,min(t[u+u].r,r),w+t[u+u].a);
   if(r>=t[u+u+1].l)then res:=res+fSum(u+u+1,max(l,t[u+u+1].l),r,w+t[u+u+1].a);
   fSum:=res;
  end;
 end;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 read(nz,n);
 gen_tree(1,1,n);
 for _:=1 to nz do begin
  read(doit,l,r);
  if(doit=1)then begin // * Find Min (L .. R) * //
   writeln(fMin(1,l,r,t[1].a));
  end else
  if(doit=2)then begin // * Find Sum (L .. R) * //
   writeln(fSum(1,l,r,t[1].a))
  end else
  if(doit=3)then begin // * Find Kol-Min (L .. R) * //
   minV:=fMin(1,l,r,t[1].a);
   writeln(fCout(1,l,r,t[1].a));
  end else
  if(doit=4)then begin // * Add Value (L .. R)* //
   read(value);
   modify(1,l,r);
  end else assert(0<>0);
 end;
 close(input);
 close(output);
end.