class Solution {
    
    struct Range {
      int r, c;
      Range(int r, int c) : r(r), c(c) {}
      
      void join(int r1, int c1) {
         r = min(r, r1);
         c = min(c, c1);
      }
    };
    
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        Range a(m, n);
        for (auto& op : ops) {
            a.join(op[0], op[1]);
        }
        return a.r * a.c;
    }
};
