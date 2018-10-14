const nSize=100000;
const testcaseSize=1000000;
const valSize=20;
var i:longint;
begin
 randomize;
 assign(output,'input.txt');
 rewrite(output);
 writeln(nSize);
 for i:=1 to nSize do writeln(random(valSize)+1);
 writeln(testcaseSize);
 for i:=1 to testcaseSize do writeln(random(nSize)+1,' ',random(nSize)+1);
 close(output);
end.