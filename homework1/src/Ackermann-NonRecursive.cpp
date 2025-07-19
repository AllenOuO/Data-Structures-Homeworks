#include <iostream>
#include <stack>

int A(int m, int n) {
    std::stack<int> s1;
    std::stack<int> s2;
    s1.push(m);
    s2.push(n);

    while (!s1.empty())
    {
        while (m != 0)
        {
            if (n == 0)
            {
                m = m - 1;
                n = 1;
                s1.push(m);
                s2.push(n);
            }
            else
            {
                n = n - 1;
                s1.push(m - 1);
                s2.push(-1);
            }
        }
        n++;
        while (!s1.empty() && s2.top() != -1) {
            s1.pop();
            s2.pop();
        }

        if (!s1.empty()) {
            m = s1.top();
            s2.pop();
            s2.push(n);
        }
    }
    return n;
}

int main() {
    int m, n;
    while(1) {
        std::cout << "Enter m and n: ";
        std::cin >> m >> n;
        std::cout << "A(" << m << ", " << n << ") = " << A(m, n) << std::endl;
    }
}