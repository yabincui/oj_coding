class Solution {
    struct Point {
        int x, y;
        
        Point(int x, int y) : x(x), y(y) {
            
        }
        
        double dist(const Point& p) {
            int dx = x - p.x;
            int dy = y - p.y;
            return sqrt(dx * dx + dy * dy);
        }
    };
    
    bool doubleEqual(double d1, double d2) {
        double diff = d1 - d2;
        return diff > -1e-6 && diff < 1e-6;
    }
    
    int getCount(vector<double>& v) {
        int result = 0;
        double value = -1;
        int count = 0;
        for (int i = 0; i < v.size(); ++i) {
            if (doubleEqual(v[i], value)) {
                count++;
            } else {
                result += count * (count - 1);
                count = 1;
                value = v[i];
            }
        }
        result += count * (count - 1);
        return result;
    }
    
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        vector<Point> s;
        for (auto& pair : points) {
            s.push_back(Point(pair.first, pair.second));
        }
        int result = 0;
        for (int i = 0; i < s.size(); ++i) {
            vector<double> v;
            for (int j = 0; j < s.size(); ++j) {
                if (i == j) continue;
                v.push_back(s[i].dist(s[j]));
            }
            sort(v.begin(), v.end());
            int count = getCount(v);
            result += count;
        }
        return result;
    }
};
