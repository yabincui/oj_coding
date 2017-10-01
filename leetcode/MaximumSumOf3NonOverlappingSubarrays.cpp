class Solution {
    
    vector<int> getKsum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ksum(n);
        for (int i = n - 1; i >= 0; --i) {
            if (i == n - 1) {
                ksum[i] = nums[i];
                continue;
            }
            if (i + k >= n) {
                ksum[i] = ksum[i + 1] + nums[i];
                continue;
            }
            ksum[i] = ksum[i + 1] + nums[i] - nums[i + k];
        }
        ksum.resize(n - k + 1);
        return ksum;
    }
    
    struct Node {
        int value;
        int pos;
    };
    
    vector<Node> getMaxOne(vector<int>& s) {
        vector<Node> res(s.size());
        for (int i = s.size() - 1; i >= 0; --i) {
            if (i + 1 == s.size()) {
                res[i].value = s[i];
                res[i].pos = i;
            } else {
                res[i] = res[i + 1];
                if (res[i].value <= s[i]) {
                    res[i].value = s[i];
                    res[i].pos = i;
                }
            }
        }
        return res;
    }
    
    vector<Node> getMaxTwo(vector<int>& s, vector<Node>& maxOne, int k) {
        int max_index = maxOne.size() - 1 - k;
        vector<Node> maxTwo(max_index + 1);
        for (int i = max_index; i >= 0; --i) {
            if (i == max_index) {
                maxTwo[i].value = maxOne[i + k].value + s[i];
                maxTwo[i].pos = i;
            } else {
                maxTwo[i] = maxTwo[i + 1];
                int newValue = maxOne[i + k].value + s[i];
                if (newValue >= maxTwo[i].value) {
                    maxTwo[i].value = newValue;
                    maxTwo[i].pos = i;
                }
            }
        }
        return maxTwo;
    }
    
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        vector<int> ksum = getKsum(nums, k);
        int n = nums.size();
        int m = ksum.size();
        
        vector<Node> maxOne = getMaxOne(ksum);
        vector<Node> maxTwo = getMaxTwo(ksum, maxOne, k);
        vector<Node> maxThree = getMaxTwo(ksum, maxTwo, k);
        
        vector<int> res(3);
        res[0] = maxThree[0].pos;
        int cur = res[0] + k;
        res[1] = maxTwo[cur].pos;
        cur = res[1] + k;
        res[2] = maxOne[cur].pos;
        return res;
    }
};
