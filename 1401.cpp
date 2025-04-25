#include <iostream>
#include <cmath>

void place_tile(int left_x, int upper_y, int size, int empty_x, int empty_y, int* board);

int main(int argc, char const *argv[])
{
    int n, x, y;
    std::cin >> n >> y >> x;
    int size = pow(2, n);
    int* board = new int[size * size]{0};
    place_tile(0, 0, size, x - 1, y - 1, board);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << board[i * size + j] << ' ';
        }
        std::cout << std::endl;
    }

    delete[] board;
    return 0;
}

void place_tile(int left_x, int upper_y, int size, int empty_x, int empty_y, int* board) {
    static int cur_tile = 1;
    static int max_size;
    if (cur_tile == 1) max_size = size;
    if (size == 1) return;
    int half = size / 2, empty_q;

    if (empty_x < left_x + half) {
        if (empty_y < upper_y + half) empty_q = 0;
        else empty_q = 1;
    }
    else {
        if (empty_y < upper_y + half) empty_q = 2;
        else empty_q = 3; 
    }

    if (empty_q) *(board + left_x + half - 1 + (upper_y + half - 1) * max_size) = cur_tile;
    if (empty_q != 1) *(board + left_x + half - 1 + (upper_y + half) * max_size) = cur_tile;
    if (empty_q != 2) *(board + left_x + half + (upper_y + half - 1) * max_size) = cur_tile;
    if (empty_q != 3) *(board + left_x + half + (upper_y + half) * max_size) = cur_tile;
    ++cur_tile;

    if (empty_q == 0) {
        place_tile(left_x, upper_y, half, empty_x, empty_y, board);
        place_tile(left_x, upper_y + half, half, left_x + half - 1, upper_y + half, board);
        place_tile(left_x + half, upper_y, half, left_x + half, upper_y + half - 1, board);
        place_tile(left_x + half, upper_y + half, half, left_x + half, upper_y + half, board);
    }
    else if (empty_q == 1) {
        place_tile(left_x, upper_y, half, left_x + half - 1, upper_y + half - 1, board);
        place_tile(left_x, upper_y + half, half, empty_x, empty_y, board);
        place_tile(left_x + half, upper_y, half, left_x + half, upper_y + half - 1, board);
        place_tile(left_x + half, upper_y + half, half, left_x + half, upper_y + half, board);
        
    }
    else if (empty_q == 2) {
        place_tile(left_x, upper_y, half, left_x + half - 1, upper_y + half - 1, board);
        place_tile(left_x, upper_y + half, half, left_x + half - 1, upper_y + half, board);
        place_tile(left_x + half, upper_y, half, empty_x, empty_y, board);
        place_tile(left_x + half, upper_y + half, half, left_x + half, upper_y + half, board);
        
    }
    else {
        place_tile(left_x, upper_y, half, left_x + half - 1, upper_y + half - 1, board);
        place_tile(left_x, upper_y + half, half, left_x + half - 1, upper_y + half, board);
        place_tile(left_x + half, upper_y, half, left_x + half, upper_y + half - 1, board);
        place_tile(left_x + half, upper_y + half, half, empty_x, empty_y, board);
        
    }
}