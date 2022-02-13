#pragma once
#include <iostream>

namespace QuickSort
{
    // Quick Sort -> Select Pivot, Split list into left and right. Keep selecting pivot and sort. Combine results.

    int Partition(int ourArray[], int startIndex, int endIndex)
    {
        // Select the rightmost element as pivot.
        int pivot = ourArray[endIndex];

        // Pointer for greater element.
        int i = (startIndex - 1);

        // Traverse each element of the array and compare them with the pivot.
        for (int j = startIndex; j < endIndex; j++)
        {
            if (ourArray[j] <= pivot)
            {
                // If element is smaller than the pivot, swap it with the greater element pointed by i.
                i++;
                // Swap element at i with element at j.
                std::swap(ourArray[i], ourArray[j]);
            }
        }

        // Swap pivot with the greater element at i.
        std::swap(ourArray[i + 1], ourArray[endIndex]);

        // Return the partition point
        return (i + 1);
    }

    void Quick_Sort(int ourArray[], int startIndex, int endIndex)
    {
        // Base Case
        if (startIndex >= endIndex)
        {
            return;
        }

        // Partition the array such that elements smaller than the pivot are on the left, and element greater are on the right. 
        int pivot = Partition(ourArray, startIndex, endIndex);

        // Recursively Sort Left part.
        Quick_Sort(ourArray, startIndex, pivot - 1);
        
        // Recursively Sort Right part.
        Quick_Sort(ourArray, pivot + 1, endIndex);
    }

    void TestCases_QuickSort()
    {
        int ourArray[] = { 9, 3, 4, 2, 1, 8 };
        int arrayCount = 6;

        Quick_Sort(ourArray, 0, arrayCount - 1);

        for (auto i : ourArray)
        {
            std::cout << i << ", ";
        }

        std::cout << std::endl;
    }
}