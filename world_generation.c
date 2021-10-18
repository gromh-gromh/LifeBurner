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

    //Initialazing player movement direction
    player->movement_direction_x = NONE;
    player->movement_direction_y = NONE;

    //Initializimg player speed
    player->speed = 0;

    //Initialazing player health
    player->health = 3;
    player->time_health_cheked = 0;

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
        enemies[i]->time_cooldown_cheked = 0;
    }
    return enemies;
}

struct Buffers *GenerateBuffers()
{
    struct Buffers *buffers = malloc(sizeof(struct Buffers));

    //Allocationg array for combining all objects
    buffers->object_buffer = calloc(SIZE_Y, sizeof(char *));
    for(int i = 0; i < SIZE_Y; i++)
    {
        buffers->object_buffer[i] = calloc(SIZE_X, sizeof(char));
    }

    return buffers;
}

struct World *CreateWorld(int passed_levels)
{
    struct World *world = malloc(sizeof(struct World));

    world->player = GeneratePlayer(passed_levels);
    world->level = GenerateLevel(world->player->passed_levels);
    world->enemies = GenerateEnemies(world->level->enemies);
    world->buffers = GenerateBuffers();

    //Setting start point for timer
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

    free(world->buffers->object_buffer);
    //free(world->buffers->graphic_buffer);
    free(world->buffers);

    free(world);
}