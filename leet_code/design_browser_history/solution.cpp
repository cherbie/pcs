#include <bits/stdc++.h>

namespace
{
    class BrowserHistory
    {
    public:
        BrowserHistory(const std::string &homepage)
        {
            m_history.push_back(homepage);
            m_current = 0;
        }

        void visit(const std::string &url)
        {
            m_history.resize(m_current + 2, url);
            m_current++;
            m_history[m_current] = url;
        }

        std::string back(int steps)
        {
            int max_steps_back = std::min(steps, m_current);
            m_current -= max_steps_back;
            return top();
        }

        std::string forward(int steps)
        {
            m_current = std::min(steps + m_current, (int)m_history.size() - 1);
            return top();
        }

        std::string top()
        {
            return m_history.at(m_current);
        }

#ifdef DEBUG
        int index()
        {
            return m_current;
        }
#endif // ifdef DEBUG

    private:
        std::vector<std::string> m_history;
        int m_current = 0;
    };
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    ::BrowserHistory history("/homepage");
    history.visit("/homepage/another");
    history.visit("/some/page/");
    std::cout << history.index() << " ";
    std::cout << history.back(4) << " " << history.index() << " ";
    history.visit("/youtube.com");
    history.visit("/another/page");
    history.visit("/what/the/hell");
    std::cout << history.index() << history.back(5) << " ";
    std::cout << history.forward(1) << " " << history.index() << " ";
    std::cout << history.top() << std::endl;
#endif // ifdef DEBUG
}