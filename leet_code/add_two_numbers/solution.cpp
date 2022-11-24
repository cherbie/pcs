#include <bits/stdc++.h>
#include <sstream>

#define DEBUG

namespace
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *sumNode = new ListNode();
        ListNode *rootNode = sumNode;
        int modulo = 0;
        while (l1 != nullptr || l2 != nullptr)
        {
            if (l1 != nullptr)
            {
                sumNode->val += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr)
            {
                sumNode->val += l2->val;
                l2 = l2->next;
            }
            modulo = sumNode->val / 10;
            sumNode->val %= 10;
            if (l1 != nullptr || l2 != nullptr || modulo > 0)
            {
                sumNode->next = new ListNode(modulo);
                sumNode = sumNode->next;
            }
        }
        return rootNode;
    }

#ifdef DEBUG
    std::stringstream printListNodeArray(ListNode *node)
    {
        std::stringstream ss = std::stringstream();
        ss << "[";
        while (node != nullptr)
        {
            ss << node->val << ",";
            node = node->next;
        }
        ss << "]";
        return ss;
    }

    ListNode *makeListNodeArray(std::vector<int> arrayValues)
    {
        ListNode *node = nullptr;
        auto valueIt = arrayValues.rbegin();
        while (valueIt != arrayValues.rend())
        {
            node = new ListNode(*valueIt, node);
            valueIt++;
        }
        return node;
    }
#endif // ifdef DEBUG
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    std::cout << "[2,4,3] + [5,6,4] =" << std::endl;
#endif
    ListNode *sum = addTwoNumbers(makeListNodeArray(std::vector<int>{2, 4, 3}), makeListNodeArray(std::vector<int>{5, 6, 4}));
#ifdef DEBUG
    std::cout << printListNodeArray(sum).str()
              << std::endl;
#endif // ifdef DEBUG

#ifdef DEBUG
    std::cout << "[9,9,9,9] + [9,9,9] =" << std::endl;
#endif
    sum = addTwoNumbers(makeListNodeArray(std::vector<int>{9, 9, 9, 9}), makeListNodeArray(std::vector<int>{9, 9, 9}));
#ifdef DEBUG
    std::cout << printListNodeArray(sum).str()
              << std::endl;
#endif // ifdef DEBUG
    return 0;
}
