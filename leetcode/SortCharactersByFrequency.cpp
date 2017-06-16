class Solution {
    
    struct Node {
        char value;
        int count;
    
        Node(char value, int count) : value(value), count(count) {}
    };
    
    static bool compareNode(Node& n1, Node& n2) {
        return n1.count > n2.count;
    }
    
public:
    string frequencySort(string s) {
        unordered_map<char, int> map;
        for (auto& c : s) {
            map[c]++;
        }
        vector<Node> nodes;
        for (auto& pair : map) {
            nodes.emplace_back(pair.first, pair.second);
        }
        sort(nodes.begin(), nodes.end(), compareNode);
        string res;
        for (auto& n : nodes) {
            for (int i = 0; i < n.count; ++i) {
                res.push_back(n.value);
            }
        }
        return res;
    }
};
