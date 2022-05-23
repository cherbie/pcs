#include <bits/stdc++.h>

bool compare(std::pair<int, int> &l, std::pair<int, int> &r)
{
    if (l.first == r.first)
        return l.second < r.second;
    // else
    return l.first < r.first;
}

int solve(std::vector<int> &loc, int n)
{
    std::vector<std::pair<int, int>> ranges;
    int i = 0;
    for (auto l : loc)
    {
        ranges.push_back(std::make_pair(std::max(0, i - l), std::min(n - 1, i + l)));
    }

    std::sort(ranges.begin(), ranges.end(), compare);

    int ans = 0;
    i = 0;
    while (i < n)
    {
        ans++;
        auto light = ranges[i];
        
        while (i < n-1 && light.first == ranges[i+1].first)
        {
            light.second = std::max(light.second, ranges[i+1].second);
            i++;
        }

        while (i < n && ranges[i].second <= light.second)
            i++;
    }
    return ans;
}

int main(int argc, char *argv[])
{
    int n;
    std::vector<int> loc;

    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int v;
        std::cin >> v;
        loc.push_back(v);
    }

    std::cout << solve(loc, n) << "\n";

    return 0;
}