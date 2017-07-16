class AutocompleteSystem {
    
    struct Node {
        string sentence;
        int time;
        Node(string s, int t) : sentence(s), time(t) {}
    };
    
    unordered_map<string, int> string_map;
    vector<Node> v;
    string cur_word;
    vector<int> cur_match;
    
    void addNode(string& s, int time) {
        auto it = string_map.find(s);
        if (it == string_map.end()) {
            string_map[s] = v.size();
            v.push_back(Node(s, time));
        } else {
            v[it->second].time += time;
        }
    }
    
    void updateCurMatch() {
        if (cur_word.size() == 1) {
            for (int i = 0; i < v.size(); ++i) {
                if (v[i].sentence.size() > 0 && v[i].sentence[0] == cur_word[0]) {
                    cur_match.push_back(i);
                }
            }
        } else {
            vector<int> next_match;
            int pos = cur_word.size() - 1;
            for (auto& i : cur_match) {
                if (v[i].sentence.size() > pos && v[i].sentence[pos] == cur_word.back()) {
                    next_match.push_back(i);
                }
            }
            cur_match = std::move(next_match);
        }
    }
    
    static bool compareNode(const Node& n1, const Node& n2) {
        if (n1.time != n2.time) {
            return n1.time > n2.time;
        }
        return n1.sentence < n2.sentence;
    }
    
    vector<string> selectMatches() {
        priority_queue<Node, vector<Node>, decltype(&compareNode)> q(compareNode);
        for (auto& i : cur_match) {
            q.push(v[i]);
            if (q.size() > 3) {
                q.pop();
            }
        }
        vector<string> res;
        while (!q.empty()) {
            res.push_back(q.top().sentence);
            q.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
    
public:
    AutocompleteSystem(vector<string> sentences, vector<int> times) {
        for (int i = 0; i < sentences.size(); ++i) {
            addNode(sentences[i], times[i]);
        }
    }
    
    vector<string> input(char c) {
        if (c != '#') {
            cur_word.push_back(c);
            updateCurMatch();
            return selectMatches();
        } else {
            addNode(cur_word, 1);
            cur_word.clear();
            cur_match.clear();
            return vector<string>();
        }
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj.input(c);
 */
