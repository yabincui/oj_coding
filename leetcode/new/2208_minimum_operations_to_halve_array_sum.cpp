// Key: priority queue, integer overflow
class Solution {
public:
    int halveArray(vector<int>& nums) {
        int64_t sum = 0;
        priority_queue<double> q;
        for (int value : nums) {
            sum += value;
            q.push(value);
        }
        double reduce = 0.0;
        int op = 0;
        while (reduce * 2 - sum < -1e-9) {
            double value = q.top();
            value /= 2;
            reduce += value;
            q.pop();
            q.push(value);
            op++;
        }
        return op;
    }
};