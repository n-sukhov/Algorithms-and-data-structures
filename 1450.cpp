#include <iostream>
#include <vector>
#include <climits>
#include <queue>

const int INF = INT_MIN;

struct Edge {
    int to;
    int cost;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<Edge>> graph(N + 1);
    std::vector<int> indegree(N + 1, 0);

    for (int i = 0; i < M; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        graph[a].push_back({b, c});
        ++indegree[b];
    }

    int S, F;
    std::cin >> S >> F;

    std::queue<int> q;
    std::vector<int> ts;

    for (int i = 1; i <= N; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ts.push_back(v);

        for (const Edge& e : graph[v]) {
            if (--indegree[e.to] == 0) {
                q.push(e.to);
            }
        }
    }

    std::vector<int> dp(N + 1, INF);
    dp[S] = 0;

    for (int v : ts) {
        if (dp[v] == INF) continue;
        for (const Edge& e : graph[v]) {
            if (dp[e.to] < dp[v] + e.cost) {
                dp[e.to] = dp[v] + e.cost;
            }
        }
    }

    if (dp[F] == INF) {
        std::cout << "No solution";
    } else {
        std::cout << dp[F];
    }

    return 0;
}
