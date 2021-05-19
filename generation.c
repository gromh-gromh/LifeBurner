#include <generation.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Map *GenerateLevel(int tries)
{
    struct Map *level = malloc(sizeof(struct Map));

    level->size_x = SIZE_X;
    level->size_y = SIZE_Y;

    level->level = calloc(level->size_y, sizeof(char *));
    for(int i = 0; i < level->size_y; i++)
    {
        level->level[i] = calloc(level->size_x, sizeof(char));
    }

    for(int i = 0; i < level->size_y; i++)
    {
        for(int j = 0; j < level->size_x; j++)
        {
            if(i == 0 || j == 0 || i == level->size_y - 1 || j == level->size_x - 1)
            {
                level->level[i][j] = WALL;
            } else
            {
                level->level[i][j] = EMPTY;
            }
        }
    }

    level->enemies = 10 - tries;

    return level;
}

struct Player *GeneratePlayer(int passed_levels)
{
    struct Player *player = malloc(sizeof(struct Player));

    player->position_x = SIZE_X / 2;
    player->position_y = SIZE_Y / 2;

    player->health = 3;

    player->passed_levels = passed_levels;

    return player;
}

struct Enemy **GenerateEnemies(int n)
{
    srand(time(NULL));

    struct Enemy **enemies = calloc(n, sizeof(struct Enemy *));

    for(int i = 0; i < n; i++)
    {
        enemies[i] = malloc(sizeof(struct Enemy));

        enemies[i]->position_x = (rand() % (SIZE_X - 2)) + 1;
        enemies[i]->position_y = (rand() % (SIZE_Y - 2)) + 1;

        enemies[i]->is_alive = true;
    }
    return enemies;
}

struct World *CreateWorld(int passed_levels)
{
    struct World *world = malloc(sizeof(struct World));

    world->player = GeneratePlayer(passed_levels);
    world->level = GenerateLevel(world->player->passed_levels);
    world->enemies = GenerateEnemies(world->level->enemies);

    world->time = 0;

    return world;
}

