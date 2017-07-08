class Solution {
    
    void AddValue(bool* cur, int value, int n, bool* next) {
        memcpy(next, cur, (n + 1) * sizeof(bool));
        for (int i = n; i >= value; --i) {
            next[i] |= next[i - value];
        }
    }
    
public:
    int minPatchesN2(vector<int>& nums, int n) {
        
        std::unique_ptr<bool[]> v1(new bool[n + 1]);
        std::unique_ptr<bool[]> v2(new bool[n + 1]);
        bool *cur, *next;
        next = v1.get();
        cur = v2.get();
        memset(cur, 0, sizeof(cur));
        cur[0] = true;
        for (auto& num : nums) {
            AddValue(cur, num, n, next);
            swap(cur, next);
        }
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            if (!cur[i]) {
                AddValue(cur, i, n, next);
                swap(cur, next);
                result++;
            }
        }
        return result;
    }
    
    int minPatches(vector<int>& nums, int n) {
        sort(nums.begin(), nums.end());
        int result = 0;
        int64_t upLimit = 0;
        int numIndex = 0;
        while (upLimit < n) {
            // use all possible nums.
            while (numIndex < nums.size() && upLimit + 1 >= nums[numIndex]) {
                upLimit += nums[numIndex];
                numIndex++;
            }
            if (upLimit >= n) {
                break;
            }
            // Now we need to add upLimit + 1.
            result++;
            upLimit += upLimit + 1;
        }
        return result;
    }
};


