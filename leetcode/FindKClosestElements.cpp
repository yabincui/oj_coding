class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res;
        auto it = lower_bound(arr.begin(), arr.end(), x);
        int splitPos = it == arr.end() ? arr.size() : it - arr.begin();
        int left = splitPos - 1;
        int right = splitPos;
        for (int i = 0; i < k; ++i) {
            int leftDiff = left < 0 ? INT_MAX : x - arr[left];
            int rightDiff = right >= arr.size() ? INT_MAX : arr[right] - x;
            if (leftDiff <= rightDiff) {
                res.push_back(arr[left--]);
            } else {
                res.push_back(arr[right++]);
            }
        }
        sort(res.begin(), res.end());
        return res;
    }
};
