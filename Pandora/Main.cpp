#include <iostream>
#include "Algorithms/BFS.h"
#include "Examples/BinaryTreeDummy.h"
#include "Time/Stopwatch.h"

using namespace std;

bool SortFunction(int a, int b)
{
    return a < b;
}

int main(int argc, int argv[])
{
    //       9
    //   4      20
    // 1   6  15  170
    {
        Time::Stopwatch stopWatch("Linear Search");
    }

    {
        Time::Stopwatch stopWatch("Binary Search");      

        Trees::BinarySearchTree* ourTree = new Trees::BinarySearchTree();

        ourTree->Insert(9);
        ourTree->Insert(4);
        ourTree->Insert(6);
        ourTree->Insert(20);
        ourTree->Insert(170);
        ourTree->Insert(15);
        ourTree->Insert(1);

        ourTree->BreadthFirstSearch();
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