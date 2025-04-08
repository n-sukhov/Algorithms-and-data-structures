#include <iostream>
#include <string>

const short CAMERAS_AMOUNT = 8;
const short ADJACTED_VERTICES = 3;

const int CAMERAS_LINKS[CAMERAS_AMOUNT][ADJACTED_VERTICES]
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


int main(int argc, char const *argv[])
{
    int cameras[CAMERAS_AMOUNT] {};
    int sum = 0;
    std::string answer = "";

    for (int i = 0; i < CAMERAS_AMOUNT; ++i) {
        std::cin >> cameras[i];
        sum += cameras[i];
    }

    if (sum % 2 == 1) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }

    for (int i = 0; i < CAMERAS_AMOUNT; ++i)
        for (int j : CAMERAS_LINKS[i])
            if (cameras[i] != 0 && cameras[j] != 0) {
                int duons_amount = std::min(cameras[i], cameras[j]);
                for (int a = 0; a < duons_amount; ++a) {
                    --cameras[i], --cameras[j];
                    answer += INDEXES[i] + INDEXES[j] + "-\n";
                }
            }

    for (int i = 0; i < CAMERAS_AMOUNT; ++i)
        if (cameras[i] != 0)
            for (int j : CAMERAS_LINKS[i])
                for (int k : CAMERAS_LINKS[j])
                    if (k != i && cameras[k] == 0)
                        for (int m : CAMERAS_LINKS[k])
                            if (m != j && cameras[m] != 0) {
                                int duons_amount = std::min(cameras[i], cameras[m]);
                                for (int a = 0; a < duons_amount; ++a) {
                                    ++cameras[j], ++cameras[k];
                                    answer += INDEXES[j] + INDEXES[k] + "+\n";
                                }
                                for (int a = 0; a < duons_amount; ++a) {
                                    --cameras[i], --cameras[j];
                                    answer += INDEXES[i] + INDEXES[j] + "-\n";
                                    --cameras[k], --cameras[m];
                                    answer += INDEXES[k] + INDEXES[m] + "-\n";
                                }
                            }

    int free_cameras = 0;
    for (int i = 0; i < CAMERAS_AMOUNT; ++i) {
        if (cameras[i] == 0) ++free_cameras;
    }
    if (free_cameras < 8) std::cout << "IMPOSSIBLE";
    else std::cout << answer;

    return 0;
}
