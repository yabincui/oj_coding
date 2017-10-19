class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int result = 0;
        int heater_pos = 0;
        for (auto house : houses) {
            while (heater_pos < heaters.size() && house > heaters[heater_pos]) {
                heater_pos++;
            }
            int nearest = INT_MAX;
            if (heater_pos < heaters.size()) {
                nearest = heaters[heater_pos] - house;
            }
            if (heater_pos > 0) {
                nearest = min(nearest, house - heaters[heater_pos - 1]);
            }
            result = max(result, nearest);
        }
        return result;
    }
};
