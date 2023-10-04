#include <bits/stdc++.h>

#define DEBUG

namespace
{
    using point_t = std::pair<int /*x*/, int /*y*/>;

    int minTimeToVisitAllPoints(std::vector<point_t> &points)
    {
        int timeTaken = 0;
        auto pPoint = points.begin();
        auto cPoint = pPoint + 1;
        while (cPoint != points.end())
        {
#ifdef DEBUG
            std::cerr << "(" << cPoint->first << ", " << cPoint->second << ")"
                      << " | "
                      << "(" << pPoint->first << ", " << pPoint->second << ")"
                      << std::endl;
#endif
            int delta_x = std::abs(cPoint->first - pPoint->first);
            int delta_y = std::abs(cPoint->second - pPoint->second);
            timeTaken += delta_x <= delta_y ? delta_x + delta_y - delta_x : delta_y + delta_x - delta_y;
            pPoint = cPoint;
            cPoint++;
        }
        return timeTaken;
    }
}

int main(int argc, char **argv)
{
    std::vector<::point_t> testCase = std::vector<::point_t>{{1, 1}, {3, 4}, {-1, 0}};
    std::cout << ::minTimeToVisitAllPoints(testCase) << std::endl;
    return 0;
}