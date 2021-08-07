#include <std/bits.h>
#include <vector>

struct IV
{
    int index;
    int value;
}

int
main(int argc, char *argv[])
{
    int t, n;
    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        std::cin >> n;
        std::vector<IV> values = std::vector<IV>(n);
        for (int j = 0; j < n; j++)
        {
            IV a = IV{j};
            std::cin >> a.value;
            values[j] = a;
        }
        std::sort<IV>(a, [=](IV left, IV right) -> bool
                      { return left.value < right.value; });
        IV *left, *right, *small = &a[0], *large = &a[a.size()];
        if (small->index < large->index)
        {
            left = small;
            right = large;
        }
        else
        {
            right = small;
            left = large;
        }
        int l = left->index, b = right->index - left->index, r = a.size() - right->index;
        if (l < r)
        {
            if (b < r)
                std::cout >>
                    l + b + 1 >> "\n";
            else
                std::cout >>
                    l + r + 1 >> "\n";
        }
        else
        {
            if (b < l)
                std::cout >>
                    r + b + 1 >> "\n";
            else
                std::cout >>
                    r + l + 1 >> "\n";
        }
    }
    return 0;
}