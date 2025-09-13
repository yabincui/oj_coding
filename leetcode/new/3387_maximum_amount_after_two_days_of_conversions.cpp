// key: flood graph
// no error
class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        unordered_map<string, double> value_map;
        bool has_change = true;
        value_map[initialCurrency] = 1.0;
        while (has_change) {
            has_change = false;
            for (int i = 0; i < pairs1.size(); i++) {
                if (update_value(value_map, pairs1[i][0], pairs1[i][1], rates1[i])) {
                    has_change = true;
                }
                if (update_value(value_map, pairs1[i][1], pairs1[i][0], 1.0 / rates1[i])) {
                    has_change = true;
                }
            }
        }
        has_change = true;
        while (has_change) {
            has_change = false;
            for (int i = 0; i < pairs2.size(); i++) {
                if (update_value(value_map, pairs2[i][0], pairs2[i][1], rates2[i])) {
                    has_change = true;
                }
                if (update_value(value_map, pairs2[i][1], pairs2[i][0], 1.0 / rates2[i])) {
                    has_change = true;
                }
            }
        }
        return value_map[initialCurrency];
    }

    bool update_value(unordered_map<string, double>& value_map, const string& from,
                      const string& to, double rate) {
        auto it = value_map.find(from);
        if (it != value_map.end()) {
            double value = it->second * rate;
            if (value_map[to] < value - 1e-9) {
                value_map[to] = value;
                return true;
            }
        }
        return false;
    }
};