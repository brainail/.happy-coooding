// Sample input 3, in CPP.

#include <cassert>

long long GetHeight() {
  return 3LL;
}

long long GetWidth() {
  return 3LL;
}

char GetPosition(long long i, long long j) {
  if (i == 2 && j == 0) return '0';
  if (i == 2 && j == 1) return '#';
  if (i == 2 && j == 2) return '#';
  if (i == 1 && j == 0) return '0';
  if (i == 1 && j == 1) return '0';
  if (i == 1 && j == 2) return '0';
  if (i == 0 && j == 0) return '#';
  if (i == 0 && j == 1) return '#';
  if (i == 0 && j == 2) return '0';
  assert(0);
}
