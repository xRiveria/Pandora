#pragma once
#include <iostream>

namespace AVL
{
    struct AVLNode
    {
        int m_Data;
        AVLNode* m_Parent;
        AVLNode* m_Left;
        AVLNode* m_Right;
        int m_Color; // 1-> Red, 0-> Black
    };

    class RedBlackTree
    {
    public:
        RedBlackTree()
        {
            m_Null = new AVLNode();
            m_Null->m_Color = 0;
            m_Null->m_Left = nullptr;
            m_Null->m_Right = nullptr;
            m_Root = m_Null;
        }

        void Preorder()
        {
            TraversePreorder(this->m_Root);
        }

        void Inorder()
        {
            TraverseInorder(this->m_Root);
        }

        void Postorder()
        {
            TraversePostorder(this->m_Root);
        }

        AVLNode* SearchTree(int K)
        {
            return Search(this->m_Root, K);
        }

        AVLNode* Minimum(AVLNode* node)
        {
            while (node->m_Left != m_Null)
            {
                node = node->m_Left;
            }

            return node;
        }

        AVLNode* Maximum(AVLNode* node)
        {
            while (node->m_Right != nullptr)
            {
                node = node->m_Right;
            }

            return node;
        }

        // Find the successor of a given node.
        AVLNode* Successor(AVLNode* node) // Successor is the left most node in the right subtree.
        {
            if (node->m_Right != nullptr)
            {
                return Minimum(node->m_Right);
            }
            // Else, locate a node with value just greater than the current node.
            // It is the lowest ancestor of X, whose left child is also an ancestor of X. 
            AVLNode* parentNode = node->m_Parent;
            while (parentNode != nullptr && node == parentNode->m_Right) // Go up the tree as long as our node is on the right subtree. 
            {
                node = parentNode;
                parentNode = parentNode->m_Parent;
            }

            return parentNode;
        }

        AVLNode* Predecessor(AVLNode* node)
        {
            if (node->m_Left != nullptr)
            {
                return Maximum(node->m_Left);
            }

            AVLNode* parentNode = node->m_Parent;
            while (parentNode != nullptr && node == parentNode->m_Left)
            {
                node = parentNode;
                parentNode = parentNode->m_Parent;
            }

            return parentNode;
        }

        // Rotate left at node X.
        void LeftRotate(AVLNode* rotatingNode)
        {
            AVLNode* stagingNode = rotatingNode->m_Right;

            // Attach the left subtree contents of the staging node to the node that was just rotated.
            rotatingNode->m_Right = stagingNode->m_Left; // Stick right pointer of the rotating node.
            if (stagingNode->m_Left != m_Null)
            {
                stagingNode->m_Left->m_Parent = rotatingNode; // Stick parent pointer of the left subtree. 
            }

            // Attach the rotating node's parent to the staging node (if it exists, otherwise we're just swapping nullptrs).
            stagingNode->m_Parent = rotatingNode->m_Parent;

            // If the rotating node had no parent to begin with, we set the new staging node that took its place as the new root of the tree.
            if (rotatingNode->m_Parent == nullptr)
            {
                this->m_Root = stagingNode;
            }
            else if (rotatingNode == rotatingNode->m_Parent->m_Left) // Else, if the node was on the left/right subtree, we set it the new node accordingly.
            {
                rotatingNode->m_Parent->m_Left = stagingNode;
            }
            else
            {
                rotatingNode->m_Parent->m_Right = stagingNode;
            }

            // Officially rotate. 
            stagingNode->m_Left = rotatingNode;
            rotatingNode->m_Parent = stagingNode;   
        }

        // Rotate right at node X.
        void RightRotate(AVLNode* rotatingNode)
        {
            AVLNode* stagingNode = rotatingNode->m_Left;
            rotatingNode->m_Left = stagingNode->m_Right;

            if (stagingNode->m_Right != nullptr)
            {
                stagingNode->m_Right->m_Parent = rotatingNode;
            }

            stagingNode->m_Parent = rotatingNode->m_Parent;

            if (stagingNode->m_Parent == m_Null)
            {
                this->m_Root = stagingNode;
            }
            else if (rotatingNode == rotatingNode->m_Parent->m_Right)
            {
                rotatingNode->m_Parent->m_Right = stagingNode;
            }
            else
            {
                rotatingNode->m_Parent->m_Left = stagingNode;
            }

            // Officially rotate.
            stagingNode->m_Right = rotatingNode;
            rotatingNode->m_Parent = stagingNode;
        }

        // Insert the key to the tree in its appropriate position, and then fix the tree.
        void Insert(int key)
        {
            // Ordinary BST insertion.
            AVLNode* node = new AVLNode();
            node->m_Parent = nullptr;
            node->m_Data = key;
            node->m_Left = m_Null;
            node->m_Right = m_Null;
            node->m_Color = 1; // New nodes are always red.

            AVLNode* stagingNode = nullptr;
            AVLNode* rootNode = this->m_Root;

            while (rootNode != m_Null)
            {
                stagingNode = rootNode;
                if (node->m_Data < rootNode->m_Data)
                {
                    rootNode = rootNode->m_Left;
                }
                else
                {
                    rootNode = rootNode->m_Right;
                }
            }

            // stagingNode should end at the appropriate place to insert our newNode.
            node->m_Parent = stagingNode;
            if (stagingNode == nullptr)
            {
                this->m_Root = stagingNode;
            }
            else if (node->m_Data < stagingNode->m_Data)
            {
                stagingNode->m_Left = node;
            }
            else
            {
                stagingNode->m_Right = node;
            }

            // If the new node is a root node, simply return.
            if (node->m_Parent == nullptr)
            {
                node->m_Color = 0; // Root nodes are black.
                return;
            }

            // If the grandparent is null, simply return.
           if (node->m_Parent->m_Parent == nullptr)
           {
               return;
           }

           // Rebalance the tree (recolor/rotatations).
           FixInsert(node);
        }

        AVLNode* GetRoot()
        {
            return this->m_Root;
        }

        // Delete the node from the tree.
        void DeleteNode(int data)
        {
            DeleteNodeHelper(this->m_Root, data);
        }

        // Print the tree structure on the screen.
        void PrettyPrint()
        {
            if (m_Root)
            {
                PrintHelper(this->m_Root, "", true);
            }
        }

    private:
        // Initializes the nodes with appropriate values. All the pointers are set to point to nullptrs.
        void InitializeNullNode(AVLNode* node, AVLNode* parentNode)
        {
            node->m_Data = 0;
            node->m_Parent = parentNode;
            node->m_Left = nullptr;
            node->m_Right = nullptr;
            node->m_Color = 0;
        }

        void TraversePreorder(AVLNode* rootNode)
        {
            if (rootNode != nullptr)
            {
                std::cout << rootNode->m_Data << " ";
                TraversePreorder(rootNode->m_Left);
                TraversePreorder(rootNode->m_Right);
            }
        }

        void TraverseInorder(AVLNode* rootNode)
        {
            if (rootNode != nullptr)
            {
                TraverseInorder(rootNode->m_Left);
                std::cout << rootNode->m_Data << " ";
                TraverseInorder(rootNode->m_Right);
            }
        }

        void TraversePostorder(AVLNode* rootNode)
        {
            if (rootNode != nullptr)
            {
                TraversePostorder(rootNode->m_Left);
                TraversePostorder(rootNode->m_Right);
                std::cout << rootNode->m_Data << " ";
            }
        }

        AVLNode* Search(AVLNode* node, int key)
        {
            if (node == m_Null || key == node->m_Data)
            {
                return node;
            }

            if (key < node->m_Data)
            {
                return Search(node->m_Left, key);
            }

            return Search(node->m_Right, key);
        }

        // Fix the red-black tree after insertion.
        // Black = 0, Red = 1
        // 4 Scenarios:
        // 1) Z = Root -> color Black
        // 2) Z.uncle = Red -> Recolor
        // 3) Z.uncle = Black (Triangle) -> Rotate Z's Parent
        // 4) Z.uncle = Black (Line)     -> Rotate Z's Grandparent and Recolor

        void FixInsert(AVLNode* node)
        {
            AVLNode* stagingNode;
            
            while (node->m_Parent->m_Color == 1) // If a node's parent is red, all its children is to be black. 
            {
                // If our node is inserted oin the right subtree. 
                if (node->m_Parent == node->m_Parent->m_Parent->m_Right) 
                {
                    stagingNode = node->m_Parent->m_Parent->m_Left; // Uncle
                    if (stagingNode->m_Color == 1) // If our node's uncle is red, we recolor. 
                    {
                        // Recolor.
                        stagingNode->m_Color = 0; // Uncle = Black 
                        node->m_Parent->m_Color = 0; // Parent = Black
                        node->m_Parent->m_Parent->m_Color = 1; // Grandparent = Red
                        node = node->m_Parent->m_Parent;
                    }
                    else
                    {
                        if (node == node->m_Parent->m_Left) // If our node is a left child. We rotate Z's parent in the opposite direction of Z. In this case, right.
                        {
                            node = node->m_Parent;
                            RightRotate(node);
                        }

                        // A line is formed on the right subtree. Rotate grandparent. Nodes are to be recolored.
                        node->m_Parent->m_Color = 0;
                        node->m_Parent->m_Parent->m_Color = 1;
                        LeftRotate(node->m_Parent->m_Parent);
                    }
                }
                else // Our node is inserted on the left subtree.
                {
                    stagingNode = node->m_Parent->m_Parent->m_Right; // Uncle
                    if (stagingNode->m_Color == 1) // If our node's uncle is red, we recolor.
                    {
                        stagingNode->m_Color = 0; // Uncle = Black
                        node->m_Parent->m_Color = 0; // Parent = Black
                        node->m_Parent->m_Parent->m_Color = 1; // Grandparent = Red
                        node = node->m_Parent->m_Parent;
                    }
                    else
                    {
                        if (node == node->m_Parent->m_Right) // If our node is a right child. We rotate the parent in the opposite direction.
                        {
                            node = node->m_Parent;
                            LeftRotate(node);
                        }

                        // A line is formed on the left subtree. Rotate grandparent. Nodes are to be recolored. 
                        node->m_Parent->m_Color = 0;
                        node->m_Parent->m_Parent->m_Color = 1;
                        RightRotate(node->m_Parent->m_Parent);
                    }
                }

                if (node == m_Root) // Break if the node is our root. 
                {
                    break;
                }
            }

            m_Root->m_Color = 0; // Root of the tree is always black.
        }

        // Fix the RB tree modifed by the delete operation.
        void FixDelete(AVLNode* node)
        {
            AVLNode* stagingNode;

            while (node != m_Root && node->m_Color == 0)
            {
                if (node == node->m_Parent->m_Left) // We are on the left subtree.
                {
                    stagingNode = node->m_Parent->m_Right;
                    if (stagingNode->m_Color == 1) // If the right sibling is red and the left sibling is black.
                    {
                        stagingNode->m_Color = 0;    // Color sibling Black.
                        node->m_Parent->m_Color = 1; // Color our node's parent red.
                        LeftRotate(node->m_Parent);  // If our node is a left child, we rotate left.
                        stagingNode = node->m_Parent->m_Right;
                    }

                    if (stagingNode->m_Left->m_Color == 0 && stagingNode->m_Right->m_Color == 0)
                    {
                        stagingNode->m_Color = 1;
                        node = node->m_Parent;
                    }
                    else
                    {
                        // If only one side is black and the other red.
                        if (stagingNode->m_Right->m_Color == 0)
                        {
                            stagingNode->m_Left->m_Color = 0;
                            stagingNode->m_Color = 1;
                            RightRotate(stagingNode);
                            stagingNode = node->m_Parent->m_Right;
                        }

                        stagingNode->m_Color = node->m_Parent->m_Color;
                        node->m_Parent->m_Color = 0;
                        stagingNode->m_Right->m_Color = 0;
                        LeftRotate(node->m_Parent);
                    }
                }

                /// Right subtree omitted.
            }
        }

        void DeleteNodeHelper(AVLNode* node, int key)
        {
            // Find the node containing the key.
            AVLNode* locatedNode = m_Null;
            AVLNode* x;
            AVLNode* stagingNode;

            while (node != m_Null)
            {
                if (node->m_Data == key)
                {
                    locatedNode = node;
                }

                if (node->m_Data <= key)
                {
                    node = node->m_Right;
                }
                else
                {
                    node = node->m_Left;
                }
            }

            if (locatedNode == m_Null)
            {
                std::cout << "Could not locate with node with key in the tree." << "\n";
                return;
            }

            stagingNode = locatedNode;
            int stagingNodeColor = stagingNode->m_Color;

            // If the node we are trying to delete has 1 NIL child and 1 non NIL child, its replacement X is the non NIL child. 
            if (locatedNode->m_Left == m_Null)
            {
                x = locatedNode->m_Right;
                Transplant(locatedNode, locatedNode->m_Right); // Put its right node into locatedNode's position.
            }
            else if (locatedNode->m_Right == m_Null)
            {
                x = locatedNode->m_Left;
                Transplant(locatedNode, locatedNode->m_Left); // Put its left node into locatedNode's position.
            }
            else // If the node we deleted has 2 non-NIL children, set X to the replacement's right child before the replacement is spliced out.
            {
                stagingNode = Minimum(locatedNode->m_Right); // Find replacement, which is to be the successor of the node to be deleted.
                stagingNodeColor = stagingNode->m_Color; // If the node we delete is red and its replacement is red or NIL, we are done. 

                // Set X to be the replacement's right child. 
                x = stagingNode->m_Right;

                // If our replacement's parent node is our node that is to be deleted...
                if (stagingNode->m_Parent == locatedNode)
                {
                    // We set the saved right subtree to be the replacement node.
                    x->m_Parent = stagingNode;
                }
                else
                {
                    Transplant(stagingNode, stagingNode->m_Right); // Replace our replacement node with its right subtree.
                    stagingNode->m_Right = locatedNode->m_Right;  // Attach the replacement node's right node to the deleted node's right tree.
                    stagingNode->m_Right->m_Parent = stagingNode; // Attach the replacement node as the parent accordingly.
                }

                // Officially plant the new location.
                Transplant(locatedNode, stagingNode);
                // Attach the saved node positions.
                stagingNode->m_Left = locatedNode->m_Left;
                stagingNode->m_Left->m_Parent = stagingNode;
                stagingNode->m_Color = locatedNode->m_Color;
            }

            delete locatedNode;
            if (stagingNodeColor == 0) // Fix colors. For example, if the node we deleted is red and its placement is black, color the replacement red. 
            {
                FixDelete(x);
            }
        }

        void Transplant(AVLNode* locatedNode, AVLNode* transplantNode)
        {
            if (locatedNode->m_Parent == nullptr)
            {
                m_Root = locatedNode;
            }
            else if (locatedNode == locatedNode->m_Parent->m_Left)
            {
                locatedNode->m_Parent->m_Left = transplantNode;
            }
            else
            {
                locatedNode->m_Parent->m_Right = transplantNode;
            }

            transplantNode->m_Parent = locatedNode->m_Parent;
        }

        void PrintHelper(AVLNode* root, std::string indent, bool last)
        {
            // Print the tree structure on the screen.
            if (root != m_Null)
            {
                std::cout << indent;
                if (last)
                {
                    std::cout << "R----";
                    indent += "       ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|       ";
                }

                std::string sColor = root->m_Color ? "RED" : "BLACK";
                std::cout << root->m_Data << "(" << sColor << ")" << std::endl;
                PrintHelper(root->m_Left, indent, false);
                PrintHelper(root->m_Right, indent, true);
            }
        }


    private:
        AVLNode* m_Null;
        AVLNode* m_Root;
    };
}