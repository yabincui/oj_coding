class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> str_map;
        for (int i = 0; i < list1.size(); ++i) {
            str_map[list1[i]] = i;
        }
        vector<string> res;
        int min_sum = INT_MAX;
        for (int i = 0; i < list2.size(); ++i) {
            auto it = str_map.find(list2[i]);
            if (it != str_map.end()) {
                int sum = i + it->second;
                if (sum < min_sum) {
                    min_sum = sum;
                    res.clear();
                    res.push_back(list2[i]);
                } else if (sum == min_sum) {
                    res.push_back(list2[i]);
                }
            }
        }
        return res;
    }
};
