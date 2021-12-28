#include <iostream>
#include "Bits/BitManipulation.h"
#include "Algorithms/PrimsMST.h"
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool SortFunction(int a, int b)
{
    return a < b;
}

int main(int argc, int argv[])
{
    MinimumSpanningTrees::TestCasesMST();
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
}