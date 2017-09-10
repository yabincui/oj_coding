class Solution {
    struct Tree {
        int h;
        int r;
        int c;
        Tree(int h, int r, int c) : h(h), r(r), c(c) {}
    };
    
    int getDist(vector<vector<int>>& forest, int sr, int sc, int er, int ec) {
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};
        queue<pair<int, int>> q;
        if (forest[sr][sc] == 0) {
            return -1;
        }
        unordered_set<int> visited;
        q.push(make_pair(sr, sc));
        visited.insert((sr << 16) | sc);
        for (int d = 0; !q.empty(); d++) {
            int size = q.size();
            for (int t = 0; t < size; ++t) {
                pair<int, int> cur = q.front(); q.pop();
                //printf("d = %d, cur = %d, %d\n", d, cur.first, cur.second);
                if (cur.first == er && cur.second == ec) {
                    return d;
                }
                for (int i = 0; i < 4; ++i) {
                    int nr = cur.first + dr[i];
                    int nc = cur.second + dc[i];
                    //printf("nr = %d, nc = %d\n", nr, nc);
                    if (nr < 0 || nr >= forest.size() || nc < 0 || nc >= forest[0].size() || forest[nr][nc] == 0) {
                        continue;
                    }
                    int key = (nr << 16) | nc;
                    if (visited.find(key) != visited.end()) {
                        continue;
                    }
                    visited.insert(key);
                    q.push(make_pair(nr, nc));
                }
            }
        }
        return -1;
    }
    
public:
    int cutOffTree(vector<vector<int>>& forest) {
        int rows = forest.size();
        if (rows == 0) return 0;
        int cols = forest[0].size();
        if (cols == 0) return 0;
        vector<Tree> trees;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (forest[r][c] > 1) {
                    trees.emplace_back(forest[r][c], r, c);
                }
            }
        }
        auto compareTree = [](const Tree& t1, const Tree& t2) { return t1.h < t2.h; };
        sort(trees.begin(), trees.end(), compareTree);
        int result = 0;
        int cur_r = 0;
        int cur_c = 0;
        for (auto& tree : trees) {
            int d = getDist(forest, cur_r, cur_c, tree.r, tree.c);
            //printf("%d, %d -> %d, %d, d = %d\n", cur_r, cur_c, tree.r, tree.c, d);
            if (d == -1) return -1;
            result += d;
            cur_r = tree.r;
            cur_c = tree.c;
        }
        return result;
    }
};
