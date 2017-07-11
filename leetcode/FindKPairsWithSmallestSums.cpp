class Solution {
    
    struct Node {
        int value;
        int i1, i2;
        Node(int value, int i1, int i2) : value(value), i1(i1), i2(i2) {
        }
    };
    
    static bool compNode(const Node& n1, const Node& n2) {
        if (n1.value != n2.value) return n1.value > n2.value;
        if (n1.i1 != n2.i1) return n1.i1 > n2.i1;
        if (n1.i2 != n2.i2) return n1.i2 > n2.i2;
        return false;
    }
    
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        if (k == 0 || nums1.empty() || nums2.empty()) return vector<pair<int, int>>();
        priority_queue<Node, vector<Node>, decltype(&compNode)> q(compNode);
        
        q.push(Node(nums1[0] + nums2[0], 0, 0));
        vector<pair<int, int>> res;
        while (!q.empty() && res.size() < k) {
            Node node = q.top(); q.pop();
            res.push_back(make_pair(nums1[node.i1], nums2[node.i2]));
            if (node.i2 == 0 && node.i1 + 1 < nums1.size()) {
                q.push(Node(nums1[node.i1 + 1] + nums2[node.i2], node.i1 + 1, node.i2));
            }
            if (node.i2 + 1 < nums2.size()) {
                q.push(Node(nums1[node.i1] + nums2[node.i2 + 1], node.i1, node.i2 + 1));
            }
        }
        return res;
        
    }
};
