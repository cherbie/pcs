#include <bits/stdc++.h>

#define DEBUG

namespace
{
    using range = std::pair<int /*min*/, int /*max*/>;

    bool compare(range &l, range &r)
    {
        return l.first <= r.first;
    }

    int solve(std::vector<int> &loc, int k)
    {
        std::vector<range> ranges;
        for (auto l : loc)
        {
            ranges.push_back(std::make_pair(l - k, l + k));
        }

        std::sort(ranges.begin(), ranges.end(), compare);

        range prev_light = ranges[0];
        int ans = prev_light.second - prev_light.first + 1;
        for (std::size_t i = 1; i < ranges.size(); i++)
        {
            range curr_light = ranges[i];
            if (prev_light == curr_light)
            {
#ifdef DEBUG
                std::cerr << "-SAME LAMP-" << std::endl;
#endif // ifdef DEBUG
                continue;
            }
            ans += curr_light.second - std::max(curr_light.first, prev_light.second + 1) + 1;
            prev_light = curr_light;
#ifdef DEBUG
            std::cerr << ans << " | ";
#endif // ifdef DEBUG
        }
        return ans;
    } // solve(std::vector<int>&, n)
}

/// -- INPUT --
/// tc
/// n k
/// a0 a1 a2 a3 ...
/// ...
int main(int argc, char *argv[])
{
    int t;

    std::cin >> t;
    for (int j = 0; j < t; j++)
    {
        int n, k;
        std::vector<int> loc;
        std::cin >> n >> k;
        for (int i = 0; i < n; i++)
        {
            int v;
            std::cin >> v;
            loc.push_back(v);
        }
        std::cout << ::solve(loc, k) << std::endl;
    }

    return 0;
}