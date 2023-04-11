#include <bits/stdc++.h>

namespace
{
    class BrowserHistory
    {
    public:
        BrowserHistory(const std::string &homepage)
        {
            m_backward_history.push(homepage);
        }

        void visit(const std::string &url)
        {
            m_backward_history.push(url);
            m_forward_history = {};
        }

        std::string back(int steps)
        {
            for (int i = 0; i < steps && m_backward_history.size() > 1; i++)
            {
                std::string url = m_backward_history.top();
                m_forward_history.push(url);
                m_backward_history.pop();
            }
            return current();
        }

        std::string forward(int steps)
        {
            for (int i = 0; i < steps && !m_forward_history.empty(); i++)
            {
                std::string url = m_forward_history.top();
                m_backward_history.push(url);
                m_forward_history.pop();
            }
            return current();
        }

        std::string current()
        {
            return m_backward_history.top();
        }

    private:
        std::stack<std::string> m_backward_history;
        std::stack<std::string> m_forward_history;
    };
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    ::BrowserHistory history("/homepage");
    history.visit("/homepage/another");
    history.visit("/some/page/");
    history.back(4);
    history.forward(1);
    std::cout << history.current() << std::endl;
#endif // ifdef DEBUG
}