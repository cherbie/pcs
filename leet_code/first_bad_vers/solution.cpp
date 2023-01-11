#include <bits/stdc++.h>

#ifdef DEBUG
constexpr bool isBadVersion(int n)
{
    return n >= 5;
}
#else
extern bool isBadVersion(int n);
#endif // ifdef DEBUG

inline int binarySearchMin(int low, int high)
{
    if (high == low) 
    {
        if (!isBadVersion(low))
            return -1; // domain error
        return low;
    }

    if (isBadVersion(high))
    {
        int mid = ((high - low) / 2) + low;
        if (isBadVersion(mid))
            return binarySearchMin(low, mid);
        else
            return binarySearchMin(mid + 1, high);
    }
    else
        return -1; // domain error
}

inline int firstBadVersion(int n)
{
    return binarySearchMin(0, n);
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    std::cout << "0 - 9: " << firstBadVersion(9) << std::endl;
    std::cout << "0 - 14: " << firstBadVersion(14) << std::endl;
#endif // ifdef DEBUG
}
