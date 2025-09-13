// key: BFS
class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        // Two steps:
        // 1. Find a 1 node, using BFS to find all 1s connected to it.
        // 2. Start from these 1s, using BFS to find another 1s in neighbors.
        if (grid.empty() or grid[0].empty()) {
            return 0;
        }
        int n = grid.size();
        int start_i = -1;
        int start_j = -1;
        for (int i = 0; i < n && start_i == -1; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    start_i = i;
                    start_j = j;
                    break;
                }
            }
        }
        if (start_i == -1) {
            return 0;
        }
        vector<pair<int, int>> q;
        q.push_back(make_pair(start_i, start_j));
        grid[start_i][start_j] = -1;
        int dr[] = {0, 0, -1, 1};
        int dc[] = {-1, 1, 0, 0};
        for (int pos = 0; pos < q.size(); pos++) {
            int r = q[pos].first;
            int c = q[pos].second;
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                    q.emplace_back(nr, nc);
                    grid[nr][nc] = -1;
                }
            }
        }
        int dist = 0;
        int pos = 0;
        while (true) {
            int end = q.size();
            if (pos == end) {
                break;
            }
            for (;pos < end; pos++) {
                int r = q[pos].first;
                int c = q[pos].second;
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] != -1) {
                        if (grid[nr][nc] == 1) {
                            return dist;
                        }
                        q.emplace_back(nr, nc);
                        grid[nr][nc] = -1;
                    }
                }
            }
            dist++;
        }
        return 0;
    }
};
