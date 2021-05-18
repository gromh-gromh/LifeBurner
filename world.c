#include <generation.h>
#include <world.h>
#include <stdio.h>
#include <time.h>

void PlayerMovement(struct World *world, char key)
{
    int prev_x = world->player->position_x;
    int prev_y = world->player->position_y;

    switch(key)
    {
        case UP:
            world->player->position_y--;
            break;
        case DOWN:
            world->player->position_y++;
            break;
        case RIGHT:
            world->player->position_x++;
            break;
        case LEFT:
            world->player->position_x--;
            break;
    }

    switch(CollisionCheck(world))
    {
        case wall:
            world->player->position_x = prev_x;
            world->player->position_y = prev_y;
            break;
        case enemy:
            world->player->health++;
    }
}

enum Collision CollisionCheck(struct World* world)
{
    if(world->level->level[world->player->position_y][world->player->position_x] == (char)WALL)
    {
        return wall;
    }

    for(int i = 0; i < world->level->enemies; i++)
    {
        if(world->player->position_x == world->enemies[i]->position_x && world->player->position_y == world->enemies[i]->position_y && world->enemies[i]->is_alive)
        {
            world->enemies[i]->is_alive = false;
            return enemy;
        }
    }
}

void DecreaseHealth(struct World *world)
{
    world->time ++;
    if(world->time % 15 == 0)
    {
        world->player->health--;
    }
}