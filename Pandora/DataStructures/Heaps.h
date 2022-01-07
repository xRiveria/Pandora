#pragma once
#include <vector>
#include <iostream>

namespace Heaps
{
    // Max Heap
    struct _PriorityQueue
    {
    public:
        unsigned int size() const
        {
            return m_HeapElements.size();
        }

        bool empty() const
        {
            return this->size() == 0;
        }

        void push(int value)
        {
            // Insert a new element at the end of the vector.
            m_HeapElements.push_back(value);
            // Get element index and call heapify-up procedure.
            int index = size() - 1;
            HeapifyUp(index);
        }

        // Removes the element with the highest priority (present at the root).
        void pop()
        {
            if (this->size() == 0)
            {
                throw "There is nothing to pop in the queue.";
            }

            // Else, replace the root of the heap with the last element and call Heapify Down.
            m_HeapElements[0] = m_HeapElements.back();
            m_HeapElements.pop_back();

            HeapifyDown(0);
        }

        // Return the element with the highest priority that is present at the root. This is either smallest or largest valued element.
        int top()
        {
            if (this->size() == 0)
            {
                throw "The queue is empty.";
            }

            return m_HeapElements[0];
        }

        void remove(int value)
        {
            if (this->size() == 0)
            {
                throw "The queue is empty.";
            }

            int i;
            for (i = 0; i < this->size(); i++)
            {
                if (value == m_HeapElements[i])
                {
                    break;
                }
            }

            std::swap(m_HeapElements[i], m_HeapElements.back());
            m_HeapElements.pop_back();

            HeapifyDown(i);
        }

        void print()
        {
            for (int i = 0; i < this->size(); i++)
            {
                std::cout << m_HeapElements[i] << " ";        
            }
            std::cout << std::endl;
        }

    private:
        int GetLeftNodeKey(int nodeKey)
        {
            return (2 * nodeKey + 1);
        }

        int GetRightNodeKey(int nodeKey)
        {
            return (2 * nodeKey + 2);
        }

        int GetParentNodeKey(int nodeKey)
        {
            return (nodeKey - 1) / 2;
        }

        // Recursive heapify-down algirthm.
        void HeapifyDown(int key)
        {
            // Get left and right child of node at index 'i'. 
            int leftNodeKey = GetLeftNodeKey(key);
            int rightNodeKey = GetRightNodeKey(key);

            int largestNodeKey = key;

            // Compare m_HeapElements[key] with its left and right child and find the larger value.
            if (leftNodeKey < this->size() && m_HeapElements[leftNodeKey] > m_HeapElements[key])
            {
                largestNodeKey = leftNodeKey; 
            }

            if (rightNodeKey < this->size() && m_HeapElements[rightNodeKey] > m_HeapElements[largestNodeKey])
            {
                largestNodeKey = rightNodeKey;
            }

            // Swap with a child having greater value and call heapify-down recursively on the child.
            if (largestNodeKey != key)
            {
                std::swap(m_HeapElements[key], m_HeapElements[largestNodeKey]);
                HeapifyDown(largestNodeKey);
            }
        }

        void HeapifyUp(int key)
        {
            if (key && m_HeapElements[GetParentNodeKey(key)] < m_HeapElements[key])
            {
                // Swap the two if heap property is violated.
                std::swap(m_HeapElements[key], m_HeapElements[GetParentNodeKey(key)]);
                HeapifyUp(GetParentNodeKey(key));
            }
        }

    private:
        std::vector<int> m_HeapElements;
    };

    void TestCases_Heap()
    {
        _PriorityQueue queue;
        queue.push(5);
        queue.push(3);
        queue.push(15);
        queue.push(1);
        std::cout << queue.top() << "\n";
        queue.remove(15);
        std::cout << queue.top() << "\n";
        std::cout << queue.size() << "\n";
        std::cout << queue.top() << "\n";

        queue.print();
    }
}