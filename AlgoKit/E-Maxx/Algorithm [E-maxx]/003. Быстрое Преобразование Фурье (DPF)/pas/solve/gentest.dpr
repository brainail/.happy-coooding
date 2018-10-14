{$r-,s-,q-,i-,o+}
const aSize=500000;
const bSize=500000;
var i:longint;
begin
 randomize;
 assign(output,'input.txt');
 rewrite(output);
 writeln(aSize);
 writeln(random(9)+1);
 for i:=2 to aSize do writeln(random(10));
 writeln(bSize);
 writeln(random(9)+1);
 for i:=2 to bSize do writeln(random(10));
 close(output);
end.