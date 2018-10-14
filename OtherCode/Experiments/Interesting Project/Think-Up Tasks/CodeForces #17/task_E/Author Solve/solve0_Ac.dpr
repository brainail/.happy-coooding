{$R-,S-,Q-,I-,O+}
const md = 51123987;
      inf = round(9e18);
var
  tot,n,i,mid: longint;
  ans,sum: int64;
  s: array [0..2000010] of char;
  a,b,p: array [0..2000010] of longint;
begin
  readln(n);
  for i:=1 to n do read(s[i]);
  s[0]:=#1; s[n+1]:=#2;
  fillchar(a,sizeof(a),0);
  fillchar(b,sizeof(b),0);
  mid:=1;
  for i:=1 to n do
  begin
    if p[mid]+mid <= i then p[i]:=0 else
    begin
      p[i]:=p[2*mid-i];
      if p[i] > p[mid]+mid-i then p[i]:=p[mid]+mid-i;
    end;
    while s[i-p[i]] = s[i+p[i]] do inc(p[i]);
    if p[i]+i > p[mid]+mid then mid:=i;
    inc(a[i-p[i]+1]); dec(a[i+1]);
    inc(b[i]); dec(b[i+p[i]]);
  end;
  mid:=1; p[1]:=0;
  for i:=1 to n-1 do
  begin
    if p[mid]+mid <= i+1 then p[i]:=0 else
    begin
      p[i]:=p[2*mid-i];
      if p[i] > p[mid]+mid-i-1 then p[i]:=p[mid]+mid-i-1;
    end;
    while s[i-p[i]] = s[i+p[i]+1] do inc(p[i]);
    if p[i]+i > p[mid]+mid then mid:=i;
    inc(a[i-p[i]+1]); dec(a[i+1]);
    inc(b[i+1]); dec(b[i+p[i]+1]);
  end;
  for i:=1 to n do inc(a[i],a[i-1]);
  for i:=1 to n do inc(b[i],b[i-1]);
  tot:=0;
  for i:=1 to n do tot:=(tot+a[i]) mod md;
  ans:=(int64(tot-1)*tot div 2) mod md;
  sum:=0;
  for i:=1 to n do
  begin
    ans:=ans-int64(sum)*a[i];
    if ans < -inf then ans:=ans mod md;
    inc(sum,b[i]);
    if sum >= md then dec(sum,md);
  end;
  ans:=ans mod md;
  if ans < 0 then inc(ans,md);
  writeln(ans);
end.