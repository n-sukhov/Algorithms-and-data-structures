#include <iostream>

const int MAX_N = 1 << 17;

void build(int n, int* tree) {
    for (int i = 0; i < 2 * MAX_N; ++i)
        tree[i] = 0;

    for (int i = 0; i < n; ++i)
        tree[MAX_N + i] = 1;

    for (int i = MAX_N - 1; i > 0; --i)
        tree[i] = tree[2 * i] + tree[2 * i + 1];
}

int find_kth(int k, int* tree) {
    int node = 1;
    while (node < MAX_N) {
        if (tree[node <<= 1] < k)
            k -= tree[node++];
    }
    return node - MAX_N;
}

void update(int pos, int* tree) {
    pos += MAX_N;
    tree[pos] = 0;
    while (pos > 1) {
        pos >>= 1;
        tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
    }
}

int main() {
    int tree[MAX_N * 2];
    int N, K;
    std::cin >> N >> K;
    
    build(N, tree);
    
    int current = K % N;
    if (current == 0) current = N;
    
    for (int i = 0; i < N; ++i) {
        int pos = find_kth(current, tree);
        std::cout << pos + 1 << ' ';
        update(pos, tree);
        if (i < N - 1) {
            int remaining = N - i - 1;
            current = (current - 1 + K) % remaining;
            if (current == 0) current = remaining;
        }
    }
    return 0;
}