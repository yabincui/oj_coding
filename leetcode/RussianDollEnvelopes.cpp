class Solution {
    
    void setChange(int pos, int value, unordered_map<int, int>& change_map) {
        auto it = change_map.find(pos);
        if (it == change_map.end()) {
            change_map[pos] = value;
        } else {
            it->second = min(it->second, value);
        }
    }
    
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        // Use stack?
        // 1. Sort envelopes in width increasing order.
        // 2. Then it becomes a height list. Find a longest increasing list. (Height, length). (length, Height) array.
        sort(envelopes.begin(), envelopes.end());
        vector<int> length;
        int i = 0;
        if (!envelopes.empty()) {
            length.push_back(envelopes[0].second);
            while (i < envelopes.size() && envelopes[i].first == envelopes[0].first) {
                i++;
            }
        }
        while (i < envelopes.size()) {
            unordered_map<int, int> change_map;
            int w = envelopes[i].first;
            int j;
            for (j = i; j < envelopes.size() && envelopes[j].first == w; ++j) {
                int h = envelopes[j].second;
                auto it = lower_bound(length.begin(), length.end(), h);
                if (it != length.end()) {
                    int pos = it - length.begin();
                    setChange(pos, h, change_map);
                } else if (h > length.back()) {
                    setChange(length.size(), h, change_map);
                }
            }
            for (auto& pair : change_map) {
                if (pair.first == length.size()) {
                    length.push_back(pair.second);
                } else {
                    length[pair.first] = pair.second;
                }
            }
            i = j;
        }
        return length.size();
    }
};
