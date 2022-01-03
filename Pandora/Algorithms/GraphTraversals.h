#pragma once
#include <limits.h>
#include <iostream>

// Inorder Successor: Node that is the smallest among all larger nodes of target node.
// Inorder Predecessor: Node that is the largest among all small nodes of target node.

namespace GraphTraversals
{
    struct GraphNode
    {
        GraphNode(int data) : m_Data(data) { }

        int m_Data;
        GraphNode* m_LeftNode = nullptr;
        GraphNode* m_RightNode = nullptr;
    };

    GraphNode* g_RootNode = nullptr;
    GraphNode* g_SecondTraversalNode = nullptr;

    GraphNode* FindNode(GraphNode* node, int targetData)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->m_Data == targetData)
        {
            return node;
        }

        GraphNode* leftResult = FindNode(node->m_LeftNode, targetData);
        GraphNode* rightResult = FindNode(node->m_RightNode, targetData);

        // If both are null, the node does not exist.
        if (leftResult == nullptr && rightResult == nullptr)
        {
            return nullptr;
        }

        // If only one side is null, then the node was found in the other subtree. Hence, result the result of recursive call to that subtree.
        else if (rightResult == nullptr)
        {
            return leftResult;
        }
        else
        {
            rightResult;
        }
    }

    void NextGreaterValueNode(GraphNode* node, int targetNode)
    {
        if (node == nullptr)
        {
            return;
        }

        // When we find a node having value greater than target node, then there is no point heading right further as we will only find nodes with higher values.
        // Therefore, we traverse left instead.
        if (node->m_Data > targetNode)
        {
            g_SecondTraversalNode = node;
            NextGreaterValueNode(node->m_LeftNode, targetNode);
        }
        else
        {
            NextGreaterValueNode(node->m_RightNode, targetNode);
        }
    }

    void NextSmallerValueNode(GraphNode* node, int targetNode)
    {
        if (node == nullptr)
        {
            return;
        }

        // Remember that the inorder successor of a node is smaller than the node itself.
        // Head left whenever our current node is larger than the target node.
        // Whenever the target node is larger than our current node, we head right immediately and save the traversal result. 
        if (targetNode > node->m_Data)
        {
            g_SecondTraversalNode = node;
            NextSmallerValueNode(node->m_RightNode, targetNode);
        }
        else // Else, we keep heading left.
        {
            NextSmallerValueNode(node->m_LeftNode, targetNode);
        }
    }

    GraphNode* RightSmallest(GraphNode* node)
    {
        // Shift node to right child.
        GraphNode* currentNode = node->m_RightNode;

        // Keep on shifting node left until we find a node with no left child.
        while (currentNode->m_LeftNode != nullptr)
        {
            currentNode = currentNode->m_LeftNode;
        }

        return currentNode;
    }

    GraphNode* LeftLargest(GraphNode* node)
    {
        // Shift node to the left child.
        GraphNode* currentNode = node->m_LeftNode;

        while (currentNode->m_RightNode != nullptr)
        {
            currentNode = currentNode->m_RightNode;
        }

        return currentNode;
    }



    int GetInorderPredecessor(int targetNode)
    {
        // Find a node having data equal to the requested data.
        GraphNode* foundNode = FindNode(g_RootNode, targetNode);

        // If the left subtree of the node is not null, the inorder predecessor will definitely lie on the left subtree's greatest value.
        if (foundNode->m_LeftNode != nullptr)
        {
            return LeftLargest(foundNode)->m_Data;
        }
        else
        {
            // If the left subtree of the node is null, we run a traversal from the root looking value just smaller than the given node.
            NextSmallerValueNode(g_RootNode, targetNode);
            return g_SecondTraversalNode->m_Data;
        }
    }

    int GetInorderSuccessor(int targetNode)
    {
        // Find a node having data equal to the requested data.
        GraphNode* foundNode = FindNode(g_RootNode, targetNode);

        // If the right child of the node is not null, then the inorder successor will definitely lie on the right side having value equal to the smallest node 
        // in the right subtree.
        if (foundNode->m_RightNode != nullptr)
        {
            return RightSmallest(foundNode)->m_Data;
        }
        else
        {
            // If the right side of the node is null, we run a traversal from the root looking for a value just greater than the given node.
            NextGreaterValueNode(g_RootNode, targetNode);
            return g_SecondTraversalNode->m_Data;
        }
    }

    void TestCases_Traversal()
    {
        g_RootNode = new GraphNode(6);
        g_RootNode->m_LeftNode = new GraphNode(4);
        g_RootNode->m_RightNode = new GraphNode(10);
        g_RootNode->m_LeftNode->m_LeftNode = new GraphNode(1);
        g_RootNode->m_LeftNode->m_RightNode = new GraphNode(5);
        g_RootNode->m_RightNode->m_RightNode = new GraphNode(12);
        g_RootNode->m_RightNode->m_LeftNode = new GraphNode(8);
        g_RootNode->m_RightNode->m_LeftNode->m_LeftNode = new GraphNode(7);
        g_RootNode->m_RightNode->m_LeftNode->m_RightNode = new GraphNode(9);

        // Remember that the rightmost node of a treee is the greatest node in the tree and hence an inorder successor cannot exist. 
        // std::cout << "Inorder Predeccesor: " << GetInorderSuccessor(5) << "\n";
        std::cout << "Inorder Successor: " << GetInorderPredecessor(7) << "\n";
    }
}