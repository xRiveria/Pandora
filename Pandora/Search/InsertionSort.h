#pragma once
#include <iostream>

namespace InsertionSort
{
    void InsertionSort(int arr[], int arraySize)
    {
        int i, key, j;
        for (i = 1; i < arraySize; i++)
        {
            // Selects the first unsorted array. 
            key = arr[i];
            j = i - 1;

            // Move elements of arr[0...i-1] that are greater than key to one position ahead of their current position to create a room for the unsorted element.
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }

            // Place key at after the element just smaller than it. 
            arr[j + 1] = key;
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