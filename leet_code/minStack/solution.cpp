#include <bits/stdc++.h>

namespace
{
    class MinStack
    {
    private:
        std::stack<std::pair<int /*value*/, int /*minValue*/>> m_minStack;

    public:
        MinStack()
        {
        }

        void push(int val)
        {
            if (!m_minStack.empty())
            {
                int minValue = getMin();
                if (val < minValue)
                {
                    m_minStack.push({val, val});
                } else {
                    m_minStack.push({val, minValue});
                }
            } else {
                m_minStack.push({val, val});
            }
        }

        void pop()
        {
            if (m_minStack.empty())
            {
                return;
            }
            m_minStack.pop();
        }

        int top()
        {
            return m_minStack.top().first;
        }

        int getMin()
        {
            return m_minStack.top().second;
        }
    };
} // end namespace

int main(int argc, char **argv)
{
#ifdef DEBUG
    ::MinStack stack;

    stack.push(5);
    std::cout << stack.getMin() << std::endl;
    stack.push(2);
    std::cout << stack.getMin() << std::endl;
    stack.push(123);
    std::cout << stack.top() << std::endl;
    stack.pop();
    std::cout << "end" << std::endl;
#endif // ifdef DEBUG

    return 0;
}
