{r-,s-,q-,i-,o+}
{$r-,s+,q-,i+,o-}
{$m 9999999}
{Memory: O(N * log(N))}
{Time: O(N * log(N))}
{Solution Writer: Malyshev Yegor (brainail)}
const SIZE=100100; {MAX LEN STRING}
const HASH_SCALE=371; {HASH SCALE - HASH_SCALE^0 * x + HASH_SCALE^1 * y ... }
var okB:array[0..SIZE]of boolean; {GOOD or BAD bracket}
 a:record N:longint; A:array[0..SIZE]of longint; end;
 sB:record N:longint; A:array[0..SIZE]of longint; end; {STACK bracket}
 pairB:array[0..SIZE]of longint; {Corresponding closing bracket}
 hB:array[0..SIZE]of longint; {HASH PREFIX STRING}
 SCALE:array[0..SIZE]of longint; {SCALE PREFIX STRING}
 cB:array[0..SIZE]of longint; {COST symbols for prefix}
 bR:record N:longint; l,r,hB,Id:array[0..SIZE]of longint; end; {All information about right bracket sequence}
 c,idB,d,k,id,t,dd,cc,idd,q,idQ,lcp:array[0..SIZE]of longint; {SUFF MASS}
 list:array[0..SIZE]of record prev,next:longint; end; {Two linked list}
 sf:array[0..20,0..SIZE]of longint; {SUFF MASS}
 i,maxIdB,len,stp,left,right,maxCost:longint;
 fSeq:boolean;
 
procedure Reading_bracket; {Reading bracket}
 var bracket:ansistring;
  i:longint;
 begin
  readln(bracket);
  fillchar(a,sizeof(a),0);
  for i:=1 to length(bracket) do
   if(bracket[i] in ['(',')'])then begin
    inc(a.N); a.A[a.N]:=ord(bracket[i]='(')-ord(bracket[i]=')');
   end;
  fillchar(hB,sizeof(hB),0);
  fillchar(SCALE,sizeof(SCALE),0);
  SCALE[0]:=1;
  for i:=1 to a.N do begin
   SCALE[i]:=int64(SCALE[i-1])*HASH_SCALE;
   hB[i]:=int64(hB[i-1])*HASH_SCALE+a.A[i]+2;
  end; 
 end;

procedure addBracketSequence(l, r, Id : longint); {ADD new right bracket sequence}
 begin
  assert(l < r);
  inc(bR.N);
  bR.l[bR.N]:=l;
  bR.r[bR.N]:=r;
  bR.Id[bR.N]:=Id;
  bR.hB[bR.N]:=hB[r]-int64(hB[l])*SCALE[r-l];
 end;

procedure dfsB(poss, l, r, Id : longint);
 var endB, idB : longint;
 begin
  if(poss = r)then exit; {Reached the end of the interval}
  if(poss = l)then begin {New right bracket sequence}
   assert(pairB[poss] > 0);
   addBracketSequence(poss, pairB[poss], Id);
  end;
  if(l + 1 = r)then exit; {Reached the zero depth}
  idB := Id;
  if(poss = l)then begin
   maxIdB := maxIdB + 1;
   idB := maxIdB;
  end;
  if(poss = l)then begin {Deepening}
   assert(pairB[l + 1] > 0);
   endB := pairB[l + 1];
   dfsB(l + 1, l + 1, pairB[l + 1], IdB);
  end else begin
   assert(pairB[poss] > 0);
   endB := pairB[poss];
   dfsB(poss, poss, pairB[poss], IdB);
  end;
  dfsB(endB + 1, l, r, IdB ); {Next right bracket sequence}
 end;

procedure Divided_into_blocks; {Divided into blocks}
 var i,poss,pmaxIdB:longint;
 begin
  fillchar(sB,sizeof(sB),0); {STACK bracket}
  fillchar(okB,sizeof(okB),0); {GOOD or BAD bracket}
  fillchar(pairB,sizeof(pairB),0); {Corresponding closing bracket}
  fillchar(bR,sizeof(bR),0); {All information about right bracket sequence}
  for i:=1 to a.N do
   if(a.A[i] = +1)then begin {Put bracket in STACK}
    inc(sB.N);
    sB.A[sB.N]:=i;
   end else begin
    if(sB.N > 0)then begin {Chekup correct works in TOP STACK}
     assert(a.A[sB.A[sB.N]] = +1);
     okB[i]:=true;
     okB[sB.A[sB.N]]:=true;
     pairB[sB.A[sB.N]]:=i;
     sB.A[sB.N]:=0;
     dec(sB.N);
    end else okB[i]:=false; {BAD bracket}
   end;
  for i:=1 to sB.N do okB[sB.A[i]]:=false; {BAD bracket}
  maxIdB:=1; {MAXIMUM ID sequence bracket}
  poss:=1; {Current position}
  pmaxIdB:=1;
  while(poss <= a.N)do begin
   if(not okB[poss])then begin {SKIP bad bracket}
    inc(maxIdB);
    pmaxIdB:=maxIdB;
    inc(poss);
    continue;
   end;
   assert(pairB[poss] > 0);
   dfsB(poss, poss, pairB[poss], pmaxIdB); {Deepening in right bracket sequence}
   poss := pairB[poss]+1; 
  end;
  poss:=1;
  while(poss <= a.N)do begin
   if(not okB[poss])then begin {SKIP bad bracket}
    inc(poss);
    continue;
   end;
   i := poss;
   while(i <= a.N)and(okB[i])do inc(i);
   if(i - poss > maxCost)then begin
    maxCost := i - poss;
    left := poss;
    right := i-1;
   end;
   poss := i;
  end;
 end;

procedure sortB(l,r:longint);
 var i,j,tmp,w:longint;
 begin
  if(l>=r)then exit;
  i:=l; j:=r; w:=bR.hB[l+random(r-l+1)];
  repeat
   while(w>bR.hB[i])do inc(i);
   while(w<bR.hB[j])do dec(j);
   if(i>j)then break;
   tmp:=bR.l[i]; bR.l[i]:=bR.l[j]; bR.l[j]:=tmp;
   tmp:=bR.r[i]; bR.r[i]:=bR.r[j]; bR.r[j]:=tmp;
   tmp:=bR.Id[i]; bR.Id[i]:=bR.Id[j]; bR.Id[j]:=tmp;
   tmp:=bR.hB[i]; bR.hB[i]:=bR.hB[j]; bR.hB[j]:=tmp;
   inc(i); dec(j);
  until(i>j);
  sortB(l,j); sortB(i,r);
 end;
 
procedure sortB2(l,r:longint);
 var i,j,tmp,wL,wId,u:longint;
 begin
  if(l>=r)then exit;
  i:=l; j:=r; u:=l+random(r-l+1); wId:=bR.Id[u]; wL:=bR.l[u];
  repeat
   while(wId>bR.Id[i])or((wId=bR.Id[i])and(wL>bR.l[i]))do inc(i);
   while(wId<bR.Id[j])or((wId=bR.Id[j])and(wL<bR.l[j]))do dec(j);
   if(i>j)then break;
   tmp:=bR.l[i]; bR.l[i]:=bR.l[j]; bR.l[j]:=tmp;
   tmp:=bR.r[i]; bR.r[i]:=bR.r[j]; bR.r[j]:=tmp;
   tmp:=bR.Id[i]; bR.Id[i]:=bR.Id[j]; bR.Id[j]:=tmp;
   tmp:=bR.hB[i]; bR.hB[i]:=bR.hB[j]; bR.hB[j]:=tmp;
   inc(i); dec(j);
  until(i>j);
  sortB2(l,j); sortB2(i,r);
 end;

procedure Union_blocks_bracket; {Union blocks bracket}
 var phB,chB,i,j,idR:longint;
 begin
  sortB(1,bR.N); {Sort blocks right bracket sequence}
  phB:=bR.hB[1];
  if(bR.N>0)then bR.hB[1]:=1;
  for i:=2 to bR.N do begin {Compress characters hash}
   chB:=bR.hB[i];
   bR.hB[i]:=bR.hB[i-1]+ord(chB<>phB);
   phB:=chB;
  end;
  sortB2(1,bR.N); {Sort2 blocks right bracket sequence}
  i:=1; idR:=bR.N;
  fillchar(c,sizeof(c),0); {Getting Started SUFF MASS}
  fillchar(idB,sizeof(idB),0);
  fillchar(cB,sizeof(cB),0);
  while(i <= bR.N)do begin
   j:=i;
   while(j <= bR.N)and(bR.Id[j] = bR.Id[i])do begin
    inc(len);
    c[len] := bR.hB[j];
    cB[len] := bR.r[j] - bR.l[j] + 1;
    idB[len] := j;
    inc(j);
   end;
   i:=j;
   inc(len); inc(idR);
   c[len] := idR;
   cB[len] := 0;
   idB[len] := -1;
  end;
  for i:=2 to len do cB[i] := cB[i-1] + cB[i]; 
  assert(idR <= SIZE);
 end;

procedure radixSort; {Radix sort}
 var i:longint;
 begin
  for i:=0 to len do begin k[i]:=0; t[i]:=0; idd[i]:=0; end;
  for i:=1 to len do inc(t[d[i]]);
  for i:=1 to len do k[i]:=k[i-1]+t[i-1];
  for i:=1 to len do begin
   inc(k[d[i]]); dd[k[d[i]]]:=d[i]; cc[k[d[i]]]:=c[i]; idd[k[d[i]]]:=i; 
  end;
  for i:=0 to len do begin k[i]:=0; t[i]:=0; id[i]:=0; end;
  for i:=1 to len do inc(t[cc[i]]);
  for i:=1 to len do k[i]:=k[i-1]+t[i-1];
  for i:=1 to len do begin
   inc(k[cc[i]]); d[k[cc[i]]]:=dd[i]; c[k[cc[i]]]:=cc[i]; id[k[cc[i]]]:=idd[i];
  end;
 end;

function Find_lcp(i,j:longint):longint; {MAXIMUM EQUAL symbols in suffix I & J}
 var x,Res_lcp:longint;
 begin
  Res_lcp := 0;
  for x:=stp downto 0 do
   if(sf[x][i]=sf[x][j])then begin
    inc(Res_lcp,1 shl x);
    inc(i,1 shl x);
    inc(j,1 shl x);
   end;
  Find_lcp := Res_lcp; 
 end;

procedure sort(l,r:longint);
 var i,j,u,wQ,wId,tmp:longint;
 begin
  if(l>=r)then exit;
  i:=l; j:=r; u:=l+random(r-l+1); wQ:=q[u]; wId:=idQ[u];
  repeat
   while(wQ<q[i])or((wQ=q[i])and(wId>idQ[i]))do inc(i);
   while(wQ>q[j])or((wQ=q[j])and(wId<idQ[j]))do dec(j);
   if(i>j)then break;
   tmp:=idQ[i]; idQ[i]:=idQ[j]; idQ[j]:=tmp;
   tmp:=q[i]; q[i]:=q[j]; q[j]:=tmp;
   inc(i); dec(j);
  until(i>j);
  sort(l,j); sort(i,r);
 end;

procedure Suff_massive; {SUFF MASS}
 var p,i,l,r:longint;
 begin
  p:=0; stp:=0;
  repeat
   for i:=1 to len do
    if(i+p>len)then d[i]:=0 else d[i]:=c[i+p];
   radixSort;
   cc[id[1]]:=1;
   for i:=2 to len do
    cc[id[i]]:=cc[id[i-1]]+ord((c[i]<>c[i-1])or(d[i]<>d[i-1]));
   for i:=1 to len do begin c[i]:=cc[i]; sf[stp][i]:=c[i]; end;
   if(p+1>len)then break;
   p:=p*2+ord(p=0); inc(stp);
  until(false);
  for i:=1 to len - 1 do begin
   lcp[i] := Find_lcp(id[i],id[i+1]); {LCP}
   q[i] := cB[id[i] + lcp[i] - 1] - cB[id[i] - 1]; {COST for this LCP}
   idQ[i] := i;
  end;
  fillchar(list,sizeof(list),0); {Find answer - two linked list}
  for i:=1 to len-1 do begin
   list[i].prev := i-1; list[i].next := i+1;
  end;
  sort(1,len-1);
  for i:=1 to len-1 do begin
   l := list[idQ[i]].prev + 1;
   r := list[idQ[i]].next - 1;
   if((r - l + 2) * q[i] > maxCost)then begin
    maxCost := (r - l + 2) * q[i];
    left := id[idQ[i]];
    right := id[idQ[i]] + lcp[idQ[i]] - 1; 
    fSeq := false;
   end;
   list[list[idQ[i]].prev].next:=list[idQ[i]].next;
   list[list[idQ[i]].next].prev:=list[idQ[i]].prev;
  end;
 end;

begin
 assign(input,'bracket.in');
 reset(input);
 assign(output,'bracket.out');
 rewrite(output);

 {randomize;
 for left:=1 to 100000 do
  if(random(2)=1)then write('(') else write(')');
 halt;       }

 maxCost := 0; left := 0; right := -1; fSeq := true;
 Reading_bracket; {Reading bracket}
 Divided_into_blocks; {Divided into blocks}
 Union_blocks_bracket; {Union blocks bracket}
 Suff_massive; {SUFF MASS}
 writeln(maxCost);
 if(fSeq)then begin
  while(left <= right)do begin
   if(a.A[left] = -1)then write(')') else write('(');
   left := left + 1;
  end;
 end else begin
  while(left <= right)do begin
   for i:=bR.l[idB[left]] to bR.r[idB[left]] do 
    if(a.A[i] = -1)then write(')') else write('(');
   inc(left);
  end;
 end; 
 close(input);
 close(output);
end.