class Solution {
    
    struct Node {
        int val;
        int mulIndex;
        
        Node(int value = 0, int mulIndex = 0) : val(value), mulIndex(mulIndex) {}
    };
    
    static bool compareNode(const Node& n1, const Node& n2) {
        return n1.val > n2.val;
    }
    
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<Node, vector<Node>, decltype(&compareNode)> q(compareNode);
        if (n == 1) {
            return 1;
        }
        q.push(Node(primes[0], 0));
        for (int i = 2; i <= n; ++i) {
            Node cur = q.top(); q.pop();
            if (i == n) {
                return cur.val;
            }
            if (cur.mulIndex + 1 < primes.size()) {
                int64_t next = (int64_t)cur.val / primes[cur.mulIndex] * primes[cur.mulIndex + 1];
                if (next <= INT_MAX) {
                    q.push(Node(next, cur.mulIndex + 1));
                }
            }
            int64_t next = (int64_t)cur.val * primes[cur.mulIndex];
            if (next <= INT_MAX) {
                q.push(Node(next, cur.mulIndex));
            }
        }
    }
};
