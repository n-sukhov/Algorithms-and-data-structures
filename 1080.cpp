#include <iostream>
#include <vector>
#include <queue>


int main() {
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> countries(N);
    for (int i = 0; i < N; ++i) {
        int neighbor;
        while (std::cin >> neighbor) {
            if (neighbor == 0) break;
            countries[i].push_back(neighbor - 1);
            countries[neighbor - 1].push_back(i);
        }
    }

    std::vector<int> colors(N, -1);
    colors[0] = 0;
    std::queue<int> q;
    q.push(0);
    bool possible = true;

    while (!q.empty() && possible) {
        int current = q.front();
        q.pop();
        for (int neighbor : countries[current]) {
            if (colors[neighbor] == -1) {
                colors[neighbor] = colors[current] ^ 1;
                q.push(neighbor);
            }
            else if (colors[neighbor] == colors[current]) {
                possible = false;
                break;
            }
        }
    }

    if (possible) {
        for (int i = 0; i < N; ++i) {
            std::cout << colors[i];
        }
        std::cout << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }

    return 0;
}