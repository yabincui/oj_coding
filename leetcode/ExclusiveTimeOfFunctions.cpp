class Solution {
    
    struct Node {
        int func_id;
        bool start;
        int time;
        Node(int func_id = 0, bool start = false, int time = 0) : func_id(func_id), start(start), time(time) {}
    };
    
    Node parseNode(string& s) {
        Node res;
        res.start = s.find("start") != string::npos;
        int i = 0;
        while (s[i] != ':') {
           res.func_id = res.func_id * 10 + s[i] - '0';
            i++;
        }
        i++;
        while (s[i] != ':') {
            i++;
        }
        i++;
        while (i < s.size()) {
            res.time = res.time * 10 + s[i] - '0';
            i++;
        }
        return res;
    } 
    
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> res(n, 0);
        vector<Node> stack;
        int prev_time = 0;  // start of time.
        for (auto& s : logs) {
            Node cur = parseNode(s);
            if (cur.start) {
                if (!stack.empty()) {
                    res[stack.back().func_id] += cur.time - prev_time;
                }
                stack.push_back(cur);
                prev_time = cur.time;
            } else {
                if (stack.empty() || stack.back().func_id != cur.func_id) {
                    return vector<int>();
                }
                if (cur.time < prev_time) {
                    stack.pop_back();
                    continue;
                }
                res[stack.back().func_id] += cur.time - prev_time + 1;
                prev_time = cur.time + 1;
                stack.pop_back();
            }
        }
        return res;
    }
};
