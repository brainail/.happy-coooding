var b,n,c:int64;

begin
 randomize;
 assign(output,'input.txt');
 rewrite(output);
 b := int64(random(1000000000)) * random(1000000000);
 while(b < 2)do b := int64(random(1000000000)) * random(1000000000);
 n := int64(random(1000000000)) * random(1000000000);
 while(n < 1)do n := int64(random(1000000000)) * random(1000000000); 
 c := random(1000000000) + 1;
 writeln(b,' ',n,' ',c);
 close(output);
end.