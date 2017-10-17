class Solution {
    
    struct Node {
        int start;
        int end;
        int top;
        
        Node() {}
        Node(int start, int end, int top) : start(start), end(end), top(top) {}
        
        bool intersect(int s, int e) {
            return !(start > e || end < s);
        }
    };
    
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        // height range for each pos.
        /*
            a map of (start, end, length). // insert or replace.  1000, use sorted array.
        
        */
        vector<Node> state;
        state.push_back(Node(0, 1000000000, 0));
        vector<int> res;
        int curHighest = 0;
        for (auto pair : positions) {
            int start = pair.first;
            int end = start + pair.second - 1;
            int heightBase = 0;
            for (Node n : state) {
                if (n.intersect(start, end)) {
                    heightBase = max(heightBase, n.top);
                }
            }
            Node newNode(start, end, heightBase + pair.second);
            curHighest = max(curHighest, newNode.top);
            res.push_back(curHighest);
            // add newNode to state.
            vector<Node> newState;
            bool pushed = false;
            for (Node n : state) {
                if (n.end < newNode.start) {
                    newState.push_back(n);
                } else if (n.end >= newNode.start) {
                    if (n.start < newNode.start) {
                        newState.push_back(Node(n.start, newNode.start - 1, n.top));
                    }
                    if (!pushed) {
                        newState.push_back(newNode);
                        pushed = true;
                    }
                    if (n.end > newNode.end) {
                        newState.push_back(Node(max(n.start, newNode.end + 1), n.end, n.top));
                    }
                }
            }
            state = newState;
        }
        return res;
    }
};