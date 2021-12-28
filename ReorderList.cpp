#include "ListNode.hpp"
#include <iostream>

using namespace std;

// You are given the head of a singly linked-list. The list can be represented as:

// L0 → L1 → … → Ln - 1 → Ln
// Reorder the list to be on the following form:

// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
// You may not modify the values in the list's nodes. Only nodes themselves may be changed.

class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        ListNode* p1 = head, *p2 = head;
        while (p1 != nullptr && p1->next != nullptr && p1->next->next != nullptr) {
            p1 = p1->next->next;
            p2 = p2->next;
        }

        ListNode* curr = p2->next;
        p2->next = nullptr;
        ListNode* prev = nullptr;

        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        ListNode* rcurr = prev;
        curr = head;

        while (rcurr != nullptr) {
            ListNode* rnext = rcurr->next;
            ListNode* next = curr->next;
            curr->next = rcurr;
            rcurr->next = next;
            curr = next;
            rcurr = rnext;
        }
    }
};

int main() {
    Solution s;
    ListNode* h1 = new ListNode(1);
    ListNode* h2 = new ListNode(2);
    ListNode* h3 = new ListNode(3);
    ListNode* h4 = new ListNode(4);
    ListNode* h5 = new ListNode(5);
    h1->next = h2;
    h2->next = h3;
    h3->next = h4;
    h4->next = h5;

    s.reorderList(h1);
    ListNode* curr = h1;
    while (curr != nullptr) {
        cout << curr->val << ' ';
        curr = curr->next;
    }

    cout << endl;
}