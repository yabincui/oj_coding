// 335. Self Crossing
    static constexpr int dx[4] = {0, -1, 0, 1};
    static constexpr int dy[4] = {1, 0, -1, 0};
    
class Solution {
private:
    enum { N, W, S, E};

    bool isHorizontal(int dir) {
        return dir == W || dir == E;    
    }
    
    struct Point {
      int64_t x, y;
      
      Point move(int dir, int64_t len) {
          Point new_p;
          new_p.x = x + dx[dir] * len;
          new_p.y = y + dy[dir] * len;
          return new_p;
      }
    };
    
    struct Line {
      bool horizontal;
      Point start, end;
      
      Line() {
          
      }
      Line(Point& a, Point& b) : start(a), end(b) {
          horizontal = a.y == b.y;
      }
      
      bool intersect(Line& o) {
          if (o.horizontal == horizontal) {
              return inLine(o.start) || inLine(o.end) || o.inLine(start) || o.inLine(end);
          }
          Point p;
          p.x = horizontal ? o.start.x : start.x;
          p.y = horizontal ? start.y : o.start.y;
          return inLine(p) && o.inLine(p);
      }
      
      bool inLine(Point& p) {
          if (horizontal) {
              return p.y == start.y && p.x >= min(start.x, end.x) && p.x <= max(start.x, end.x);
          }
          return p.x == start.x && p.y >= min(start.y, end.y) && p.y <= max(start.y, end.y);
      }
      
      string show() {
          char buf[40];
          snprintf(buf, sizeof(buf), "(%d,%d - %d,%d)", start.x, start.y, end.x, end.y);
          return buf;
      }
    };
    
    struct Wall {
      bool valid;
      Line line;
    };
    
public:
    bool isSelfCrossing(vector<int>& x) {
        // 1. At first the length of edge in vertial and horizontal directions should continuously increase.
        // 2. Otherwise, we have a strong limit in each directions.
        int horizon_limit = 0;
        int vertical_limit = 0;
        int dir = N;
        int break_pos = -1;
        Point cur_p;
        cur_p.x = cur_p.y = 0;
        for (int i = 0; i < x.size(); ++i) {
            if (isHorizontal(dir)) {
                if (x[i] <= horizon_limit) {
                    break_pos = i;
                    break;
                }
                horizon_limit = x[i];
            } else {
                if (x[i] <= vertical_limit) {
                    break_pos = i;
                    break;
                }
                vertical_limit = x[i];
            }
            cur_p = cur_p.move(dir, x[i]);
            dir = (dir + 1) % 4;
        }
        if (break_pos == -1) {
            return false;
        }
        printf("break_pos = %d\n", break_pos);
        deque<Line> walls;
        
        int cur_dir = dir;
        Point p = cur_p;
        for (int i = break_pos - 1; i >= 0 && i >= break_pos - 4; --i) {
            cur_dir = (cur_dir + 3) % 4;
            Point prev_p = cur_p.move((cur_dir + 2) % 4, x[i]);
            walls.push_front(Line(cur_p, prev_p));
            cur_p = prev_p;
        }
        
        cur_p = p;
        cur_dir = dir;
        for (int i = break_pos; i < x.size(); ++i) {
            Point next_p = cur_p.move(cur_dir, x[i]);
            Line line = Line(cur_p, next_p);
            //printf("i = %d, dir = %d, line = %s\n", i, cur_dir, line.show().c_str());
            int prev_dir = (cur_dir + 3) % 4;
            for (int i = 0; i < walls.size() - 1; ++i) {
                if (walls[i].intersect(line)) {
                    printf("walls[] is line %s, intersects with current line %s, i = %d\n", walls[i].show().c_str(), line.show().c_str(), i);
                    return true;
                }
            }
            walls.push_back(line);
            if (walls.size() > 5) {
                walls.pop_front();
            }
            /*
            for (int d = 0; d < 4; ++d) {
                if (d == prev_dir) continue;
                if (walls[d].line.intersect(line)) {
                    
                    return true;
                }
            }
            
            walls[cur_dir].valid = true;
            walls[cur_dir].line = line;
            */
            cur_p = next_p;
            cur_dir = (cur_dir + 1)  % 4;
        }
        return false;
    }
};
