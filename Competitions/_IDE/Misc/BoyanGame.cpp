#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>
#include <cmath>
#include <ctime>
#include <numeric>
#include <iomanip>
#include <complex>
#include <cfloat>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <iterator>
#include <vector>
#include <bitset>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>

using namespace std;

const string IDE_PATH
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/";
const string INPUT_FILE
        = IDE_PATH + "Misc/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "Misc/output.txt";

const int MAXN = 500 + 10;
int n, balls[MAXN], score[MAXN][MAXN];

int main() {
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &balls[i]);
    }

    memset(score, 0, sizeof(score));
    for (int length = 2; length <= n; ++length) {
        for (int left = 0, right = length - 1; right < n; ++left, ++right) {
            score[left][right] = score[left + 1][right];
            for (int middle = left + 1; middle <= right; ++middle) {
                if (balls[left] == balls[middle]) {
                    int removalScore = score[left + 1][middle - 1] + 2 + score[middle + 1][right];
                    score[left][right] = max(score[left][right], removalScore);
                }
            }
        }
    }

    //    1 2 5 3
    // 1:   <--->
    // 1: <--->

    printf("%d", score[0][n - 1]);
}