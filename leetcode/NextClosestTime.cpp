class Solution {
    
    struct Node {
        int hour;
        int minute;
        
        Node(int hour=0, int minute=0) : hour(hour), minute(minute) {}
        
        Node(const string& s) {
            hour = (s[0] - '0')  * 10 + (s[1] - '0');
            minute = (s[3] - '0') * 10 + (s[4] - '0');
        }
        
        string toString() const {
            char s[20];
            sprintf(s, "%02d:%02d", hour, minute);
            return s;
        }
        
        int distTo(const Node& to) {
            int a = hour * 60 + minute;
            int b = to.hour * 60 + to.minute;
            if (a < b) {
                return b - a;
            }
            return b + 24 * 60 - a;
        }
    };
    
    Node from;
    int minDist;
    Node minNode;
    
    void permute(vector<int>& v, int pos, int value) {
        if (pos == 4) {
            int hour = value / 100;
            int minute = value % 100;
            if (hour >= 24 || minute >= 60) return;
            Node node(value / 100, value % 100);
            int d = from.distTo(node);
            if (d < minDist) {
                minDist = d;
                minNode = node;
            }
            return;
        }
        for (int i = 0; i < 4; ++i) {
            int nValue = value * 10 + v[i];
            permute(v, pos + 1, nValue);
        }
    }
    
public:
    string nextClosestTime(string time) {
        minDist = INT_MAX;
        from = Node(time);
        vector<int> v;
        v.push_back(from.hour / 10);
        v.push_back(from.hour % 10);
        v.push_back(from.minute / 10);
        v.push_back(from.minute % 10);
        permute(v, 0, 0);
        return minNode.toString();
    }
};









