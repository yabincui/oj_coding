class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> nostock(n);
        vector<int> stock(n);
        vector<int> cooldown(n);
        
        if (n == 0) return 0;
        stock[0] = -prices[0];
        for (int i = 1; i < n; ++i) {
            // buy a stock.
            stock[i] = max(stock[i-1], nostock[i-1] - prices[i]);
            // sell a stock.
            cooldown[i] = stock[i-1] + prices[i];
            // cool down.
            nostock[i] = max(nostock[i-1], cooldown[i-1]);
        }
        return max(nostock[n-1], cooldown[n-1]);
    }
};