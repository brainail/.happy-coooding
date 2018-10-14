int x, y;
int g = gcdex (r, m, x, y);
if (g != 1)
	cout << "no solution";
else
	cout << x;

для любого модуля m:
 a^{\phi(m)-1} \equiv a^{-1} \pmod m, 

для простого модуля m:
 a^{m-2} \equiv a^{-1} \pmod m. 