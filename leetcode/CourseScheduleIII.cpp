class Solution {
    
    struct Node {
        int endDay;
        int costDay;
        Node(int endDay, int costDay) : endDay(endDay), costDay(costDay) {}
    };
    
    static bool compareNode(const Node& n1, const Node& n2) {
        return n1.endDay < n2.endDay;
    }
    
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        int n = courses.size();
        int max_d = 0;
        for (auto& v : courses) {
            max_d = max(max_d, v[1]);
        }
        vector<int> dp(max_d + 1, 0);
        vector<Node> nodes;
        for (auto& v : courses) {
            nodes.emplace_back(v[1], v[0]);
        }
        sort(nodes.begin(), nodes.end(), compareNode);
        
        vector<int> finishDay; // finishDay[i] = earliest finish day of finishing i courses.
        finishDay.push_back(0);

        for (auto& node : nodes) {
            int needDay = node.endDay - node.costDay + 1;
            int prevDay = 0;
            int i;
            for (i = 1; i < finishDay.size(); ++i) {
                int nextDay = finishDay[i];
                if (prevDay + 1 > needDay) {
                    break;
                }
                if (finishDay[i] > prevDay + node.costDay) {
                    finishDay[i] = prevDay + node.costDay;
                }
                prevDay = nextDay;
            }
            if (i == finishDay.size() && prevDay < needDay) {
                //printf("node.endDay = %d, node.costDay = %d, prevDay = %d, i = %d\n", node.endDay, node.costDay, prevDay, i);
                finishDay.push_back(prevDay + node.costDay);
            }
        }
        return finishDay.size() - 1;
    }
};
