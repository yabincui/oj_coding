// Key: array, simulation
class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int waiting = 0;
        int profit = 0;
        int max_profit = 0;
        int rotation_for_max_profit = 0;
        for (int rotation = 0; rotation < customers.size() || waiting > 0; rotation++) {
            if (rotation < customers.size()) {
                waiting += customers[rotation];
            }
            int board = min(waiting, 4);
            waiting -= board;
            profit += board * boardingCost - runningCost;
            if (profit > max_profit) {
                max_profit = profit;
                rotation_for_max_profit = rotation + 1;
            }
        }
        if (max_profit <= 0) {
            return -1;
        }
        return rotation_for_max_profit;
    }
};