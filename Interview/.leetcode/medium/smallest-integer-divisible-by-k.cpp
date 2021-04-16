class Solution {
   public:
    int smallestRepunitDivByK(int K) {
        for (int r = 0, N = 1; N <= K; ++N)
            if ((r = (r * 10 + 1) % K) == 0)
                return N;
        return -1;
    }
};

/*
class Solution {
public:
    int smallestRepunitDivByK(int K) {
        if (0 == (K % 2) || 0 == (K % 5)) return -1;
        
        int x = 0, result = -1;
        vector<int> mods(K);
        for (int i = 1; ; ++i) {
            x = (x * 10 + 1) % K;
            if (0 == mods[x]) {
                mods[x] = i;
            } else {
                result = i - mods[x];
                break;
            }
        }
        return result;
    }
};
*/