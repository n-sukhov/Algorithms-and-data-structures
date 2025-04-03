#include <iostream>
#include <string>
#include <algorithm>
#include <random>

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
const std::string INDEXES[CAMERAS_AMOUNT]
{
    "A", "B", "C", "D", "E", "F", "G", "H"
};

std::random_device rd;
std::mt19937 gen(rd());

bool try_to_anihilate(int* array, int vertice);
bool move_duons(int* array);
void create_duons(int* array, int vertice);

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

    for (int i = 0; i < MAX_ITERS; ++i)
        if (move_duons(cameras)) {
            return 0;
        }

    return 0;
}


bool try_to_anihilate(int* array, int vertice) {
    for (int x : CAMERAS_LINKS[vertice])
        if (*(array + x) > 0) {
            --*(array + vertice), --*(array + x);
            std::cout <<  INDEXES[vertice] << INDEXES[x] << "-\n";
            return false;
        }
    return true;
};

void create_duons(int* array, int vertice) {
    if (*(array + vertice) == 1) {
        int links_1[ADJACTED_VERTICES] = { CAMERAS_LINKS[vertice][0], CAMERAS_LINKS[vertice][1], CAMERAS_LINKS[vertice][2] };
        std::shuffle(links_1, links_1 + ADJACTED_VERTICES, gen);
    
        for (int x : links_1) {
            int links_2[ADJACTED_VERTICES] = { CAMERAS_LINKS[x][0], CAMERAS_LINKS[x][1], CAMERAS_LINKS[x][2] };
            std::shuffle(links_2, links_2 + ADJACTED_VERTICES, gen);
    
            for (int i : links_2) if (i != vertice) {
                ++*(array + x), ++*(array + i);
                std::cout << INDEXES[x] << INDEXES[i] << "+\n";
                return;
            }
        }    
    }
    ++*(array + CAMERAS_LINKS[vertice][0]), ++*(array + CAMERAS_LINKS[vertice][1]);
    std::cout << INDEXES[CAMERAS_LINKS[vertice][0]] << INDEXES[CAMERAS_LINKS[vertice][1]] << "+\n";
}

bool move_duons(int* array) {
    int numbers[CAMERAS_AMOUNT] = {0, 1, 2, 3, 4, 5, 6, 7};
    std::shuffle(numbers, numbers + CAMERAS_AMOUNT, gen);

    for (int i = 0; i < CAMERAS_AMOUNT; ++i)
        if (*(array + i) > 0)
            if (!try_to_anihilate(array, i))
                return false;

    int sum = array[0];
    for (int i = 1; i < CAMERAS_AMOUNT; ++i){
        sum += array[i];
    }
    if (sum == 0) return true;
        
    for (int i = 0; i < CAMERAS_AMOUNT; ++i) {
        if (*(array + i) > 0) {
            create_duons(array, i);
            break;
        }
    }

    return false;
}