#include <sstream>
#include <string>
#include <vector>
#include <iostream>

class Solution
{
public:
    std::string encode(const std::vector<std::string> &strs)
    {
        std::stringstream stream;
        for (auto s : strs)
        {
            stream << s << _delimiter;
        }
        return stream.str();
    }

    std::vector<std::string> decode(std::string s)
    {
        std::vector<std::string> strs;
        while (!s.empty())
        {
            auto delimiterIdx = s.find(_delimiter);
            strs.push_back(s.substr(0, delimiterIdx));
            s.erase(0, delimiterIdx + _delimiter.length());
        }
        return strs;
    }

private:
    const std::string _delimiter = "@!@";
};

#ifdef DEBUG

void printVector(const std::vector<std::string> &vector)
{
    std::cout << "[";
    for (auto &element : vector)
    {
        std::cout << element << ", ";
    }
    std::cout << "]";
}

int main(int argc, char **argv)
{
    const std::vector<std::string> testCase = {"neet", "code", "love", "you"};
    std::cout << "test case: ";
    printVector(testCase);
    std::cout << std::endl;

    auto s = Solution();
    const std::string encodedString = s.encode(testCase);
    std::cout << encodedString << std::endl;

    printVector(s.decode(encodedString));
    std::cout << std::endl;
}

#endif
