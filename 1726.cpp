#include <iostream>
#include <vector>
#include <algorithm>

unsigned long long count_distance(std::vector<int>& coords) {
    sort(coords.begin(), coords.end());
    unsigned long long total = 0;
    unsigned long long prefixSum = 0;
    for (int i = 0; i < coords.size(); ++i) {
        total += (unsigned long long)coords[i] * i - prefixSum;
        prefixSum += coords[i];
    }
    return total;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i)
        std::cin >> x[i] >> y[i];
    
    unsigned long long sumX = count_distance(x);
    unsigned long long sumY = count_distance(y);
    
    unsigned long long totalSum = sumX + sumY;
    unsigned long long average = totalSum / (n * (n - 1LL) / 2LL);
    
    std::cout << average;
    
    return 0;
}