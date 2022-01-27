#pragma once
#include <utility>

namespace UnivalTree
{
    struct UnivalNode
    {
        int m_Value;
        UnivalNode* m_Left;
        UnivalNode* m_Right;
    };

    // A tree is unival when all values in the tree are equal. https://www.dailycodingproblem.com/blog/unival-trees/
    // Note that the root cannot be a unival tree if any subtree of said root violates the same value rule. 
    int CountUnivalSubtrees(UnivalNode* root)
    {
        std::pair<int, bool> finalCount = Helper(root);
        return finalCount.first;
    }

    // Also returns number of unival subtrees, and where it is itself a unival tree.
    std::pair<int, bool> Helper(UnivalNode* root)
    {
        if (root == nullptr)
        {
            return { 0, true }; // Null nodes are also inherently unival trees. 
        }

        std::pair<int, bool> leftTreeUnival = Helper(root->m_Left);
        std::pair<int, bool> rightTreeUnival = Helper(root->m_Right);

        int totalCount = leftTreeUnival.first + rightTreeUnival.first;

        if (leftTreeUnival.second && rightTreeUnival.second)
        {
            if (root->m_Left != nullptr && root->m_Value != root->m_Left->m_Value)
            {
                return { totalCount, false };
            }
            
            if (root->m_Right != nullptr && root->m_Value != root->m_Right->m_Value)
            {
                return { totalCount, false };
            }

            return { totalCount + 1, true };
        }

        return { totalCount, false };
    }

}