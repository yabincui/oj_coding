// 398. Random Pick Index
#include <random>

class Solution {
public:
    vector<pair<int, int>> s;
    
    Solution(vector<int> nums) {
        for (int i = 0; i < nums.size(); ++i) {
            s.push_back(pair<int, int>(nums[i], i));
        }
        sort(s.begin(), s.end());
        //printf("s[6415]=%d, s[4857] = %d\n", nums[6415], nums[4857]);
    }
    
    int Rand() {
        uint32_t value = rand() & ((1<<15)-1);
        value <<= 15;
        value |= rand() & ((1<<15)-1);
        value <<= 1;
        value |= rand() % 2;
        return value;
    }
    
    int pick(int target) {
        int low = findLowEdge(target);
        int high = findHighEdge(target, low);
        int id = Rand() % (high - low + 1) + low;
        return s[id].second;
    }
    
    int findLowEdge(int target) {
        int low = 0;
        int high = s.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (s[mid].first > target) {
                high = mid - 1;
            } else if (s[mid].first < target) {
                low = mid + 1;
            } else {
                if (mid == 0 || s[mid-1].first < target) {
                    return mid;
                }
                high = mid - 1;
            }
        }
        return -1;
    }
    
    int findHighEdge(int target, int low) {
        int high = s.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (s[mid].first > target) {
                high = mid - 1;
            } else if (s[mid].first < target) {
                low = mid + 1;
            } else {
                if (mid == s.size() - 1 || s[mid+1].first > target) {
                    return mid;
                }
                low = mid + 1;
            }
        }
        return -1;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */
