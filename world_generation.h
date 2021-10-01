#pragma once
#include <time.h>

#define SIZE_X 50
#define SIZE_Y 20
#define WALL 178
#define EMPTY 32
#define PLAYER 254
#define ENEMY 253     

enum bool
{
    false,
    true
};

enum player_direction
{
    NONE,
    positive,
    negative
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
    enum player_direction movement_direction_x;
    enum player_direction movement_direction_y;
    int passed_levels;
    int health;
    int time_health_cheked;
    float speed;
};

struct Enemy
{
    int position_x;
    int position_y;
    enum bool is_alive;
    enum bool moved;
    int move_cooldown;
    int time_cooldown_cheked;
};

struct World
{
    struct Map *level;
    struct Player *player;
    struct Enemy **enemies;
    time_t start_time;
};

//Generate level
struct Map *GenerateLevel(int);

//Generate player character
struct Player *GeneratePlayer(int);

//Generate enemies
struct Enemy **GenerateEnemies(int);

//Combining all generated structures in one
struct World *CreateWorld(int);

//Free allocated memory for world
void FreeWorld(struct World *);