#include <iostream>
using namespace std;
int binarysearch(int vector[], int x, int low, int high)
{
    int mid;
    if(low > high)
        return -1;
    mid = (low + high) / 2;
    return(x == vector[mid] ? mid : x < vector[mid] ?
           binarysearch(vector, x, low, mid - 1) :
           binarysearch(vector, x, mid + 1, high));
}
int main()
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value = 6;
    cout << "found " << 6 << " at position " << binarysearch(array, value, 0, 10) << endl;
    return 0;
}
