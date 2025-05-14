#include <iostream>
#include <vector>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> sequence(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> sequence[i];
    }

    std::stack<int> stk;
    int current = 1;
    int idx = 0;

    while (current <= n) {
        stk.push(current);
        while (!stk.empty() && idx < n && stk.top() == sequence[idx]) {
            stk.pop();
            ++idx;
        }
        ++current;
    }

    while (!stk.empty() && idx < n && stk.top() == sequence[idx]) {
        stk.pop();
        ++idx;
    }

    if (idx == n) {
        std::cout << "Not a proof";
    }
    else {
        std::cout << "Cheater";
    }

    return 0;
}
