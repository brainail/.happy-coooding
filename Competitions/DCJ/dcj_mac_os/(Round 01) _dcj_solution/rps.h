// Sample input 3, in CPP.

#include <cassert>

long long GetN() {
  return 28LL;
}

char GetFavoriteMove(long long id) {
  switch ((int)id) {
    case 0: return 'S';
    case 1: return 'R';
    case 2: return 'P';
    case 3: return 'P';
    case 4: return 'S';
    case 5: return 'R';
    case 6: return 'P';
    case 7: return 'P';
    case 8: return 'S';
    case 9: return 'R';
    case 10: return 'P';
    case 11: return 'P';
    case 12: return 'P';
    case 13: return 'P';
    case 14: return 'R';
    case 15: return 'S';
    default: return 'P';
  }
}
