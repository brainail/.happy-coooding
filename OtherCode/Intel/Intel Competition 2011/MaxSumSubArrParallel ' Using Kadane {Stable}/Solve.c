#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
// #include <ctime>
// #include <iostream>
// #include <cmath>
// using namespace std;

// defines
#define __MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define __MAX(X, Y) ((X) > (Y) ? (X) : (Y))

// Maximum field size
// const int maxColumn = 20000 + 10;
#define maxColumn 20010

// Number of threads
// const int maxNumberOfThreads = 100;
#define maxNumberOfThreads 100
int numberOfThreads = 32;

// Sum in column
int sumColumn[maxNumberOfThreads][maxColumn];

// Cur answer for function
int maxFuncSum[maxColumn];
int upFuncI[maxColumn];
int leftFuncJ[maxColumn];
int downFuncI[maxColumn];
int rightFuncJ[maxColumn];

// Field size
int N, M;
int MAXN, MAXM;

// Parameters to generate
int a, b, m, seed0, mean, rem;
short rotateMatrix;

// Answer
int maxSum, leftJ, rightJ, upI, downI;

// Number of tests
int numberOfTestCase;

// Field
int ** board;

// Get Time
static inline size_t curTime() {
    struct timeval now_tv;
    gettimeofday( &now_tv, NULL );
    return (size_t)now_tv.tv_sec * 1000 + (size_t)now_tv.tv_usec / 1000;
    // return 0;
}

// Generate a new value
int PRNG(int seed, int a, int b, int m)
{
    return (a * seed + b) % m;
}

// Maximum size of the field
void maxFieldSize() 
{
    MAXN = MAXM = 0;
    for(int it = 0; it < numberOfTestCase; ++ it) 
    {
        scanf("%d %d %d %d %d %d", &N, &M, &seed0, &a, &b, &m);
        if(__MIN(N, M) > MAXN) MAXN = __MIN(N, M);
        if(__MAX(N, M) > MAXM) MAXM = __MAX(N, M);
    }
}

// The generation of matrix elements
void generatingOfMatrix()
{
    int seed = seed0;
    int dstSize = N * M;
    int sum = 0;
    rotateMatrix = 0;

    if(N <= M) {
        for(int i = 0; i < N; ++ i) 
            for(int j = 0; j < M; ++ j) 
            {
                seed = PRNG(seed, a, b, m);
                board[i][j] = seed;
                sum += seed;
            }
    } 
    else 
    {
        rotateMatrix = 1;
        for(int i = 0; i < N; ++ i)
            for(int j = 0; j < M; ++ j)
            {
                seed = PRNG(seed, a, b, m);
                board[j][N - i - 1] = seed;
                sum += seed;
            }
        int temp = N;
        N = M;
        M = temp;
    }

    mean = sum / (signed) dstSize;
    rem = sum - mean * (signed) dstSize;
    mean += (rem * 2 > (signed) dstSize) ? (1) : (0);
    mean -= (rem * 2 < -(signed) dstSize) ? (1) : (0);

    // Initialize the initial answer
    maxSum = board[0][0] - mean;
    upI = 0, leftJ = 0;
    downI = 0, rightJ = 0;

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
        {
            board[i][j] -= mean;
            if(board[i][j] > maxSum)
            {
                maxSum = board[i][j];
                upI = i, leftJ = j;
                downI = i, rightJ = j;
            }
        }
}

int main(int numberOfArgumet, char * args[])
{
    size_t timeStart = curTime();	

    // numberOfThreads = omp_get_num_procs();
    numberOfThreads = omp_get_max_threads();

    printf("Number of threads: %d\n", numberOfThreads);
    // cout << numberOfArgumet << endl;

    // args = new char * [3];
    // numberOfArgumet = 3;
    // args[1] = "input.txt";
    // args[2] = "output.txt";

    // Error, wrong data
    if(numberOfArgumet < 3) 
    {
        printf("Check the number of parameters");
        return 0;
    }

    // Open input / output
    freopen(args[1], "r", stdin);
    freopen(args[2], "w", stdout);

    // How many tests
    scanf("%d", &numberOfTestCase);

    // Maximum size of the field
    maxFieldSize();

    // Creation of the matrix
    board = (int **) malloc(MAXN * sizeof(int *));
    for(int i = 0; i < MAXN; ++ i) 
        board[i] = (int *) malloc(MAXM * sizeof(int));

    // Reopen input
    freopen(args[1], "r", stdin);

    // How many tests again
    scanf("%d", &numberOfTestCase);

    // Loop tests
    for(int it = 0; it < numberOfTestCase; ++ it) 
    {
        // Read the parametrs for generating 
        scanf("%d %d %d %d %d %d", &N, &M, &seed0, &a, &b, &m);

        // The generation of matrix elements
        generatingOfMatrix();

        // Calculation of answer
        #pragma omp parallel for num_threads(numberOfThreads) 
        for(int curIndex = 0; curIndex < N; ++ curIndex)
        {
            // Calculation of the current answer

            // Get ID
            int indexThread = omp_get_thread_num();

            // Some data
            int curSum, curLeftJ;

            // Clear
            // memset(sumColumn[indexThread], 0, (M + 1) * sizeof(int));
            for(int i = 0; i < M; ++ i) sumColumn[indexThread][i] = 0;

            // Init
            maxFuncSum[curIndex] = maxSum;
            upFuncI[curIndex] = upI;
            leftFuncJ[curIndex] = leftJ;
            downFuncI[curIndex] = downI;
            rightFuncJ[curIndex] = rightJ;

            // Cycle for the upper bound
            for(int i = curIndex; i < N; ++ i) 
            {     
                curSum = 0, curLeftJ = 0;
                for(int j = 0; j < M; ++ j)
                {
                    sumColumn[indexThread][j] += board[i][j];
                    curSum += sumColumn[indexThread][j];

                    if(curSum > maxFuncSum[curIndex])
                    {
                        maxFuncSum[curIndex] = curSum;
                        upFuncI[curIndex] = curIndex;
                        leftFuncJ[curIndex] = curLeftJ;
                        downFuncI[curIndex] = i;
                        rightFuncJ[curIndex] = j;
                    }

                    if(curSum < 0)
                    {
                        curSum = 0;
                        curLeftJ = j + 1;
                    }
                }
            }
        }
        
        // Checking the results
        for(int curIndex = 0; curIndex < N; ++ curIndex)
            if(maxFuncSum[curIndex] > maxSum)
            {
                maxSum = maxFuncSum[curIndex];
                upI = upFuncI[curIndex];
                leftJ = leftFuncJ[curIndex];
                downI = downFuncI[curIndex];
                rightJ = rightFuncJ[curIndex];
            }

        if(rotateMatrix == 1)
        {
            int tempUpI = M - rightJ - 1, tempLeftJ = upI, tempDownI = M - leftJ - 1, tempRightJ = downI;
            upI = tempUpI, leftJ = tempLeftJ, downI = tempDownI, rightJ = tempRightJ;
        }

        printf("Case #%d: %d %d %d %d %d %d\n", it + 1, upI, leftJ, downI, rightJ, maxSum, (rightJ - leftJ + 1) * (downI - upI + 1));

        // cout << "Case #" << it + 1 << ": " << upI << " " << leftJ << " " << downI << " " << rightJ << " ";
        // cout << maxSum << " " << (rightJ - leftJ + 1) * (downI - upI + 1) << endl;
    }

    size_t timeFinish = curTime();	

    // cout << fixed << setprecision(5) << (timeFinish - timeStart + 0.0) / CLOCKS_PER_SEC << endl;
    fprintf(stderr, "Time of execution: %.3lf sec.\n", (double)(timeFinish - timeStart) / 1000.0);

    return 0;
}



