#include <iostream>
#include <vector>


struct edge {
    int a, b;
    double rate, commission;
};

bool can_increase(int N, int M, int S, double V, std::vector<edge>& edges) {
    std::vector<double> max_curr(N + 1, 0.0);
    max_curr[S] = V;

    for (int i = 1; i <= N - 1; ++i) {
        bool not_updated = true;
        for (const edge& e : edges) {
            if (max_curr[e.a] > 0) {
                double new_amount = (max_curr[e.a] - e.commission) * e.rate;
                if (new_amount > max_curr[e.b]) {
                    max_curr[e.b] = new_amount;
                    not_updated = false;
                }
            }
        }
        if (not_updated) break;
    }

    for (const edge& e : edges) {
        if (max_curr[e.a] > 0) {
            double new_amount = (max_curr[e.a] - e.commission) * e.rate;
            if (new_amount > max_curr[e.b]) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int N, M, S;
    double V;
    std::cin >> N >> M >> S >> V;

    std::vector<edge> edges;
    for (int i = 0; i < M; ++i) {
        int A, B;
        double RAB, CAB, RBA, CBA;
        std::cin >> A >> B >> RAB >> CAB >> RBA >> CBA;
        edges.push_back({A, B, RAB, CAB});
        edges.push_back({B, A, RBA, CBA});
    }

    if (can_increase(N, M, S, V, edges)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }

    return 0;
}