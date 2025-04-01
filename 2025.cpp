#include <iostream>

int main(int argc, char const *argv[]) {
    int T;
    std::cin >> T;
    int n[T] {};
    int k[T] {};

    for (int i = 0; i < T; ++i)
        std::cin >> n[i] >> k[i];

    for (int i = 0, sum = 0; i < T; ++i, sum = 0) {
        int k_temp = k[i], n_temp = n[i], fighters_past = 0;
        int teams[k[i]] {};

        while (k_temp) {
            teams[k_temp - 1] = n_temp / k_temp;
            n_temp -= n_temp / k_temp--;
        }

        for (int j = 0; j < k[i] - 1; ++j) {
            fighters_past += teams[j];
            sum += teams[j] * (n[i] - fighters_past);
        }

        std::cout << sum << std::endl;
    }
    
    return 0;
}
