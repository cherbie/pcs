#include <bits/stdc++.h>

int main(int argc, char** argv)
{
    unsigned int n = 0;
    std::cin >> n;
    while (n > 1)
    {
        std::cout << n << " ";
        if (n % 2 == 0)
            n >>= 1;
        else
            n = n*3 + 1;
    }
}
