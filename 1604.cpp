#include <iostream>

inline int max_position_not_key(int* array, int size, int key) {
    int cur_max = 0, pos = -1;
    for (int i = 0; i < size; ++i)
        if (*(array + i) > cur_max && i != key) {
            cur_max = *(array + i);
            pos = i;
        }
    return pos;
}

int main(int argc, char const *argv[])
{
    int k, sum = 0;
    std::cin >> k;
    
    int* n = new int[k];
    for (int i = 0; i < k;  ++i) {
        std::cin >> *(n + i);
        sum += *(n + i);
    }

    int last_val = -1;

    for (int i = 0; i < sum; ++i) {
        int pos = max_position_not_key(n, k, last_val);
        pos = pos != -1 ? pos : last_val;
        int sign = pos + 1;
        std::cout << sign << ' ';
        --*(n + pos);
        last_val = pos;
    }
    
    delete[] n;
    return 0;
}
