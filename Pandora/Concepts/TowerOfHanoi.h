#pragma once
#include <iostream >

namespace TOH
{
    void PrintMovement(std::string fromRod, std::string toRod)
    {
        std::cout << "Move from Rod '" << fromRod << "' to Rod '" << toRod << "'.\n";
    }

    void TowerOfHanoi(int diskCount, std::string fromRod, std::string auxRod, std::string toRod)
    {
        // Put the last disk on.
        if (diskCount == 1)
        {
            std::cout << "\t\tMove disc " << 1 << " from " << fromRod << " to " << toRod << "\n";
            return;
        }
        else
        {
            TowerOfHanoi(diskCount - 1, fromRod, toRod, auxRod);
            std::cout << "\t\tMove disc " << diskCount << " from " << fromRod << " to " << toRod << "\n";
            TowerOfHanoi(diskCount - 1, auxRod, fromRod, toRod);
        }
    }

    void TestCases_TowerOfHanoi()
    {
        TowerOfHanoi(4, "A", "B", "C");
    }
}