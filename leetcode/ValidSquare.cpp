class Solution {
    
    struct Point {
        int x, y;
    
        Point(int x = 0, int y = 0) : x(x), y(y) {}
        
        double dist(const Point& other) {
            double dx = x - other.x;
            double dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }
    };
    
    static bool doubleEqual(double a, double b) {
        double diff = a - b;
        if (diff < 0) diff = -diff;
        return diff < 1e-6;
    }
    
    struct Line {
        Point p1, p2;
        Line() {}
        Line(Point p1, Point p2) : p1(p1), p2(p2) {}
        
        double getLength() {
            return p1.dist(p2);
        }
        
        bool has90Degree(const Line& other) {
            double x1 = p1.x - p2.x;
            double y1 = p1.y - p2.y;
            double x2 = other.p1.x - other.p2.x;
            double y2 = other.p1.y - other.p2.y;
            double sum = x1 * x2 + y1 * y2;
            return doubleEqual(sum, 0.0);
        }
    };
    
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<Point> v;
        v.push_back(Point(p1[0], p1[1]));
        v.push_back(Point(p2[0], p2[1]));
        v.push_back(Point(p3[0], p3[1]));
        v.push_back(Point(p4[0], p4[1]));
        int leftUp = 0;
        int rightBottom = 0;
        for (int i = 1; i < 4; ++i) {
            Point& p = v[i];
            if (p.x < v[leftUp].x || (p.x == v[leftUp].x && p.y < v[leftUp].y)) {
                leftUp = i;
            }
            if (p.x > v[rightBottom].x || (p.x == v[rightBottom].x && p.y > v[rightBottom].y)) {
                rightBottom = i;
            }
        }
        int mid0 = -1;
        int mid1 = -1;
        for (int i = 0; i < 4; ++i) {
            if (i != leftUp && i != rightBottom) {
                if (mid0 == -1) mid0 = i;
                else mid1 = i;
            }
        }
        vector<Line> lines;
        lines.push_back(Line(v[leftUp], v[mid0]));
        lines.push_back(Line(v[mid0], v[rightBottom]));
        lines.push_back(Line(v[rightBottom], v[mid1]));
        lines.push_back(Line(v[mid1], v[leftUp]));
        double d = lines[0].getLength();
        if (doubleEqual(d, 0)) {
            return false;
        }
        for (int i = 0; i < 4; ++i) {
            if (!doubleEqual(d, lines[i].getLength())) {
                return false;
            }
            if (!lines[i].has90Degree(lines[(i+1) % 4])) {
                return false;
            }
        }
        return true;
    }
};