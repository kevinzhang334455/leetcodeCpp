#include "ListNode.hpp"
#pragma once

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class PrintUtil
{
public:
    static void printListNode(ListNode* head);
    template <class T> static void printVectorOf(vector<T> items);
    template <class T> static void printVectorVectorOf(vector<vector<T>> items);
};

void PrintUtil::printListNode(ListNode* head)
{
    if (head == nullptr)
    {
        cout << endl;
        return;
    }

    ListNode* curr = head;
    while (curr != nullptr)
    {
        cout << curr->val << ' ';
        curr = curr->next;
    }

    cout << endl;
}

template <class T> void PrintUtil::printVectorOf(vector<T> items)
{
    for (auto item : items)
    {
        cout << item << ' ';
    }

    cout << endl;
}

template <class T> void PrintUtil::printVectorVectorOf(vector<vector<T>> items)
{
    for (auto vec : items)
    {
        for (auto item : vec)
        {
            cout << item << ' ';
        }
        cout << endl;
    }

    cout << endl;
}