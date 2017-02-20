// 525. Contiguous Array
class Solution {
public:
    /*
    // Use divide-and-conquer. O(nlogn)
    int left_0_buf[50001];
    int left_1_buf[50001];
    int right_0_buf[50001];
    int right_1_buf[50001];
    int max_len;
    
    void half_search(int* data, int size) {
        if (size <= max_len) {
            return;
        }
        int left_0_len = 0;
        int left_1_len = 0;
        int right_0_len = 0;
        int right_1_len = 0;
        
        int mid = size / 2;
        int base = data[mid] == 0 ? -1 : 1;
        left_0_buf[0] = left_1_buf[0] = right_0_buf[0] = right_1_buf[0] = 0;
        for (int i = mid - 1, sum = 0; i >= 0; --i) {
            sum += data[i] == 0 ? -1 : 1;
            int diff = sum < 0 ? -sum : sum;
            int len = mid - i;
            if (sum <= 0) {
                if (diff > left_0_len) {
                    left_0_len = diff;
                }
                left_0_buf[diff] = len;
            }
            if (sum >= 0) {
                if (diff > left_1_len) {
                    left_1_len = diff;
                }
                left_1_buf[diff] = len;
            }
        }
        for (int i = mid + 1, sum = 0; i < size; ++i) {
            sum += data[i] == 0 ? -1 : 1;
            int diff = sum < 0 ? -sum : sum;
            int len = i - mid;
            if (sum <= 0) {
                if (diff > right_0_len) {
                    right_0_len = diff;
                }
                right_0_buf[diff] = len;
            }
            if (sum >= 0) {
                if (diff > right_1_len) {
                    right_1_len = diff;
                }
                right_1_buf[diff] = len;
            }
        }
        int range1 = (base == -1) ? min(left_0_len + 1, right_1_len) : min(left_0_len, right_1_len + 1);
        for (int i = 1; i <= range1; ++i) {
            int left = (base == -1) ? left_0_buf[i-1] : left_0_buf[i];
            int right = (base == -1) ? right_1_buf[i] : right_1_buf[i-1];
            int tmp = right + left + 1;
            max_len = max(max_len, tmp);
        }
        range1 = (base == -1) ? min(left_1_len, right_0_len + 1) : min(left_1_len + 1, right_0_len);
        for (int i = 1; i <= range1; ++i) {
            int left = (base == -1) ? left_1_buf[i] : left_1_buf[i-1];
            int right = (base == -1) ? right_0_buf[i-1] : right_0_buf[i];
            int tmp = right + left + 1;
            max_len = max(max_len, tmp);
        }
        half_search(data, mid);
        half_search(data + mid + 1, size - mid - 1);
    }

    int findMaxLength(vector<int>& nums) {
        max_len = 0;
        half_search(nums.data(), nums.size());
        return max_len;
    }
    */

    // Use sum array.
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> diff_map;
        int diff = 0;
        int res = 0;
        diff_map[0] = -1;
        for (int i = 0; i < nums.size(); ++i) {
            diff += nums[i] == 0 ? -1 : 1;
            auto it = diff_map.find(diff);
            if (it != diff_map.end()) {
                int dist = i - it->second;
                res = max(res, dist);
            } else {
                diff_map[diff] = i;
            }
        }
        return res;
    }
};
