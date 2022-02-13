#pragma once
#include <iostream>

namespace BubbleSort
{
    // O^2
    void BubbleSort(int arr[], int arraySize)
    {
        int i, j;
        for (i = 0; i < arraySize - 1; i++)
        {
            for (j = 0; j < arraySize - 1 - i; j++) // Minusing i here allows us to avoid comparing the already sorted elements.
            {
                if (arr[j] > arr[j + 1])
                {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // Stop the algorithm if the inner loop didn't cause any swaps. Best case of (N), worse case of O(N*N).
    void BubbleSortOptimized(int arr[], int arraySize)
    {
        int i, j;
        bool swapped;
        for (i = 0; i < arraySize - 1; i++)
        {
            swapped = false;
            for (j = 0; j < arraySize - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }

            // If no two elements were swapped by the inner loop, break.
            if (swapped == false)
            {
                break;
            }
        }
    }

    void TestCases_BubbleSort()
    {
        int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
        int sizeArray = sizeof(arr) / sizeof(arr[0]);
        BubbleSortOptimized(arr, sizeArray);

        for (int i = 0; i < sizeArray; i++)
        {
            std::cout << arr[i] << " ";
        }
        
        std::cout << std::endl;
    }
}