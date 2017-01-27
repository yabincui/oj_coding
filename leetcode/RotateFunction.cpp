// 396. Rotate Function
typedef long long u64;
class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        u64 sum = 0;
        for (auto& a : A) {
            sum += a;
        }
        u64 f0 = 0;
        for (int i = 0; i < A.size(); ++i) {
            u64 tmp = (u64)i * A[i];
            f0 += tmp;
        }
        u64 max_f = f0;
        u64 prev_f = f0;
        for (int i = 0; i < A.size(); ++i) {
            u64 f = prev_f - sum + (u64)A.size() * A[i];
            //printf("f[%d] = %llu\n", i, prev_f);
            if (f > max_f) {
                max_f = f;
            }
            prev_f = f;
        }
        return (int)max_f;
    }
};
