#pragma once
#include <list>
#include <iostream>

namespace HashTables
{
    // Chaining Implementation
    class HashTable
    {
    public:
        HashTable(int elementCount)
        {
            m_TotalElements = elementCount;
            m_Table = new std::list<int>[m_TotalElements];
        }

        // Insert data in our hash table.
        void InsertElement(int key, int data)
        {
            m_Table[Hash(key)].push_back(data);
        }

        void PrintAll()
        {
            for (int i = 0; i < m_TotalElements; i++)
            {
                std::cout << "Index " << i << ": ";
                for (auto x : m_Table[i])
                {
                    std::cout << x << ", ";
                }
                
                std::cout << std::endl;
            }
        }

    private:
        // Simple hash calculation
        int Hash(int key)
        {
            return key % m_TotalElements;
        }

    private:
        std::list<int>* m_Table; // Pointer to the head of each linked list in our table.
        int m_TotalElements;
    };
}
