// INCLUDES
#include <cstdlib>
#include <cstdio>
using namespace std;

// TYPEDEFS

// DEFINES

// CONSTS
// const string INPUT_FILE = "input.txt";
// const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES

// MY
const int DLIMIT = 19;
const int MAXC = 300;
const int vd [4][2] = {{0, -1}, {0, +1}, {-1, 0}, {+1, 0}};

bool wasHere [MAXC * 2 + 10][MAXC * 2 + 10];
int wasPoints = 0;

inline int calcDist(int x, int y) {
    x = abs(x), y = abs(y);
    int result = 0;
    while (x > 0 && result <= DLIMIT) result += (x % 10), x /= 10;
    while (y > 0 && result <= DLIMIT) result += (y % 10), y /= 10;
    return result;
}

void move(int cX, int cY) {
    if (calcDist(cX, cY) <= DLIMIT && !wasHere [MAXC + cX][MAXC + cY]) {
        wasHere [MAXC + cX][MAXC + cY] = true, ++ wasPoints;
        for (int i = 0; i < 4; ++ i) move(cX + vd [i][0], cY + vd [i][1]);
    }
}

int runSolution() {
    // memset(wasHere, false, sizeof(wasHere));
    // wasPoints = 0;
    move(0, 0);
    return wasPoints;
}

// MAIN
int main(int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    // freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    printf("%d", runSolution());
    // CODE AREA <=

    return 0;
}