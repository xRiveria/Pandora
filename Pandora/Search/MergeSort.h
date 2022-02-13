#pragma once
#include <iostream>

namespace Sorting
{
    void Merge(int ourArrayp[], int leftIndex, int middleIndex, int rightIndex)
    {
        // Create our two subarrays.
        const int arrayOneSize = middleIndex - leftIndex + 1;
        const int arrayTwoSize = rightIndex - middleIndex;

        // int leftArray[arrayOneSize];
        // int rightArray[arrayTwoSize];
    }

    // Divide the array into two subarrays, sort them and merge them.
    void MergeSort(int ourArray[], int leftIndex, int rightIndex)
    {
        if (leftIndex < rightIndex)
        {
            // M is the middle index where the array is divided into two subarrays.
            int middleIndex = std::floor(leftIndex + (rightIndex - leftIndex) / 2);
            MergeSort(ourArray, leftIndex, middleIndex);
            MergeSort(ourArray, middleIndex + 1, rightIndex);

            // Merge the sorted subarrays.
            Merge(ourArray, leftIndex, middleIndex, rightIndex);
        }
    }

    void TestsCases_MergeSort()
    {
        int arraySize = 6;
        int arr[] = { 14, 20, 78, 98, 20, 45 };
        
        // MergeSort(arr, 6); // -1 for last index.

        std::cout << "Sorted Array: \n";
        for (int i = 0; i < arraySize; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
}