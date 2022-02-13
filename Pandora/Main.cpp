#include <iostream>
#include <string>
#include "Algorithms/BFS.h"
#include "Examples/BinaryTreeDummy.h"
#include "Time/Stopwatch.h"
#include "Examples/DummyGraph.h"
#include "DataStructures/HashTable.h"
#include "Search/BubbleSort.h"
#include "Search/SelectionSort.h"
#include "Search/InsertionSort.h"
#include "Search/QuickSort.h"
#include "Algorithms/Dijkstras.h"
#include <bitset>
#include <map>

using namespace std;

bool SortFunction(int a, int b)
{
    return a < b;
}

int ReturnFactorialIterative(int number)
{
    int total = number;
    for (int i = number - 1; i > 0; i--)
    {
        total *= i;
    }

    return total;
}

int ReturnFactorialRecursive(int counter)
{
    if (counter == 2)
    {
        return 2;
    }

    return counter * ReturnFactorialRecursive(counter - 1);
}

int ReturnFibonacciRecursive(int fibIndex) // O(2^N) -> Exponential Time. Can be fixed with Dynamic Programming.
{
    if (fibIndex <= 1) // Base case. Can alos be < 2
    {
        return fibIndex;
    }

    return ReturnFibonacciRecursive(fibIndex - 1) + ReturnFibonacciRecursive(fibIndex - 2);
}

int ReturnFibonacciIterative(int fibIndex)
{
    std::vector<int> ourArray = { 0, 1 };

    for (int i = 2; i < fibIndex + 1; i++)
    {
        ourArray.push_back(ourArray[i - 2] + ourArray[i - 1]);
    }

    return ourArray[fibIndex];
}

std::map<int, int> fibDatabase;
int ReturnFibonacciMaster(int N)
{
    if (fibDatabase[N])
    {
        return fibDatabase[N];
    }
    else
    {
        if (N < 2)
        {
            return N;
        }
        else
        {
            fibDatabase[N] = ReturnFibonacciMaster(N - 1) + ReturnFibonacciMaster(N - 2);
            return fibDatabase[N];
        }
    }
}

//void ReverseString(const std::string& ourString)
//{
    //return ReverseString()
//}

std::string ReverseString(std::string string)
{
    if (string.length() <= 1)
    {
        return string;
    }

        
    // Reverse(o) = Returns o
    // Reverse(lo) = Returns ol
    // Reverse(llo) = Returns oll
    // Reverse (ello) = Returns olle
    // Reverse (Hello) = Returns olleh

    return ReverseString(string.substr(1)) + string.at(0);
}

class Solution {
public:
    int maxProduct(vector<int> nums)
    {
        if (nums.empty() || nums.size() == 0)
        {
            return -1; // Invalid input.
        }

        int maxValueThusFar = INT_MIN;
        int localMax = 1; // The max cumulative product up to the current element starting from somewhere in the past.
        int localMin = 1; // The minimum cumulative product up to the current element. 

        for (int num : nums)
        {
            // If we encounter a negative number, we need to know that a negative number multiplied with
            // another negative number turns the whole number positive.
            // And, a positive number multipled with a negative number turns the whole number super small.

            // Hence, whenever we encounter a negative number, the candidate for max product should 
            // become the previous miniumum product.
            if (num < 0)
            {
                int temporary = localMax;
                localMax = localMin;
                localMin = temporary;
            }

            // Either we restart at num, or compute the total thus far.
            localMax = std::max(num, localMax * num);
            localMin = std::min(num, localMin * num);

            maxValueThusFar = std::max(localMax, maxValueThusFar);
        }

        return maxValueThusFar;
    }
};

int main(int argc, int argv[])
{
    Solution solution;
    std::cout << solution.maxProduct({ 2, 3, -2, 4 }) << "\n";

    // 0000 0110 -> 1111 1001 + 1 = 1111 1010
    int a = -6;
    std::cout << std::bitset<8>(a) << "\n";

    AnotherDijkstra::TestCases();
    QuickSort::TestCases_QuickSort();
    SelectionSort::TestCases_SelectSort();
    BubbleSort::TestCases_BubbleSort();
    InsertionSort::TestCases_InsertionSort();

    std::cout << ReverseString("Pika") << "\n";
    std::cout << ReturnFibonacciMaster(10) << "\n";

    std::cout << ReturnFactorialIterative(5) << "\n";
    std::cout << ReturnFactorialRecursive(5) << "\n";

    int key[] = { 231, 321, 212, 321, 433, 262 };
    int data[] = { 123, 432, 523, 43, 423, 111 };
    const int size = sizeof(key) / sizeof(key[0]);
    HashTables::HashTable hashTable(size);
    for (int i = 0; i < size; i++)
    {
        hashTable.InsertElement(key[i], data[i]);
    }

    hashTable.PrintAll();

    Graphs::Graph* ourGraph = new Graphs::Graph(7); // Use Resize, which is not 0 inclusive.
    ourGraph->AddEdges(3, 1);
    ourGraph->AddEdges(3, 4);
    ourGraph->AddEdges(4, 2);
    ourGraph->AddEdges(4, 5);
    ourGraph->AddEdges(1, 2);
    ourGraph->AddEdges(1, 0);
    ourGraph->AddEdges(0, 2);
    ourGraph->AddEdges(6, 5);

    ourGraph->ShowConnections();

    //       9
    //   4       20
    // 1   6   15  170

    Trees::BinarySearchTree* ourTree = new Trees::BinarySearchTree();
    ourTree->Insert(9);
    ourTree->Insert(4);
    ourTree->Insert(6);
    ourTree->Insert(20);
    ourTree->Insert(170);
    ourTree->Insert(15);
    ourTree->Insert(1);
    ourTree->Remove(6);

    {
        Time::Stopwatch stopWatch("Breadth First Search Iterative");
        ourTree->BreadthFirstSearchIterative();
    }

    {
        Time::Stopwatch stopWatch("Breadth First Search Recursive");      
        ourTree->BreadthFirstSearchRecursive();
    }

    {
        Time::Stopwatch stopWatch("Depth First Search - InOrder");
        ourTree->DFS_InOrder();
    }

    {
        Time::Stopwatch stopWatch("Depth First Search - PreOrder");
        ourTree->DFS_PreOrder();
    }

    {
        Time::Stopwatch stopWatch("Depth First Search - PostOrder");
        ourTree->DFS_PostOrder();
    }



    /*
    TOH::TestCases_TowerOfHanoi();
    InsertionSort::TestCases_InsertionSort();
    Heaps::TestCases_Heap();
    BubbleSort::TestCases_BubbleSort();

    std::vector<int> searchStuff = { 2, 4, 5, 7, 10, 11 };
    int target = 7;
    int low = 0;
    int high = searchStuff.size() - 1; // Index

    while (low <= high)
    {
        int mid = low + (high - low) / 2; // Always locate the middle element.

        if (searchStuff[mid] == target)
        {
            std::cout << mid << "\n";
            break;
        }

        if (searchStuff[mid] < target)
        {
            low = mid + 1;
        }
        else if (searchStuff[mid] > target)
        {
            high = mid - 1;
        }
    }

    MinimumSpanningTrees::TestCasesMST();
    MinimumSpanningTrees::TestCasesKruskalsMST();
    BellmanFord::TestCases_BellmanFord();
    DijkstrasAlgorithmMatrix::TestCases_Dijkstra();
    DijkstrasAlgorithmAdjacencyList::TestsCases_DijkstrasAdjacencyList();
    BFS::TestCases_BFS();
    DFS::TestCase_DFS();
    GraphTraversals::TestCases_Traversal();

    char derp = 'a';
    std::cout << (int)derp << "\n";

    std::vector<int> test = { 2, 4, 5, 1, 3 };
    std::sort(test.begin(), test.end(), SortFunction);
    for (auto& thing : test)
    {
        std::cout << thing << "\n";
    }



    Bits::OddOrEven(5);
    Bits::OddOrEven(10);

    std::cout << "\n";

    // 128 64, 32, 16, 8, 4, 2  1
    //   1  0   0   0  0  0  0
    //              1  0  1  1  0
    Bits::IsBitSet(128, 7);
    Bits::IsBitSet(1, 0);

    std::cout << "\n";

    Bits::SetBit(1, 0);
    Bits::SetBit(6, 3);
    Bits::SetBit(6, 4);

    std::cout << "\n";
    // 0001
    // ~0001 = 1110
    // 0000
    Bits::UnsetBit(1, 0); // Yield 0.
    Bits::UnsetBit(6, 2); // Yield 2.

    std::cout << "\n";

    Bits::ToggleBit(0, 0);
    Bits::ToggleBit(6, 4);

    std::cout << "\n";

    Bits::TurnOffRightMost1Bit(1);

    std::cout << "\n";

    Bits::IsolateRightMost1Bit(5);

    std::cout << "\n";

    // 0110, 1001
    //       0111
    //       0001
    Bits::IsolateRightMost0Bit(6);

    std::cout << "\n";

    Bits::TurnOnRightMost0Bit(6);
    return 0;
    */
}