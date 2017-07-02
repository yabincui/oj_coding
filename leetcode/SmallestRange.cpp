class Solution {
    struct Range {
        int s, e;
        Range(int s = 0, int e = 0) : s(s), e(e) {}
    };
    
    bool isBetter(Range& a, Range& b) {
        int64_t diff1 = (int64_t)a.e - a.s;
        int64_t diff2 = (int64_t)b.e - b.s;
        if (diff1 < diff2) {
            return true;
        }
        if (diff1 > diff2) {
            return false;
        }
        return a.s < b.s;
    }
    
    struct Node {
        int val;
        int list; // from which list
        Node(int val, int list) : val(val), list(list) {}
    };
    
    typedef bool (*compareNodeType)(const Node& n1, const Node& n2);
    
    static bool compareNode(const Node& n1, const Node& n2) {
        return n1.val < n2.val;
    }
    
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        if (nums.empty()) return vector<int>();
        vector<Node> nodes;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i].empty()) return vector<int>();
            for (auto& v : nums[i]) {
                nodes.push_back(Node(v, i));
            }
        }
        sort(nodes.begin(), nodes.end(), compareNode);
        int begin = -1;
        int end = 0;
        int okCount = 0;
        vector<int> countForLists(nums.size(), 0);
        Range bestRange(INT_MIN, INT_MAX);
        Range curRange(nodes[0].val);
        while (begin + 1 < nodes.size()) {
            while (okCount < nums.size() && begin + 1 < nodes.size()) {
                begin++;
                curRange.e = nodes[begin].val;
                //printf("curRange.e = %d\n", curRange.e);
                if (countForLists[nodes[begin].list]++ == 0) {
                    okCount++;
                }
            }
            if (okCount < nums.size()) break;
            while (end <= begin) {
                if (countForLists[nodes[end].list] == 1) {
                    curRange.s = nodes[end].val;
                    //printf("end curRange.s = %d\n", curRange.s);
                    if (isBetter(curRange, bestRange)) {
                        bestRange = curRange;
                    }
                }
                if (countForLists[nodes[end].list]-- == 1) {
                    okCount--;
                    end++;
                    break;
                }
                end++;
            }
        }
        vector<int> res;
        res.push_back(bestRange.s);
        res.push_back(bestRange.e);
        return res;
    }
};
