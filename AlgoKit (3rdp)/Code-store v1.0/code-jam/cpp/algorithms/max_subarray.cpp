#include<iostream>

int a[10] = {1, 2, -6, 3, -2, 4, -1, 3, 2, -4};

int maximum_subarray()
{
    int max_sum = 0, sum = 0;
    int start = 0, end = 0, temp_start = 0;

    for(int i = 0; i < 10; ++i) {
        sum += a[i];

        if(sum < 0) {
            sum = 0;
            temp_start = i + 1; // 現在情況很糟，故設定起點在下一個數字
        }

        if(sum > max_sum) {
            max_sum = sum;
            start = temp_start;
            end = i;
        }
    }

    if(start > end)
        cout << "什麼數字都不取" << endl;
    else
        cout << "從" << start << "到" << end << endl;

    return max_sum;
}

int main()
{
    maximum_subarray();
    return 0;
}
