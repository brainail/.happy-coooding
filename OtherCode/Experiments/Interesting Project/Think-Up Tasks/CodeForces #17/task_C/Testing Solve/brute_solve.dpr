{r-,s-,q-,i-,o+}
{$r+,s+,q+,i+,o-}
{$apptype console}
const SIZE=201;
const HASH_BASE=1000003;
const HASH_SIZE=2000000;
const HASH_SCALE=253;
var hash:record n:longint;
 hd:array[0..HASH_BASE]of longint;
 pr:array[0..HASH_SIZE]of longint;
 st:array[0..HASH_SIZE]of ansistring;
end;
 id,n,i:longint;
 st:ansistring;

function ok(st:ansistring):boolean;
 var i,a,b,c:longint;
 begin
  a := 0; b := 0; c := 0;
  for i:=1 to n do
   if(st[i] = 'a')then inc(a) else
   if(st[i] = 'b')then inc(b) else
   if(st[i] = 'c')then inc(c) else assert(0<>0);
  ok := (abs(a-b) <= 1) and (abs(a-c) <= 1) and (abs(b-c) <= 1); 
 end;

function was(st:ansistring):boolean;
 var x,i:longint;
 begin
  x := 0; 
  for i:=1 to n do 
   x := (x * HASH_SCALE + ord(st[i])) mod HASH_BASE;
  i := hash.hd[x];
  while(i>0)do begin
   if(hash.st[i] = st)then begin
    was := true;
    exit;
   end;
   i := hash.pr[i];
  end; 
  was := false;
  inc(hash.n);
  hash.pr[hash.n] := hash.hd[x];
  hash.hd[x] := hash.n;
  hash.st[hash.n] := st;
 end;

procedure rec(st:ansistring);
 var i:longint;
  node:ansistring;
 begin
  if(was(st))then exit;
  for i:=2 to n do begin
   node := st;
   node[i-1] := node[i];
   rec(node);
   node := st;
   node[i] := node[i-1];
   rec(node);
  end;
 end;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'ok.txt');
 rewrite(output);
 readln(n);
 readln(st);
 fillchar(hash,sizeof(hash),0);
 rec(st);
 id := 0;
 for i:=1 to hash.n do
  if(ok(hash.st[i]))then begin
   inc(id);
   //writeln(id,'. ',hash.st[i]);
  end;
 writeln(id);
 close(input);
 close(output);
end.