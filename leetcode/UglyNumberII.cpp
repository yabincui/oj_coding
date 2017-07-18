class Solution {
    
    struct Node {
        int val;
        int mulIndex;
        Node(int val, int mulIndex) : val(val), mulIndex(mulIndex) {}
    };
    
    static bool compareNode(const Node& n1, const Node& n2) {
        if (n1.val != n2.val) {
            return n1.val > n2.val;
        }
        return n1.mulIndex > n2.mulIndex;
    }
    
public:
    int nthUglyNumber(int n) {
        if (n == 1) return 1;
        priority_queue<Node, vector<Node>, decltype(&compareNode)> q(compareNode);
        vector<int> s = {2, 3, 5};
        q.push(Node(s[0], 0));
        for (int i = 2; i <= n; ++i) {
            Node cur = q.top(); q.pop();
            if (i == n) {
                return cur.val;
            }
            int64_t next = (int64_t)cur.val * s[cur.mulIndex];
            if (next <= INT_MAX) {
                q.push(Node(next, cur.mulIndex));
            }
            if (cur.mulIndex + 1 < s.size()) {
                next = (int64_t)cur.val / s[cur.mulIndex] * s[cur.mulIndex + 1];
                if (next <= INT_MAX) {
                    q.push(Node(next, cur.mulIndex + 1));
                }
            }
        }
    }
};
