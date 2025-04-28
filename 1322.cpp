#include <iostream>
#include <vector>
#include <string>

const int ALPHABET_SIZE = 53;

int get_alphabet_pos(const char& c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c == '_') return 26;
    if (c >= 'a' && c <= 'z') return 27 + (c - 'a');
    return -1;
}


int main() {
    int k;
    std::cin >> k;
    --k;
    std::string last_column;
    std::cin >> last_column;
    
    int N = last_column.size();

    std::vector<int> count(ALPHABET_SIZE, 0);
    for (char c : last_column) {
        ++count[get_alphabet_pos(c)];
    }
    
    std::vector<int> first_occurrence(ALPHABET_SIZE, 0);
    int sum = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        first_occurrence[i] = sum;
        sum += count[i];
    }
    
    std::vector<int> rank(N, 0);
    std::vector<int> seen(ALPHABET_SIZE, 0);
    for (int i = 0; i < N; ++i)
        rank[i] = seen[get_alphabet_pos(last_column[i])]++;
    
    std::string result(N, ' ');
    for (int i = N - 1; i >= 0; --i) {
        char c = last_column[k];
        result[i] = c;
        k = first_occurrence[get_alphabet_pos(c)] + rank[k];
    }
    
    std::cout << result;
    return 0;
}
