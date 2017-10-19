class Solution {
    
    
    
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> count_map;
        for (auto& s : words) {
            count_map[s]++;
        }
        
        struct Node {
            string s;
            int freq;
            Node(const string& s, int freq) : s(s), freq(freq) {}
        };
        auto comp = [](const Node& n1, const Node& n2) {
            if (n1.freq != n2.freq) return n1.freq > n2.freq;
            return n1.s < n2.s;
        };
        priority_queue<Node, vector<Node>, decltype(comp)> q(comp);
        for (auto& pair : count_map) {
            q.push(Node(pair.first, pair.second));
            if (q.size() > k) {
                q.pop();
            }
        }
        vector<string> res(q.size());
        int i = res.size() - 1;
        while (!q.empty()) {
            res[i--] = q.top().s; q.pop();
        }
        return res;
    }
};
