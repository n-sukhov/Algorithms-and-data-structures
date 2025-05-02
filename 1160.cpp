#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int u, v, length;
};

bool compareEdges(const Edge &a, const Edge &b);
void unionSets(int u, int v, std::vector<int>* parent);
int find(int u, std::vector<int>* parent);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    std::vector<int> parent;

    std::vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].length;
    }

    std::sort(edges.begin(), edges.end(), compareEdges);

    parent.resize(N + 1);
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    std::vector<std::pair<int, int>> mstEdges;
    int maxLen = 0;

    for (const Edge &edge : edges) {
        if (find(edge.u, &parent) != find(edge.v, &parent)) {
            unionSets(edge.u, edge.v, &parent);
            mstEdges.emplace_back(edge.u, edge.v);
            maxLen = edge.length;
        }
    }

    std::cout << maxLen << '\n';
    std::cout << mstEdges.size() << '\n';
    for (const auto &edge : mstEdges) {
        std::cout << edge.first << ' ' << edge.second << '\n';
    }

    return 0;
}

bool compareEdges(const Edge &a, const Edge &b) {
    return a.length < b.length;
}

int find(int u, std::vector<int>* parent) {
    if ((*parent)[u] != u) {
        (*parent)[u] = find((*parent)[u], parent);
    }
    return (*parent)[u];
}

void unionSets(int u, int v, std::vector<int>* parent) {
    int rootU = find(u, parent);
    int rootV = find(v, parent);
    if (rootU != rootV) {
        (*parent)[rootV] = rootU;
    }
}