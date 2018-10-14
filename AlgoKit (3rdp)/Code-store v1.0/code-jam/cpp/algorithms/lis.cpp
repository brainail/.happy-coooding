#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int s[5] = {1, 6, 3, 4, 5}; //input
int lis[5];
int prev[5];    // prev[x] 紀錄 s[x] 是接在哪個位置的數字後面
// 如果它前面沒有數字就紀錄 -1
int LIS()
{
    for(int i = 0; i < 5; i++) lis[i] = 1;

    // -1 代表這個數字沒有接在其他數字之後
    for(int i = 0; i < 5; i++) prev[i] = -1;

    for(int i = 0; i < 5; i++)
        for(int j = i + 1; j < 5; j++)
            if(s[j] > s[i])
                if(lis[i] + 1 > lis[j]) {
                    lis[j] = lis[i] + 1;
                    prev[j] = i;   // s[j] 接在 s[i] 後面
                }

    int ans = 0;

    for(int i = 0; i < 5; i++)
        ans = max(ans, lis[i]);

    return ans;
}

void print_LIS(int x)
{
    if(prev[x] != -1)
        print_LIS(prev[x]);

    cout << s[x] << " ";
}

int main()
{
    int ans = LIS();
    print_LIS(4);
    return 0;
}