// 407. Trapping Rain Water II
typedef unsigned long long u64;
class Solution {
public:
    struct Node {
      int h;
      int r, c;
      
      Node() {}
      Node(int r, int c, int h) : r(r), c(c), h(h) {}
    };
    
    static bool compareNode(Node* n1, Node* n2) {
        return n1->h < n2->h;
    }
    
    int dr[4] = {-1, 0, 0, 1};
    int dc[4] = {0, -1, 1, 0};

    int trapRainWater(vector<vector<int>>& heightMap) {
        int rows = heightMap.size();
        if (rows == 0) {
            return 0;
        }
        int cols = heightMap[0].size();
        if (rows * cols == 0) {
            return 0;
        }
        int edge_sum = 0;
        Node node_v[rows][cols];
        vector<Node*> nodes;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                node_v[i][j] = Node(i, j, heightMap[i][j]);
                nodes.push_back(&node_v[i][j]);
                edge_sum += heightMap[i][j];
            }
        }
        sort(nodes.begin(), nodes.end(), compareNode);
        bool nowater[rows][cols];
        memset(nowater, false, sizeof(nowater));
        int nowater_count = 0;
        u64 sum = 0;
        int prev_h = 0;
        //printf("edge_sum = %d\n", edge_sum);
        for (int t = 0; t < nodes.size();) {
            int h = nodes[t]->h;
            u64 add_sum = (u64)(rows * cols - nowater_count) * (h - prev_h);
            sum += add_sum;
            //printf("prev_h = %d, h = %d, nowater_count = %d, add_sum %lld, sum = %lld\n", prev_h, h, nowater_count,
            //        add_sum, sum);
            prev_h = h;
            
            queue<Node*> q;
            while (t < nodes.size() && nodes[t]->h == h) {
                q.push(nodes[t]);
                t++;
            }
            while (!q.empty()) {
                Node* cur = q.front(); q.pop();
                if (cur->h > h || nowater[cur->r][cur->c]) {
                    continue;
                }
                for (int i = 0; i < 4; ++i) {
                    int nr = cur->r + dr[i];
                    int nc = cur->c + dc[i];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || nowater[nr][nc]) {
                        nowater[cur->r][cur->c] = true;
                        nowater_count++;
                        break;
                    }
                }
                if (nowater[cur->r][cur->c]) {
                    //printf("mark point %d, %d\n", cur->r, cur->c);
                    for (int i = 0; i < 4; ++i) {
                        int nr = cur->r + dr[i];
                        int nc = cur->c + dc[i];
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                            //printf("try node_v[%d][%d], %d, %d\n", nr, nc, node_v[nr][nc].r, node_v[nr][nc].c);
                            q.push(&node_v[nr][nc]);
                        }
                    }
                }
            }
        }
        return (int)(sum - edge_sum);
    }
};
