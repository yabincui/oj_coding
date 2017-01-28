// 215. Kth Largest Element in an Array
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return findKth(nums.data(), nums.size(), nums.size() - k);
    }
    
    int findKth(int* s, int n, int k) {
        if (n == 1) {
            return s[0];
        }
        int left = 1;
        int right = n - 1;
        int key = s[0];
        while (left <= right) {
            while (s[left] < key && left <= right) left++;
            while (s[right] > key && left <= right) right--;
            if (left <= right) {
                int tmp = s[left]; s[left] = s[right]; s[right] = tmp;
                left++;
                right--;
            }
        }
        int tmp = s[0]; s[0] = s[right]; s[right] = tmp;
        if (right == k) {
            return s[right];
        } else if (right < k) {
            return findKth(s + right + 1, n - right - 1, k - right - 1);
        } else {
            return findKth(s, right, k);
        }
    }
};
