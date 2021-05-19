#include <generation.h>
#include <world.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void PlayerMovement(struct World *world, char key)
{
    //Saving player position before movement
    int prev_x = world->player->position_x;
    int prev_y = world->player->position_y;

    //Move player according on input
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

    //Check for collision
    switch(CollisionCheck(world))
    {
        case wall:
            //Return player to the previous position
            world->player->position_x = prev_x;
            world->player->position_y = prev_y;
            break;
        case enemy:
            //Increase player health
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
            //"Killing" enemy
            world->enemies[i]->is_alive = false;
            return enemy;
        }
    }
}

void DecreaseHealth(struct World *world)
{
    world->time ++;
    if(world->time % HEALTH_DECREASE_RATE == 0)
    {
        world->player->health--;
        //Temprorary call to avoid graphic bug
        system("cls");
    }
}

int CheckEnemies(struct World *world)
{
    int enemy_counter = 0;
    for(int i = 0; i < world->level->enemies; i++)
    {
        if(world->enemies[i]->is_alive == true)
        {
            enemy_counter++;
        }
    }
    return enemy_counter;
}

void EnemiesAI(struct World *world)
{
    
}

void ChangePassedLevels(struct Player *player, int enemies)
{
    if(enemies == 0)
    {
        player->passed_levels++;
    } else
    {
        player->passed_levels = 0;
    }
}