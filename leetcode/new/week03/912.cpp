// error: wrong set loop edge case.
// quick sort
// 912. Sort an Array
class Solution {
   public:
    vector<int> sortArray(vector<int>& nums) {
        // quick sort
        if (nums.size() <= 1) {
            return nums;
        }
        quick_sort(nums.data(), nums.size());
        return nums;
    }

   private:
    void quick_sort(int* s, int n) {
        if (n <= 3) {
            small_sort(s, n);
            return;
        }
        // 5 2 3 1
        // pivot = 5
        // p = 1, q = 3, p moves to 4
        // swap 0 and 3, 1 2 3 5
        // sort 1 2 3
        int pivot = s[0];
        int* p = &s[1];
        int* q = &s[n - 1];
        while (p <= q) {
            // 0 ... p - 1 are all < pivot
            while (p <= q && *p < pivot) {
                p++;
            }
            // q + 1 ... n - 1 are all > pivot
            while (p <= q && *q > pivot) {
                q--;
            }
            // if p < q, p points to one >= pivot, q points to one <= pivot, swap them.
            // and adjust p and q.
            if (p <= q) {
                swap(*p, *q);
                p++;
                q--;
            }
        }
        // after while loop, 0 ... p - 1 contains all < pivot.
        // printf("p - 1 = %zu, *s=%d, *(p-1)=%d\n", (p - 1 - s), *s, *(p - 1));
        swap(*s, *(p - 1));

        quick_sort(s, p - 1 - s);

        quick_sort(p, s + n - p);
    }

    void small_sort(int* s, int n) {
        if (n == 2) {
            if (s[0] > s[1]) {
                swap(s[0], s[1]);
            }
        } else if (n == 3) {
            if (s[0] > s[1]) {
                swap(s[0], s[1]);
            }
            if (s[1] > s[2]) {
                swap(s[1], s[2]);
            }
            if (s[0] > s[1]) {
                swap(s[0], s[1]);
            }
        }
    }
};