#include "ListNode.hpp"
#include "PrintUtil.hpp"

// swap the linked list such that: 1->2->3->4 => 2->1->3->4
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(-1, head);
        ListNode* next = dummy.next;
        ListNode* prev = &dummy;
        while (next != nullptr)
        {
            ListNode* curr = next;
            bool needSwap = curr->next != nullptr;
            if (needSwap)
            {
                // dummy->2->1 (prev) ->3 (curr) -> 4 -> ...
                next = curr->next->next;
                prev->next = curr->next;
                curr->next->next = curr;
                curr->next = next;
                prev = curr;
            }
            else
            {
                next = curr->next;
            }
        }

        return dummy.next;
    }
};

int main ()
{
    Solution s;
    PrintUtil printUtil;

    // Test 1:
    ListNode* n11 = new ListNode(1);
    ListNode* n12 = new ListNode(2);
    ListNode* n13 = new ListNode(3);
    n11->next = n12;
    n12->next = n13;
    printUtil.printListNode(s.swapPairs(n11));

    // Test 2:
    ListNode* n21 = new ListNode(1);
    ListNode* n22 = new ListNode(2);
    ListNode* n23 = new ListNode(3);
    ListNode* n24 = new ListNode(4);
    n21->next = n22;
    n22->next = n23;
    n23->next = n24;
    printUtil.printListNode(s.swapPairs(n21));

    // Test 3:
    ListNode* n31 = new ListNode(1);
    ListNode* n32 = new ListNode(2);
    ListNode* n33 = new ListNode(3);
    ListNode* n34 = new ListNode(4);
    ListNode* n35 = new ListNode(5);
    n31->next = n32;
    n32->next = n33;
    n33->next = n34;
    n34->next = n35;
    printUtil.printListNode(s.swapPairs(n31));
}