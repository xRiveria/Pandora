#pragma once
#include <string>

namespace Bits
{
    /* 
       By using the & operator between our numerical value and 1, all bits are eliminated except the LSB(least significant bit), which is compared.
       If the result is 0, it means the LSB is 0, hence the number is Even. Else, it is Odd. 

       You can immediately conclude that a binary value ending with 1 is odd, in the same way that a decimal number ending in an add number is odd. The last 
       term in the "ones" place and all of the terms to the left of that are in multiples of 2 (in the form 2^k for integer k > 1). Therefore, only in the right 
       most term determines oddness. Of course, if it ends in 0, then it is even. Graphical representation:

       1        1        0       1
       1 x 8    1 x 4    0 x 2   1  x 1

       You can change any of these digits except the first one and the remainder when divided by 2 will stay the same. Only by changing the first unit's digit can be 
       change whether the total is odd or even.
    */
    void OddOrEven(int numericalValue)
    {
        if ((numericalValue & 1) == 0)
        {
            std::cout << numericalValue << " is " << "Even.\n";
        }
        else
        {
            std::cout << numericalValue << " is " << "Odd.\n";
        }
    }

    bool IsBitSet(int numericalValue, int bitToCheck)
    {
        if (numericalValue & (1 << bitToCheck)) // Shifting 0000 0001 left by k (bitToCheck) times.
        {
            std::cout << "The " << bitToCheck << " bit in " << numericalValue << " is set.\n";
            return true;
        }
        else
        {
            std::cout << "The " << bitToCheck << " bit in " << numericalValue << " is not set.\n";
            return false;
        }
    }

    bool SetBit(int numericalValue, int bitToSet)
    {
        if (numericalValue & (1 << bitToSet))
        {
            std::cout << "Original Value: " << numericalValue << ". ";
            std::cout << "Bit " << bitToSet << " has already been set. Value remains as " << numericalValue << ".\n";
            return false;
        }
        else
        {
            std::cout << "Original Value: " << numericalValue << ". ";
            // Using the OR operator on any 0 value leaves it unchanged. Otherwise, the value is changed to 1.
            numericalValue = numericalValue | (1 << bitToSet);
            std::cout << "Bit " << bitToSet << " has been set. Value changed to " << numericalValue << ".\n";
            return true;
        }
    }

    bool UnsetBit(int numericalValue, int bitToUnset)
    {
        if (numericalValue & (1 << bitToUnset))
        {
            // All bits are turned except the targeted one with the One's Complement operator ~.
            // We can do this with our numericalValue to ensure that only the kth (bitToUnset) value is unset to 0.
            std::cout << "Original Value: " << numericalValue << ". ";
            numericalValue = numericalValue & ~(1 << bitToUnset);
            std::cout << "Bit " << bitToUnset << " has been unset. Value changed to " << numericalValue << ".\n";
            return true;
        }
        else
        {
            std::cout << "Original Value: " << numericalValue << ". ";
            std::cout << "Bit " << bitToUnset << " has already been unset. Value remains as " << numericalValue << ".\n";
            return false;
        }
    }

    void ToggleBit(int numericalValue, int bitToToggle)
    {
        // XOR (^) toggles the value of the bit to 1 if it is 0, and to 0 if it is 1. 
        std::cout << "Original Value: " << numericalValue << ". ";
        numericalValue = numericalValue ^ (1 << bitToToggle);
        std::cout << "Toggled Value: " << numericalValue << ".\n";
    }

    void TurnOffRightMost1Bit(int numericalValue)
    {
        std::cout << "Original Value: " << numericalValue << ". ";
        // Subtracting 1 sets all the lower bits to 1 and an & operation will set all of them to 0 including the right most 1 bit.
        numericalValue = numericalValue & (numericalValue - 1);
        std::cout << "New Value: " << numericalValue << ".\n";
    }

    void IsolateRightMost1Bit(int numericalValue)
    {
        // In 2s complement, 0 is added to the front of our numericalValue. It is then inverted and added to with a 1 to find its negative value.
        // We will then & this with our original value to isolate the right most bit. 
        std::cout << "Isolated Right Most 1 Bit of " << numericalValue;
        numericalValue = numericalValue & (-numericalValue);
        std::cout << ": " << numericalValue << ".\n";
    }

    void IsolateRightMost0Bit(int numericalValue)
    {
        // Finds the right most zero bit and sets it to 1.
        std::cout << "Isolated Right Most 0 Bit of " << numericalValue;
        numericalValue = ~numericalValue & (numericalValue + 1);
        std::cout << ": " << numericalValue << ".\n";
    }

    void TurnOnRightMost0Bit(int numericalValue)
    {
        std::cout << "Turned On Right Most 0 Bit of " << numericalValue;
        numericalValue = numericalValue | (numericalValue + 1);
        std::cout << ": " << numericalValue << ".\n";
    }
}