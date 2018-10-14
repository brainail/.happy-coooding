int numberOf1Bits(int n) {
  int res = 0;
  while (n != 0) {
    n &= (n - 1);
    res++;
  }
  return res;
}
