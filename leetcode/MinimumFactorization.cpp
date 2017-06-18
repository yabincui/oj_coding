class Solution {
public:
    int smallestFactorization(int a) {
        if (a == 1) return 1;
        vector<int> s(10, 0);
        s[2] = getCount(a, 2);
        s[3] = getCount(a, 3);
        s[5] = getCount(a, 5);
        s[7] = getCount(a, 7);
        if (a != 1) {
            return 0;
        }
        if (s[2] >= 3) {
            s[8] = s[2] / 3;
            s[2] %= 3;
        }
        if (s[2] >= 2) {
            s[4] = s[2] / 2;
            s[2] %= 2;
        }
        if (s[3] >= 2) {
            s[9] = s[3] / 2;
            s[3] %= 2;
        }
        if (s[2] == 1 && s[3] == 1) {
            s[2] = s[3] = 0;
            s[6] = 1;
        }
        if (s[4] > 0 && s[3] == 1) {
            s[4]--;
            s[2]++;
            s[6]++;
            s[3] = 0;
        }
        long long result = 0;
        for (int i = 2; i < 10; ++i) {
            for (int j = 0; j < s[i]; ++j) {
                result = result * 10 + i;
                if (result > INT_MAX) {
                    return 0;
                }
            }
        }
        if (result > INT_MAX) {
            return 0;
        }
        return result;
    }
    
    int getCount(int& a, int f) {
        int count = 0;
        while (a % f == 0) {
            a /= f;
            count++;
        }
        return count;
    }
};
