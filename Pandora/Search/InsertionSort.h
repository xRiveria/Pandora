#pragma once
#include <iostream>

namespace InsertionSort
{
    void InsertionSort(int arr[], int arraySize)
    {
        int unsortedIndex, unsortedValue, lastSortedIndex;
        // Assume that index 0 is already sorted. 
        for (unsortedIndex = 1; unsortedIndex < arraySize; unsortedIndex++)
        {
            // Selects the first unsorted array. 
            unsortedValue = arr[unsortedIndex];
            lastSortedIndex = unsortedIndex - 1; // This will be the last index of the already sorted items in our list.

            // Move all values in the sorted list greater than the unsorted value up by 1 position to make room for our child.
            while (lastSortedIndex >= 0 && arr[lastSortedIndex] > unsortedValue)
            {
                arr[lastSortedIndex + 1] = arr[lastSortedIndex];
                lastSortedIndex = lastSortedIndex - 1; // Decrement the index here. This should land at the key 1 smaller than the element to be inserted.
            }

            // Place key at after the element just smaller than it. 
            arr[lastSortedIndex + 1] = unsortedValue;
        }
    }

    void TestCases_InsertionSort()
    {
        int arr[] = { 12, 11, 13, 5, 6 };
        int arraySize = sizeof(arr) / sizeof(arr[0]);

        InsertionSort(arr, arraySize);

        for (int i = 0; i < arraySize; i++)
        {
            std::cout << arr[i] << " ";
        }

        std::cout << std::endl;
    }
}