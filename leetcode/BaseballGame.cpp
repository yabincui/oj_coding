class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> v;
        for (auto& s : ops) {
            if (s == "C") {
                if (!v.empty()) {
                    v.pop_back();
                }
            } else if (s == "D") {
                if (!v.empty()) {
                    v.push_back(v.back() * 2);
                }
            } else if (s == "+") {
                if (v.size() >= 2) {
                    v.push_back(v.back() + v[v.size() - 2]);
                }
            } else {
                v.push_back(atoi(s.c_str()));
            }
        }
        int sum = 0;
        for (auto n : v) {
            sum += n;
        }
        return sum;
    }
};