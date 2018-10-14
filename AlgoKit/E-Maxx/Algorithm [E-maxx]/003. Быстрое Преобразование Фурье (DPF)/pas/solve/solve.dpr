{$r-,s-,q-,i-,o+}
{r+,s+,q+,i+,o-}
{$m 8000000}
uses math;
const Size=530000;
type dataComplex=record r,i:extended; end;
type dataMass=array[0..Size]of longint;
type dataCMass=array[0..Size]of dataComplex;
var fa,fb:dataCMass;
 a,b,ans:dataMass;
 pw2:array[0..32]of longint;
 n,i,n1,n2,ost:longint;

function mylCpx(a,b:dataComplex):dataComplex; // Умножение комплексных чисел.
 var res:dataComplex;
 begin
  res.r:=a.r*b.r-a.i*b.i;
  res.i:=a.r*b.i+a.i*b.r;
  mylCpx:=res;
 end;

function sumCpx(a,b:dataComplex):dataComplex; // Сложение комплексных чисел.
 var res:dataComplex;
 begin
  res.r:=a.r+b.r;
  res.i:=a.i+b.i;
  sumCpx:=res;
 end;

function subCpx(a,b:dataComplex):dataComplex; // Вычитание комплексных чисел.
 var res:dataComplex;
 begin
  res.r:=a.r-b.r;
  res.i:=a.i-b.i;
  subCpx:=res;
 end;

procedure fft(var a:dataCMass; inv:longint);
 var i,j,q,bitN,len:longint;
  tmp,w,wpw,u,v:dataComplex;
  ang:extended;
 begin
  bitN:=0;
  while(pw2[bitN]<n)do inc(bitN);
  for i:=0 to n-1 do begin // Сортируем массив так,что бы не использовать рекурсию.
   j:=0;
   for q:=0 to bitN-1 do // I - позицию меняем с позицией J - обратная битовая запись I.
    if(i and pw2[q]>0)then j:=j or pw2[bitN-q-1];
   if(i<j)then begin
    tmp:=a[i];
    a[i]:=a[j];
    a[j]:=tmp;
   end; 
  end;
  len:=2;
  while(len<=n)do begin // Длина шага
   ang:=2*pi/len*inv;
   wpw.r:=cos(ang); wpw.i:=sin(ang);
   i:=0;
   while(i<n)do begin  // Считаем текущее DPF.
    w.r:=1; w.i:=0;
    for j:=0 to (len shr 1)-1 do begin
     u:=a[i+j]; v:=mylCpx(a[i+j+(len shr 1)],w);
     a[i+j]:=sumCpx(u,v);
     a[i+j+(len shr 1)]:=subCpx(u,v);
     w:=mylCpx(w,wpw);
    end;
    inc(i,len);
   end;
   len:=len*2;
  end;
  if(inv<0)then // Если это обратное DPF, не забываем всё поделить на N.
   for i:=0 to n-1 do begin
    a[i].r:=a[i].r/n;
    a[i].i:=a[i].i/n;
   end;
 end;

procedure multiply(a,b:dataMass; var ans:dataMass);
 var i:longint;
 begin
  fillchar(fa,sizeof(fa),0);
  fillchar(fb,sizeof(fb),0);
  for i:=0 to n1-1 do fa[i].r:=a[i];
  for i:=0 to n2-1 do fb[i].r:=b[i];
  fft(fa,+1); fft(fb,+1); // Находим DPF для обоих многочленов,чисел
  for i:=0 to n-1 do fa[i]:=mylCpx(fa[i],fb[i]);
  fft(fa,-1); // Считаем обратное DPF,это и есть результат
  for i:=0 to n-1 do ans[i]:=trunc(fa[i].r+0.5); // Забираем целую часть для чисел.
 end;

begin
 assign(input,'input.txt');
 reset(input);
 assign(output,'output.txt');
 rewrite(output);
 pw2[0]:=1;
 for i:=1 to 30 do pw2[i]:=pw2[i-1]*2;
 read(n1);
 for i:=0 to n1-1 do read(a[n1-i-1]); // Такое чтение для чисел.
 read(n2);
 for i:=0 to n2-1 do read(b[n2-i-1]); // Для многочлена наооборот
 n:=1;
 while(n<max(n1,n2))do n:=n*2; // Делаем массивы равной длины, Len = 2^x.
 n:=n*2;
 multiply(a,b,ans); // Функция умножения за ~n*log(n), DPF
 ost:=0;
 for i:=0 to n-1 do begin  // Переносим разряды
  inc(ans[i],ost);
  ost:=ans[i] div 10;
  ans[i]:=ans[i] mod 10;
 end;
 while(n>0)and(ans[n]=0)do dec(n);
 for i:=n downto 0 do write(ans[i]); // Вывод, для многочлена наооборот.
 close(input);
 close(output);
end.