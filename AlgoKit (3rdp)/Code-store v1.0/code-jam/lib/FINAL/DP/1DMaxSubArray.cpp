/**
Largest Sum Contiguous Subarray: Kadane’s Algorithm

maximum subarray problem is the task of finding the contiguous subarray within a one-dimensional array of numbers (containing at least one positive number) which has the largest sum
*/
#include <cstdio>
int maxSubArraySum(int a[], int size)
{
    int max_so_far = 0, max_ending_here = 0;

    for(int i = 0; i < size; ++i) {
        max_ending_here += a[i];

        if(max_ending_here < 0) {
            max_ending_here = 0;
        } else if(max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
    }

    return max_so_far;
}
int main()
{
    int a[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4};
    int max_sum = maxSubArraySum(a, sizeof(a) / sizeof(int));
    printf("{-2, 1, -3, 4, -1, 2, 1, -5, 4}\n");
    printf("Maximum contiguous sum = %d\n", max_sum);
    return 0;
}
