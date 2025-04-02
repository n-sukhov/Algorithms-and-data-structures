#include <iostream>

const short CAMERAS_AMOUNT = 8;
const short ADJACTED_VERTICES = 3;
const int MAX_ITERS = 1000;

const short CAMERAS_LINKS[CAMERAS_AMOUNT][ADJACTED_VERTICES]
{
    { 1, 3, 4 }, // A
    { 0, 2, 5 }, // B
    { 1, 3, 6 }, // C
    { 0, 2, 7 }, // D
    { 0, 5, 7 }, // E
    { 1, 4, 6 }, // F
    { 2, 5, 7 }, // G
    { 3, 4, 6 }  // H
};
const char INDEXES[CAMERAS_AMOUNT]
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'
};

bool try_to_anihilate(int* array, int vertice);
bool create_duons(int* array, int vertice);
bool move_duons(int* array);

int main(int argc, char const *argv[])
{
    int cameras[CAMERAS_AMOUNT] {};
    int sum = 0;

    for (int i = 0; i < CAMERAS_AMOUNT; ++i) {
        std::cin >> cameras[i];
        sum += cameras[i];
    }

    if (sum % 2 == 1) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }

    for (int i = 0; i < MAX_ITERS; ++i) {
        if (move_duons(cameras)) return 0;
    }
    
    std::cout << "IMPOSSIBLE";
    
    return 0;
}


bool try_to_anihilate(int* array, int vertice) {
    for (int x : CAMERAS_LINKS[vertice])
        if (*(array + x) > 0) {
            --(*(array + vertice)), --(*(array + x));
            std::cout << INDEXES[vertice] << INDEXES[x] << '-' << std::endl;
            return false;
        }
    return true;
};

bool create_duons(int* array, int vertice) {
    for (int x : CAMERAS_LINKS[vertice])
        for (int i : CAMERAS_LINKS[x]) if (i != vertice && *(array + i) > 0)
            for (int j : CAMERAS_LINKS[i])
                if (*(array + j) > 0 && j != vertice) {
                    ++*(array + x), ++(*(array + i));
                    std::cout << INDEXES[x] << INDEXES[x] << '+' << std::endl;
                    return true;
                }
    for (int x : CAMERAS_LINKS[vertice])
        if (create_duons(array, x))
            return true;
    return false;
}

bool move_duons(int* array) {
    for (int i = 0; i < CAMERAS_AMOUNT; ++i)
        if (*(array + i) > 0) {
            if (try_to_anihilate(array, i))
                create_duons(array, i);
            return false;
        }
    return true; // if all cameras empty
}