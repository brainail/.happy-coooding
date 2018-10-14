
int s = m;
while (s > 0) {
	..
	s = (s-1) & m;
}

for (int s=m; ; s=(s-1)&m) {
	...
	if (s==0)  break;
}

for (int m=0; m<(1<<n); ++m)
	for (int s=m; s; s=(s-1)&m)
		

