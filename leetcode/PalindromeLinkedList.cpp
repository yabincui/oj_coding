/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 class Solution {
    
    int getLength(ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }
    
    ListNode* splitList(ListNode* head, int splitPos) {
        ListNode** pp = &head;
        for (int i = 0; i < splitPos; ++i) {
            pp = &((*pp)->next);
        }
        ListNode* res = *pp;
        *pp = nullptr;
        return res;
    }
    
    ListNode* concat(ListNode* a, ListNode* b) {
        ListNode** pp = &a;
        while (*pp != nullptr) {
            pp = &((*pp)->next);
        }
        *pp = b;
        return a;
    }
    
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur != nullptr) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
    
    bool checkEqual(ListNode* a, ListNode* b) {
        while (a != nullptr && b != nullptr) {
            if (a->val != b->val) {
                return false;
            }
            a = a->next;
            b = b->next;
        }
        return a == nullptr && b == nullptr;
    }
    
public:
    bool isPalindrome(ListNode* head) {
        int n = getLength(head);
        if (n <= 1) return true;
        ListNode* mid = nullptr;
        ListNode* left = head;
        ListNode* right = splitList(head, n / 2);
        if (n % 2 != 0) {
            mid = right;
            right = mid->next;
        }
        right = reverseList(right);
        bool equal = checkEqual(left, right);
        right = reverseList(right);
        if (mid) {
            mid->next = right;
        } else {
            mid = right;
        }
        concat(head, mid);
        return equal;
    }
};