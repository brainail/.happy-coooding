{$r+,s+,q+,i+,o-}
var b:array[0..1000]of ansistring;
 bracket:ansistring;
 i,j,x,y,len:longint;

begin
 randomize;
 assign(output,'bracket.in');
 rewrite(output);
 fillchar(b,sizeof(b),0);
 for i:=1 to 5 do begin
  b[i]:='()';
  for j:=1 to 40 do begin
   x:=random(length(b[i])-1)+1;
   while(not(((b[i][x]='(')and(b[i][x+1]=')')){or ((b[i][x]=')') and (b[i][x+1]=')')) }))do
    x:=random(length(b[i])-1)+1;
   insert('()',b[i],x+1);
  end;
 end;
 bracket := ''; len := 0;
 while(len < 400)do begin
  x := random(5) + 1;
  y := random(len)+1;
  bracket := bracket + b[x];
  //insert(b[x],bracket,y);
  //bracket := bracket + b[x];
  inc(len,length(b[x]));
 end;
 for i:=1 to 77 do 
  insert(')',bracket,random(length(bracket))+1);
 bracket := copy(bracket, 1, 400);
 writeln(bracket);
 close(output);
end.