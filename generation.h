#pragma once

#define SIZE_X 50
#define SIZE_Y 20
#define WALL 178
#define EMPTY 32
#define PLAYER 254
#define ENEMY 216      

enum bool
{
    false,
    true
};

struct Map
{
    int size_x;
    int size_y;
    char **level;
    int enemies;
};

struct Player
{
    int position_x;
    int position_y;
    int passed_levels;
    int health;
};

struct Enemy
{
    int position_x;
    int position_y;
    enum bool is_alive;
};

struct World
{
    struct Map *level;
    struct Player *player;
    struct Enemy **enemies;
    int time;
};

//Generates level
struct Map *GenerateLevel(int);

//Generates player character
struct Player *GeneratePlayer(int);

//Generates enemies
struct Enemy **GenerateEnemies(int);

//Combining all generated structures in one
struct World *CreateWorld(int);

//Frees allocated for world memory
void FreeWorld(struct World *);