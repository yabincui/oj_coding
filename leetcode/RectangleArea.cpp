class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int a1 = (C - A) * (D - B);
        int a2 = (G - E) * (H - F);
        int sub = 0;
        int left = max(A, E);
        int right = min(C, G);
        int bottom = max(B, F);
        int top = min(D, H);
        if (left < right && bottom < top) {
            sub = (right - left) * (top - bottom);
        }
        return a1 - sub + a2;
    }
};
