#include <iostream>

int main(int argc, char const *argv[])
{
    int N, best_sum = 0, current_sum = 0;
    std::cin >> N;
    int p[N] {};
    
    for (int i= 0; i < N; ++i)
        std::cin >> p[i];
    
    for (int i = 0; i < N; ++i) {
        current_sum = std::max(p[i], current_sum + p[i]);
        best_sum = std::max(best_sum, current_sum);
    }
    
    std::cout << best_sum;
        
    return 0;
}
