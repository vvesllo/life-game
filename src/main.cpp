#include "include/main.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    point world[WORLD_H][WORLD_W];
    point prev_world[WORLD_W][WORLD_H];

    init(world);
    unsigned int live_points = -1;
    bool is_optimal = false;

    do {
        system("cls");

        // std::cout << nline;
        printWorld(world);
        copyWorld(world, prev_world);
        nextGen(world, prev_world);

        is_optimal = cmpWorld(world, prev_world) == 0;
        live_points = getLCount(world);

        if (is_optimal) {
            std::cout << "Сycles detected!" << std::endl;
        }

        if (live_points == 0) {
            std::cout << "All points died" << std::endl;
        }
        // Sleep(500);
    } while (live_points != 0 && !is_optimal);

}