// 517. Super Washing Machines.
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int sum = 0;
        for (auto n : machines) {
            sum += n;
        }
        if (sum == 0) return 0;
        if (sum % machines.size() != 0) return -1;
        int average = sum / machines.size();
        int left = 0;
        int right = sum;
        int res = 0;
        for (int i = 0; i < machines.size(); ++i) {
            right -= machines[i];
            int left_need = average * i - left;
            int right_need = average * (machines.size() - i - 1) - right;
            int flow = 0;
            if (left_need > 0 && right_need > 0) {
                flow = left_need + right_need;
            } else if (left_need < 0 && right_need < 0) {
                flow = -min(left_need, right_need);
            } else {
                flow = max(abs(left_need), abs(right_need));
            }
            //printf("i = %d, left = %d, right = %d, left_need = %d, right_need = %d, flow = %d\n", i, left, right, left_need, right_need, flow);
            res = max(res, flow);
            left += machines[i];
        }
        return res;
    }
};
