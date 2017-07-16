class Solution {
    
    vector<int> coins;
    unordered_map<int, int> cache;
    
    int find(int amount) {
        auto it = cache.find(amount);
        if (it != cache.end()) {
            return it->second;
        }
        int best_cost = INT_MAX;
        for (int i = 0; i < coins.size() && coins[i] <= amount; ++i) {
            int cost = find(amount - coins[i]);
            if (cost != INT_MAX) {
                best_cost = min(best_cost, cost + 1);
            }
        }
        cache[amount] = best_cost;
        return best_cost;
    }
    
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        this->coins = coins;
        cache.clear();
        cache[0] = 0;
        return find(amount) == INT_MAX ? -1 : find(amount);
    }
};
