#pragma once
#include <vector>
#include <queue>

namespace Trees
{
    class TreeNode
    {
    public:
        TreeNode(int value)
        {
            this->m_Left = nullptr;
            this->m_Right = nullptr;
            this->m_Value = value;
        }

    public:
        TreeNode* m_Left = nullptr;
        TreeNode* m_Right = nullptr;
        int m_Value = 0;
    };

    class BinarySearchTree
    {
    public:
        BinarySearchTree()
        {
            this->m_Root = nullptr;
        }

        BinarySearchTree* Insert(int value)
        {
            TreeNode* newNode = new TreeNode(value);
            if (this->m_Root == nullptr)
            {
                this->m_Root = newNode;
            }
            else
            {
                TreeNode* currentNode = this->m_Root;
                while (true)
                {
                    // Left
                    if (value < currentNode->m_Value)
                    {
                        if (currentNode->m_Left == nullptr)
                        {
                            currentNode->m_Left = newNode;
                            return this;
                        }

                        currentNode = currentNode->m_Left;
                    }
                    else
                    {
                        //Right
                        if (currentNode->m_Right == nullptr)
                        {
                            currentNode->m_Right = newNode;
                            return this;
                        }

                        currentNode = currentNode->m_Right;
                    }
                }
            }
        }

        TreeNode* LookUp(int value)
        {
            if (this->m_Root == nullptr)
            {
                return nullptr;
            }

            TreeNode* currentNode = this->m_Root;
            while (currentNode != nullptr)
            {
                if (value < currentNode->m_Value)
                {
                    currentNode = currentNode->m_Left;
                }
                else if (value > currentNode->m_Value)
                {
                    currentNode = currentNode->m_Right;
                }
                else if (value == currentNode->m_Value)
                {
                    return currentNode;
                }
            }

            return nullptr;
        }

        TreeNode* GetInorderSuccessor(TreeNode* node)
        {
            TreeNode* currentNode = node;

            while (currentNode != nullptr && currentNode->m_Left != nullptr)
            {
                currentNode = currentNode->m_Left;
            }

            return currentNode;
        }

        void Remove(int value)
        {
            if (m_Root == nullptr)
            {
                return;
            }

            TreeNode* currentNode = m_Root;
            TreeNode* parentNode = nullptr;

            // Find our node.
            while (currentNode != nullptr)
            {
                if (value < currentNode->m_Value)
                {
                    parentNode = currentNode;
                    currentNode = currentNode->m_Left;
                }
                else if (value > currentNode->m_Value)
                {
                    parentNode = currentNode;
                    currentNode = currentNode->m_Right;
                }
                else if (value == currentNode->m_Value)
                {
                    break;
                }
            }

            if (currentNode == nullptr)
            {
                return;
            }

            // Case 1: The found node has no children at all. Hence, it is a leaf node. Simply remove it.
            if (currentNode->m_Left == nullptr && currentNode->m_Right == nullptr)
            {
                // If the node to be deleted is not a root node, then set its parent left/right child to null.
                if (currentNode != m_Root)
                {
                    if (parentNode->m_Left == currentNode)
                    {
                        parentNode->m_Left = nullptr;
                    }
                    else
                    {
                        parentNode->m_Right = nullptr;
                    }
                }
                else // If the tree has only a root node, set it to null.
                {
                    m_Root = nullptr;
                }

                // Deallocate the memory.
                delete currentNode;
            }

            // Case 2: Node to be deleted has 2 children.
            else if (currentNode->m_Left != nullptr && currentNode->m_Right != nullptr)
            {
                // Find inorder successor.
                TreeNode* inorderSuccessor = GetInorderSuccessor(currentNode->m_Right);

                // Store successor value.
                int value = inorderSuccessor->m_Value;

                // Recursively delete the successor. Note that the successor will have at most one child (right child).
                Remove(inorderSuccessor->m_Value);

                // Copy value of the successor to the current node.
                currentNode->m_Value = value;
            }

            // Case 3: Node to be deleted has only one child.
            else
            {
                TreeNode* childNode = (currentNode->m_Left != nullptr) ? currentNode->m_Left : currentNode->m_Right;

                // If the node to be deleted is not a root node, set its parent to its child.
                if (currentNode != m_Root)
                {
                    if (currentNode == parentNode->m_Left)
                    {
                        parentNode->m_Left = childNode;
                    }
                    else
                    {
                        parentNode->m_Right = childNode;
                    }
                }
                else
                {
                    // If the node to be deleted is a root node, then set the root to the child/
                    m_Root = childNode;
                }

                // Deallocate.
                delete currentNode;
            }
        }

        void BreadthFirstSearchRecursive()
        {
            std::vector<int> finalList;
            std::queue<TreeNode*> currentQueue;
            currentQueue.push(m_Root);

            BreadthFirstSearch_(finalList, currentQueue);

            for (int i : finalList)
            {
                std::cout << i << " ";
            }

            std::cout << std::endl;
        }

        std::vector<int> BreadthFirstSearch_(std::vector<int>& finalList, std::queue<TreeNode*>& currentQueue)
        {
            if (currentQueue.empty())
            {
                return finalList;
            }

            TreeNode* currentNode = currentQueue.front();
            currentQueue.pop();
            finalList.push_back(currentNode->m_Value);

            if (currentNode->m_Left != nullptr)
            {
                currentQueue.push(currentNode->m_Left);
            }

            if (currentNode->m_Right != nullptr)
            {
                currentQueue.push(currentNode->m_Right);
            }

            return BreadthFirstSearch_(finalList, currentQueue);
        }

        std::vector<int> BreadthFirstSearchIterative()
        {
            std::vector<int> finalList;
            std::queue<TreeNode*> currentQueue;
            currentQueue.push(m_Root);

            while (!currentQueue.empty())
            {
                TreeNode* currentNode = currentQueue.front();
                currentQueue.pop();
                finalList.push_back(currentNode->m_Value);

                if (currentNode->m_Left != nullptr)
                {
                    currentQueue.push(currentNode->m_Left);
                }

                if (currentNode->m_Right != nullptr)
                {
                    currentQueue.push(currentNode->m_Right);
                }
            }

            for (int i : finalList)
            {
                std::cout << i << " ";
            }

            std::cout << std::endl;
            return finalList;
        }

        // DFS Traversal -> Inorder, PostOrder, PreOrder
        void DFS_InOrder()
        {
            std::vector<int> itemList;
            TraverseInOrder(m_Root, itemList);

            for (int i : itemList)
            {
                std::cout << i << " ";
            }

            std::cout << std::endl;
        }

        //       9
        //   4      20
        // 1   6  15  170
        void TraverseInOrder(TreeNode* node, std::vector<int>& itemList)
        {
            if (node->m_Left != nullptr)
            {
                TraverseInOrder(node->m_Left, itemList);
            }

            itemList.push_back(node->m_Value);

            if (node->m_Right != nullptr)
            {
                TraverseInOrder(node->m_Right, itemList);
            }
        }

        void DFS_PostOrder()
        {
            std::vector<int> itemList;
            TraversePostOrder(m_Root, itemList);

            for (int i : itemList)
            {
                std::cout << i << " ";
            }

            std::cout << std::endl;
        }

        void TraversePostOrder(TreeNode* node, std::vector<int>& itemList)
        {
            if (node->m_Left != nullptr)
            {
                TraversePostOrder(node->m_Left, itemList);
            }

            if (node->m_Right != nullptr)
            {
                TraversePostOrder(node->m_Right, itemList);
            }

            itemList.push_back(node->m_Value);
        }

        void DFS_PreOrder()
        {
            std::vector<int> itemList;
            TraversePreOrder(m_Root, itemList);

            for (int i : itemList)
            {
                std::cout << i << " ";
            }

            std::cout << std::endl;
        }

        void TraversePreOrder(TreeNode* node, std::vector<int>& itemList)
        {
            itemList.push_back(node->m_Value);

            if (node->m_Left != nullptr)
            {
                TraversePreOrder(node->m_Left, itemList);
            }

            if (node->m_Right != nullptr)
            {
                TraversePreOrder(node->m_Right, itemList);
            }
        }

    private:
        TreeNode* m_Root = nullptr;
    };


}