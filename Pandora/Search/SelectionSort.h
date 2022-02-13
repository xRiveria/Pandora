#pragma once
#include <vector>

namespace SelectionSort
{
    void SelectSort(std::vector<int>& items)
    {
        for (int i = 0; i < items.size(); i++)
        {
            int smallestItemKey = i;

            for (int j = 0 + i; j < items.size(); j++)
            {
                if (items[j] < items[smallestItemKey])
                {
                    smallestItemKey = j;
                }
            }

            std::swap(items[i], items[smallestItemKey]);
        }
    }

    void TestCases_SelectSort()
    {
        std::vector<int> ourVector = { 2, 1, 6, 9, 3, 15 };
        SelectSort(ourVector);

        for (auto i : ourVector)
        {
            std::cout << i << ", ";
        }

        std::cout << std::endl;
    }
}