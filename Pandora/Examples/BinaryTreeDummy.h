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

        void BreadthFirstSearch()
        {
            std::vector<int> finalList;
            std::queue<TreeNode*> currentQueue;
            currentQueue.push(m_Root);

            BreadthFirstSearchRecursive(finalList, currentQueue);

            for (int i : finalList)
            {
                std::cout << i << " ";
            }

            std::cout << std::endl;
        }

        std::vector<int> BreadthFirstSearchRecursive(std::vector<int>& finalList, std::queue<TreeNode*>& currentQueue)
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

            return BreadthFirstSearchRecursive(finalList, currentQueue);
        }

    private:
        TreeNode* m_Root = nullptr;
    };


}