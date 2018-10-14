// Sample input 2, in CPP.

#include <cassert>

long long GetNumStacks() {
  return 4LL;
}

long long GetStackHeight(long long i) {
  switch ((int)i) {
    case 1: return 1LL;
    case 2: return 2LL;
    case 3: return 5LL;
    case 4: return 1LL;
    default: assert(0);
  }
}
