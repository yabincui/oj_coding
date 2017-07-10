class Solution {
    
public:
    vector<int> majorityElement(vector<int>& nums) {
        // keep two numbers. a third number, all minus one.
        vector<pair<int, int>> v;
        for (auto& n : nums) {
            bool exist = false;
            for (auto& p : v) {
                if (p.first == n) {
                    p.second++;
                    exist = true;
                }
            }
            if (exist) continue;
            if (v.size() < 2) {
                v.push_back(make_pair(n, 1));
            } else {
                for (int i = 0; i < 2; ++i) {
                    v[i].second--;
                }
                if (v[0].second == 0) {
                    if (v[1].second == 0) {
                        v.clear();
                    } else {
                        v[0] = v[1];
                        v.resize(1);
                    }
                } else if (v[1].second == 0) {
                    v.resize(1);
                }
            }
        }
        vector<int> res;
        for (int i = 0; i < v.size(); ++i) {
            int count = 0;
            for (auto n : nums) {
                if (n == v[i].first) {
                    count++;
                }
            }
            if (count * 3 > nums.size()) {
                res.push_back(v[i].first);
            }
        }
        return res;
    }
};
