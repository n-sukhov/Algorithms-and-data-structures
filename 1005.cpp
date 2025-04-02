#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> weights(n);
    int total_sum = 0;
    
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
        total_sum += weights[i];
    }
    
    int target = total_sum / 2;
    std::vector<std::vector<bool>> d_table(n + 1, std::vector<bool>(target + 1, false));
    d_table[0][0] = true;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= target; ++j) {
            d_table[i][j] = d_table[i - 1][j];
            if (j >= weights[i - 1]) {
                d_table[i][j] = d_table[i][j] || d_table[i - 1][j - weights[i - 1]];
            }
        }
    }
    
    int best_sum = 0;
    for (int i = target; i >= 0; --i) {
        if (d_table[n][i]) {
            best_sum = i;
            break;
        }
    }
    
    std::cout << total_sum - 2 * best_sum;
    
    return 0;
}
