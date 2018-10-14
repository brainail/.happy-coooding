// Sample input 2, in CPP.

#include <cassert>

long long GetNumKms() {
  return 4LL;
}

long long GetTankSize() {
  return 2LL;
}

long long GetGasPrice(long long i) {
  switch ((int)i) {
    case 0: return 1LL;
    case 1: return 2LL;
    case 2: return 4LL;
    case 3: return 3LL;
    default: assert(0);
  }
}
