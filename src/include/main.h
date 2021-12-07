#pragma once

#include <iostream>
#include <random>
#include <string>
// u can change it
const int WORLD_H = 50;
const int WORLD_W = 50;

struct point
{
    unsigned is_live:1;
};

void init(point world[][WORLD_H])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);
    unsigned int i, j;

    for (i = 0; i< WORLD_W; i++)
    {
        for (j = 0; j< WORLD_H; j++)
        {
            unsigned int num = dis(gen);
            if (num % 2 == 0)
                world[i][j].is_live = 1;
            else
                world[i][j].is_live = 0;
        }   
    }
}

unsigned int getLCount(point world[][WORLD_H])
{
    unsigned int count = 0;
    unsigned i, j;
    for (i = 0; i < WORLD_H; i++)
    {
        for (j = 0; j < WORLD_W; j++)
        {
            if (world[i][j].is_live == 1)
                count++;
        }   
    }
    return count;
}

void pointNeighbors(signed int nb[][2], unsigned int x, unsigned int y)
{
    unsigned int i, j;
    unsigned int k = 0;

    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y)
                continue;
            nb[k][0] = i;
            nb[k][1] = j;
            k++;
        }
    }
}

unsigned int countLiveNeighbors(point world[][WORLD_H], unsigned int x, unsigned int y)
{
    unsigned int count = 0;
    unsigned int i;
    signed int nb[8][2];
    signed int _x, _y;

    pointNeighbors(nb, x, y);

    for (i = 0; i < 8; i++) {
        _x = nb[i][0];
        _y = nb[i][1];

        if (_x < 0 || _y < 0)
            continue;
        if (_x >= WORLD_W || _y >= WORLD_H)
            continue;
        if (world[_x][_y].is_live == 1)
            count++;
    }

    return count;
}

void nextGen(point world[][WORLD_H], point prev_world[][WORLD_H])
{
    unsigned int i, j;
    unsigned int live_nb;
    point p;

    for (i = 0; i < WORLD_W; i++)
    {
        for (j = 0; j < WORLD_H; j++)
        {
            p = prev_world[i][j];
            live_nb = countLiveNeighbors(prev_world, i, j);

            if (p.is_live == 0)
            {
                if (live_nb == 3)
                    world[i][j].is_live = 1;
            }                    
            else 
            {
                if (live_nb < 2 || live_nb > 3)
                    world[i][j].is_live = 0;
            }
        }
    }
}

void copyWorld(point src[][WORLD_H], point dest[][WORLD_H])
{
    unsigned int i, j;
    for (i = 0; i < WORLD_W; i++)
    {
        for (j = 0; j < WORLD_H; j++)
            dest[i][j] = src[i][j];
    }
}

int cmpWorld(point w1[][WORLD_H], point w2[][WORLD_H])
{
    unsigned int i, j;
    for (i = 0; i < WORLD_W; i++)
    {
        for (j = 0; j < WORLD_H; j++)
        {
            if (w1[i][j].is_live != w2[i][j].is_live)
            {
                return -1;
            }
        }
    }
    return 0;
}

void printWorld(point world[][WORLD_H])
{
    unsigned int i, j;
    std::string map;
    for (i = 0; i < WORLD_W; i++)
    {
        for (j = 0; j < WORLD_H; j++)
        {
            if (world[i][j].is_live == 1)
                map += "@";
            else
                map += " ";
            map +=  " ";
        }
        map += "\n";
    }
    std::cout << map << std::endl;
}

