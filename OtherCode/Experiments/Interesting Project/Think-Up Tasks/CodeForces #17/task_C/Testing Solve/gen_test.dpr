const SIZE=10;
var i,n:longint;
begin
 randomize;
 assign(output,'input.txt');
 rewrite(output);
 n := random(SIZE)+1;
 writeln(n);
 for i:=1 to n do write(chr(random(3)+ord('a')));
 close(output);
end.