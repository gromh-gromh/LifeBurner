#include <world_generation.h>
#include <stdio.h>
#include <stdlib.h>

struct Map *GenerateLevel(int tries)
{
    //Allocating memory for game level
    struct Map *level = malloc(sizeof(struct Map));

    level->size_x = SIZE_X;
    level->size_y = SIZE_Y;

    level->level = calloc(level->size_y, sizeof(char *));
    for(int i = 0; i < level->size_y; i++)
    {
        level->level[i] = calloc(level->size_x, sizeof(char));
    }

    //Filling 2D array that representates game map
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

    //Calculating number of enemies
    level->enemies = 10 - tries;

    return level;
}

struct Player *GeneratePlayer(int passed_levels)
{
    //Allocating memory for player
    struct Player *player = malloc(sizeof(struct Player));

    //Initialazing player position
    player->position_x = SIZE_X / 2;
    player->position_y = SIZE_Y / 2;

    //Initialazing player health
    player->health = 3;

    //Initialazing passed levels varable
    player->passed_levels = passed_levels;

    return player;
}

struct Enemy **GenerateEnemies(int n)
{
    srand(time(NULL));

    //Allocating memory for array, wich contains pointers to the enemies
    struct Enemy **enemies = calloc(n, sizeof(struct Enemy *));

    //Allocating memory for enemies and generating their coordinates
    for(int i = 0; i < n; i++)
    {
        enemies[i] = malloc(sizeof(struct Enemy));

        enemies[i]->position_x = (rand() % (SIZE_X - 2)) + 1;
        enemies[i]->position_y = (rand() % (SIZE_Y - 2)) + 1;

        enemies[i]->is_alive = true;
        
        enemies[i]->moved = false;
        enemies[i]->move_cooldown = 0;
    }
    return enemies;
}

struct World *CreateWorld(int passed_levels)
{
    struct World *world = malloc(sizeof(struct World));

    world->player = GeneratePlayer(passed_levels);
    world->level = GenerateLevel(world->player->passed_levels);
    world->enemies = GenerateEnemies(world->level->enemies);

    //TODO remove
    //Setting "timer" to zero (actually counter of loops)
    world->time = 0;

    //Setting start point for actual timer
    time(&(world->start_time));

    return world;
}

void FreeWorld(struct World *world)
{
    free(world->level->level);
    free(world->level);

    free(world->player);

    for(int i = 0; i < world->level->enemies; i++)
    {  
        free(world->enemies[i]);
    }
    free(world->enemies);

    free(world);
}