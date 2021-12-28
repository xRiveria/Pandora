#pragma once

namespace LinkedLists
{
    struct Node
    {
        int m_Data;
        Node* m_NextNode;
    };

    // Assumes both nodes are already sorted. 
    Node* MergeLinkedListsAndSort(Node* headA, Node* headB)
    {
        if (headA == nullptr)
        {
            return headB;
        }

        if (headB == nullptr)
        {
            return headA;
        }

        // Return A if data contained is smaller than B, else return B. Recursively iterate.
        if (headA->m_Data < headB->m_Data)
        {
            headA->m_NextNode = MergeLinkedListsAndSort(headA->m_NextNode, headB);
            return headA;
        }
        else
        {
            headB->m_NextNode = MergeLinkedListsAndSort(headA, headB->m_NextNode);
            return headB;
        }
    }
}