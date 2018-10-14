{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
const SIZE=100100; {MAX LEN STRING}
const HASH_BASE=1073741823; {HASH MODULO - HASH % HASH_BASE}
const HASH_SCALE=371; {HASH SCALE - HASH_SCALE^0 * x + HASH_SCALE^1 * y ... }
var okB:array[0..SIZE]of boolean; {GOOD or BAD bracket}
 a:record N:longint; A:array[0..SIZE]of longint; end;
 sB:record N:longint; A:array[0..SIZE]of longint; end; {STACK bracket}
 pairB:array[0..SIZE]of longint; {Corresponding closing bracket}
 hB:array[0..SIZE]of longint; {HASH PREFIX STRING}
 SCALE:array[0..SIZE]of longint; {SCALE PREFIX STRING}
 bR:record N:longint; l,r,hB,Id:array[0..SIZE]of longint; end; {All information about right bracket sequence}
 maxIdB:longint;
 
procedure reading_bracket; {Reading bracket}
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
   SCALE[i]:=(int64(SCALE[i-1])*HASH_SCALE) mod HASH_BASE;
   hB[i]:=(int64(hB[i-1])*HASH_SCALE+a.A[i]+2) mod HASH_BASE;
  end; 
 end;

procedure addBracketSequence(l, r, Id : longint); {ADD new right bracket sequence}
 begin
  assert(l < r);
  inc(bR.N);
  bR.l[bR.N]:=l;
  bR.r[bR.N]:=r;
  bR.Id[bR.N]:=Id;
  bR.hB[bR.N]:=(((hB[r]-int64(hB[l])*SCALE[r-l]) mod HASH_BASE)+HASH_BASE) mod HASH_BASE;
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
  endB := -1; idB := Id;
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

procedure divided_into_blocks; {Divided into blocks}
 var i,poss:longint;
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
  while(poss <= a.N)do begin
   if(not okB[poss])then begin {SKIP bad bracket}
    inc(poss);
    continue;
   end;
   assert(pairB[poss] > 0);
   dfsB(poss, poss, pairB[poss], 1); {Deepening in right bracket sequence}
   poss := pairB[poss]+1; 
  end;
 end;

begin
 assign(input,'bracket.in');
 reset(input);
 assign(output,'bracket.out');
 rewrite(output);
 reading_bracket;
 divided_into_blocks;
 close(input);
 close(output);
end.