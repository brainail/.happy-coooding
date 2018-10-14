#include <iostream>
#include <omp.h>
#include <ctime>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
// #include <sys/time.h>
#include <string.h>
using namespace std;

// Maximum field size
const int maxColumn = 20000 + 10;

// Number of threads
const int maxNumberOfThreads = 100;
int numberOfThreads = 32;

// Sum in column
int sumColumn[maxNumberOfThreads + 10][maxColumn];

// Cur answer for function
int maxFuncSum[maxColumn];
int upFuncI[maxColumn];
int leftFuncJ[maxColumn];
int downFuncI[maxColumn];
int rightFuncJ[maxColumn];

// Field size
int N, M;

// Parameters to generate
int a, b, m, seed0;
bool rotateMatrix = false;

// Answer
int maxSum, leftJ, rightJ, upI, downI;

// Number of tests
int numberOfTestCase;

// Field
int ** board;

// Get Time
static inline size_t curTime() {
    // struct timeval now_tv;
    // gettimeofday( &now_tv, NULL );
    // return (size_t)now_tv.tv_sec * 1000 + (size_t)now_tv.tv_usec / 1000;
    return 0;
}

// Generate a new value
int PRNG(int seed, int a, int b, int m)
{
    return (a * seed + b) % m;
}

// Maximum size of the field
void maxFieldSize(int & MAXN, int & MAXM) 
{
    MAXN = MAXM = 0;
    for(int it = 0; it < numberOfTestCase; ++ it) 
    {
        scanf("%d %d %d %d %d %d", &N, &M, &seed0, &a, &b, &m);
        if(min(N, M) > MAXN) MAXN = min(N, M);
        if(max(N, M) > MAXM) MAXM = max(N, M);
    }
}

// The generation of matrix elements
void generatingOfMatrix()
{
    int seed = seed0;
    int dstSize = N * M;
    long long sum = 0;
    rotateMatrix = false;

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
        rotateMatrix = true;
        for(int i = 0; i < N; ++ i)
            for(int j = 0; j < M; ++ j)
            {
                seed = PRNG(seed, a, b, m);
                board[j][N - i - 1] = seed;
                sum += seed;
            }
            swap(N, M);
    }

    /* calculate the mean value. Avoid float logic when making rounding. */
    int mean = (int) (sum / (long long) dstSize); 
    int remainder = (int) (sum % (long long) dstSize); 
    mean += (remainder * 2 > (signed) dstSize) ? (1) : (0); 

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

    numberOfThreads = omp_get_max_threads();

    cout << numberOfThreads << endl;

    args = new char * [3];
    numberOfArgumet = 3;
    args[1] = "input.txt";
    args[2] = "output.txt";

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
    int MAXN = 0, MAXM = 0;
    maxFieldSize(MAXN, MAXM);

    // Creation of the matrix
    board = new int * [MAXN];
    for(int i = 0; i < MAXN; ++ i) 
        board[i] = new int [MAXM];

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

        int chunkSize = 5;

        // Calculation of answer
        omp_set_num_threads(numberOfThreads);
        #pragma omp parallel shared(sumColumn, board)
        {
            #pragma omp for schedule (dynamic)
            for(int curIndex = 0; curIndex < N; ++ curIndex)
            {
                // Calculation of the current answer

                // Get ID
                int indexThread = omp_get_thread_num();

                // Some data
                int curSum, curLeftJ;

                // Clear
                memset(sumColumn[indexThread], 0, (M + 1) * sizeof(int));

                // Init
                int m_maxFuncSum = maxSum;
                int m_upFuncI = upI;
                int m_leftFuncJ = leftJ;
                int m_downFuncI = downI;
                int m_rightFuncJ = rightJ;

                // Cycle for the upper bound
                for(int i = curIndex; i < N; ++ i) 
                {
                    curSum = 0;
                    curLeftJ = 0;
                    for(int j = 0; j < M; ++ j)
                    {
                        curSum += *(*(sumColumn + indexThread) + j) += *(*(board + i) + j);

                        if(curSum > m_maxFuncSum)
                        {
                            m_maxFuncSum = curSum;
                            m_upFuncI = curIndex;
                            m_leftFuncJ = curLeftJ;
                            m_downFuncI = i;
                            m_rightFuncJ = j;
                        } 

                        if(curSum < 0)
                        {
                            curSum = 0;
                            curLeftJ = j + 1;
                        }
                    }
                }

                maxFuncSum[curIndex] = m_maxFuncSum;
                upFuncI[curIndex] = m_upFuncI;
                leftFuncJ[curIndex] = m_leftFuncJ;
                downFuncI[curIndex] = m_downFuncI;
                rightFuncJ[curIndex] = m_rightFuncJ;
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

            if(rotateMatrix)
            {
                int tempUpI = M - rightJ - 1, tempLeftJ = upI, tempDownI = M - leftJ - 1, tempRightJ = downI;
                upI = tempUpI, leftJ = tempLeftJ, downI = tempDownI, rightJ = tempRightJ;
            }

            printf("Case #%d: %d %d %d %d %d %d\n", it + 1, upI, leftJ, downI, rightJ, maxSum, (rightJ - leftJ + 1) * (downI - upI + 1));
    }

    // Destruction of the matrix
    for(int i = 0; i < MAXN; ++ i) 
        delete [] board[i];
    delete [] board;

    size_t timeFinish = curTime();	

    fprintf(stderr, "Time of execution: %.3lf sec.\n", (double)(timeFinish - timeStart) / 1000.0);

    return 0;
}



