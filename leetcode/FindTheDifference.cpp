// 389. Find the Difference.
typedef unsigned long long u64;
typedef unsigned int u32;

class Solution {
public:

    class Rect {
    public:
        int bottom, left, top, right;
        Rect() {}
        Rect(vector<int>& r)
            : bottom(r[0]), left(r[1]), top(r[2]), right(r[3]) {}
        
        bool operator==(const Rect& r) const {
            return bottom == r.bottom && left == r.left && top == r.top &&
                right == r.right;
        }
        bool covers(const Rect& r) const {
            return bottom <= r.bottom && left <= r.left && top >= r.top &&
                right >= r.right;
        }
        bool overlaps(const Rect& r) const {
            if (bottom >= r.top || top <= r.bottom) {
                return false;
            }
            if (left >= r.right || right <= r.left) {
                return false;
            }
            return true;
        }
    };
    
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        if (n == 0) {
            return false;
        }
        vector<Rect> rects;
        for (int i = 0; i < n; ++i) {
            rects.emplace_back(rectangles[i]);
        }
        Rect r = rects[0];
        for (int i = 1; i < n; ++i) {
            r.bottom = min(r.bottom, rects[i].bottom);
            r.left = min(r.left, rects[i].left);
            r.top = max(r.top, rects[i].top);
            r.right = max(r.right, rects[i].right);
        }
        unordered_map<u64, int> hit_map;
        for (auto& a : rects) {
            hit_map[getP(a.bottom, a.left)]++;
            hit_map[getP(a.bottom, a.right)]++;
            hit_map[getP(a.top, a.left)]++;
            hit_map[getP(a.top, a.right)]++;
        }
        for (auto& pair : hit_map) {
            int y, x;
            getPos(pair.first, &y, &x);
            if ((y == r.bottom || y == r.top) && (x == r.left || x == r.right)) {
                if (pair.second != 1) {
                    printf("y = %d, x = %d, count = %d\n", y, x, pair.second);
                    return false;
                }
            } else {
                if (pair.second != 2 && pair.second != 4) {
                    printf("t2, y = %d, x = %d, count = %d\n", y, x, pair.second);
                    return false;
                }
            }
        }
        u64 total_area = (u64)(r.top - r.bottom) * (r.right - r.left);
        u64 sum_area = 0;
        for (auto& r : rects) {
            u64 a = (u64)(r.top - r.bottom) * (r.right - r.left);
            if (a + sum_area < sum_area) {
                return false;
            }
            sum_area += a;
        }
        printf("sum_area = %lld, total_area = %lld\n", sum_area, total_area);
        return sum_area == total_area;
    }

    u64 getP(u32 y, u32 x) {
        return ((u64)y << 32) | x;
    }
    
    void getPos(u64 p, int* y, int* x) {
        *y = (int)(p >> 32);
        *x = (int)p;
    }

    bool isRectangleCover2(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        if (n == 0) {
            return false;
        }
        vector<Rect> rects;
        for (int i = 0; i < n; ++i) {
            rects.emplace_back(rectangles[i]);
        }
        if (hasOverlap(rects)) {
            return false;
        }
        //printf("no overlap\n");
        Rect r = rects[0];
        for (int i = 1; i < n; ++i) {
            r.bottom = min(r.bottom, rects[i].bottom);
            r.left = min(r.left, rects[i].left);
            r.top = max(r.top, rects[i].top);
            r.right = max(r.right, rects[i].right);
        }
        printf("n = %d, r = %d, %d, %d, %d\n",
            n, r.bottom, r.left, r.top, r.right);
        vector<Rect*> s;
        for (int i = 0; i < n; ++i) {
            s.push_back(&rects[i]);
        }
        return canFill(s.data(), n, r);
    }
    
    bool hasOverlap(const vector<Rect>& s) {
        for (int i = 0; i < s.size(); ++i) {
            for (int j = i + 1; j < s.size(); ++j) {
                if (s[i].overlaps(s[j])) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool canFill(Rect** s, int n, Rect& r) {
        //printf("n = %d\n", n);
        if (n == 0) {
            //printf("can't fill %d, %d, %d, %d\n",
            //    r.bottom, r.left, r.top, r.right);
            return false;
        }
        if (n == 1) {
            bool res = s[0]->covers(r);
            if (!res) {
                //printf("s[0] = %d, %d, %d, %d, r = %d, %d, %d, %d\n",
                //    s[0]->bottom, s[0]->left, s[0]->top, s[0]->right,
                //    r.bottom, r.left, r.top, r.right);
            }
            return res;
        }
        // split into two parts.
        if (r.left + 1 < r.right) {
            int mid = (r.left + r.right) / 2;
            if (r.left < mid) {
                int tmp = r.right;
                r.right = mid;
                int count = selRect(s, n, r);
                if (!canFill(s, count, r)) {
                    return false;
                }
                r.right = tmp;
            }
            if (mid < r.right) {
                int tmp = r.left;
                r.left = mid;
                int count = selRect(s, n, r);
                if (!canFill(s, count, r)) {
                    return false;
                }
                r.left = tmp;
            }
        } else if (r.bottom + 1 < r.top) {
            int mid = (r.bottom + r.top) / 2;
            if (r.bottom < mid) {
                int tmp = r.top;
                r.top = mid;
                int count = selRect(s, n, r);
                if (!canFill(s, count, r)) {
                    return false;
                }
                r.top = tmp;
            }
            if (mid < r.top) {
                int tmp = r.bottom;
                r.bottom = mid;
                int count = selRect(s, n, r);
                if (!canFill(s, count, r)) {
                    return false;
                }
                r.bottom = tmp;
            }
        }
        return true;
    }
    
    int selRect(Rect** s, int n, Rect& r) {
        int count = 0;
        Rect* tmp;
        for (int i = 0; i < n; ++i) {
            //printf("s[%d] = %d, %d, %d, %d, r = %d, %d, %d, %d ",
            //        i, s[i]->bottom, s[i]->left, s[i]->top, s[i]->right,
            //        r.bottom, r.left, r.top, r.right);
            if (s[i]->overlaps(r)) {
                if (i == count) {
                    ++count;
                } else {
                    //printf("overlaps\n");
                    tmp = s[count];
                    s[count++] = s[i];
                    s[i] = tmp;
                }
            } else {
                //printf("no overlap\n");
            }
        }
        //printf("count = %d\n", count);
        return count;
    }
};
