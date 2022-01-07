#pragma once
#include <iostream>

namespace Sorting
{
    void Merge(int* arr, int leftIndex, int middleIndex, int rightIndex)
    {
    }

    void MergeSort(int* arr, int leftIndex, int rightIndex)
    {
        int middleIndex;
        if (leftIndex < rightIndex)
        {
            middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
            // Sort the first and second arrays.
            MergeSort(arr, leftIndex, middleIndex);
            MergeSort(arr, leftIndex + 1, rightIndex);
            Merge(arr, leftIndex, middleIndex, rightIndex);
        }
    }

    void TestsCases_MergeSort()
    {
        int arraySize = 6;
        int arr[] = { 14, 20, 78, 98, 20, 45 };
        
        MergeSort(arr, 0, 6 - 1); // -1 for last index.

        std::cout << "Sorted Array: \n";
        for (int i = 0; i < arraySize; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
}