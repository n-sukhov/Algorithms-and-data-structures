#include <iostream>
#include <vector>

struct edge {
    int u, v, length;
};

bool edgecomparer(const edge &a, const edge &b);
void union_sets(int u, int v, int* parent);
int find(int u, int* parent);
int Partition(std::vector<edge>& A, int p, int r);
void Quicksort(std::vector<edge>& A, int p, int r);


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    int parent[N + 1];
    std::vector<edge> edges(M);
    for (int i = 0; i < M; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].length;
    }

    Quicksort(edges, 0, M - 1);

    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    std::vector<std::pair<int, int>> mstedges;
    int maxLen = 0;

    for (const edge &e : edges) {
        if (find(e.u, parent) != find(e.v, parent)) {
            union_sets(e.u, e.v, parent);
            mstedges.emplace_back(e.u, e.v);
            maxLen = e.length;
        }
    }

    std::cout << maxLen << std::endl << mstedges.size() << std::endl;
    for (const std::pair<int, int> &e : mstedges) {
        std::cout << e.first << ' ' << e.second << std::endl;
    }

    return 0;
}

bool edgecomparer(const edge &a, const edge &b) {
    return a.length < b.length;
}

int find(int u, int* parent) {
    if (parent[u] != u) {
        parent[u] = find(parent[u], parent);
    }
    return parent[u];
}

void union_sets(int u, int v, int* parent) {
    int rootU = find(u, parent);
    int rootV = find(v, parent);
    if (rootU != rootV) {
        parent[rootV] = rootU;
    }
}

int Partition(std::vector<edge>& A, int p, int r) {
    edge x = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j)
        if (edgecomparer(A[j], x)) {
            ++i;
            edge temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    ++i;
    edge temp = A[i];
    A[i] = A[r];
    A[r] = temp;
    return i;
}

void Quicksort(std::vector<edge>& A, int p, int r) {
    if (p < r) {
        int q = Partition(A, p, r);
        Quicksort(A, p, q - 1);
        Quicksort(A, q + 1, r);
    }
}