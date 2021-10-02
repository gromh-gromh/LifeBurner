#include <world_generation.h>
#include <world.h>
#include <loops.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <timer.h>

void PlayerInput(struct World *world, char key)
{
    //Change player/game state according on input
    switch(key)
    {
        case UP:
            world->player->movement_direction_y = negative;
            world->player->movement_direction_x = NONE;
            world->player->speed = MAX_SPEED;
            break;
        case DOWN:
            world->player->movement_direction_y = positive;
            world->player->movement_direction_x = NONE;
            world->player->speed = MAX_SPEED;
            break;
        case RIGHT:
            world->player->movement_direction_x = positive;
            world->player->movement_direction_y = NONE;
            world->player->speed = MAX_SPEED;
            break;
        case LEFT:
            world->player->movement_direction_x = negative;
            world->player->movement_direction_y = NONE;
            world->player->speed = MAX_SPEED;
            break;
        case ESC:
            PauseMenu();
    }
}

void PlayerMovement(struct World *world)
{
    //Saving player position before movement
    int prev_x = world->player->position_x;
    int prev_y = world->player->position_y;

    //Change player position
    switch(world->player->movement_direction_y)
    {
        case negative:
            world->player->position_y -= (int)world->player->speed;
            break;
        case positive:
            world->player->position_y += (int)world->player->speed;
            break;
    }

    switch(world->player->movement_direction_x)
    {
        case negative:
            world->player->position_x -= (int)world->player->speed;
            break;
        case positive:
            world->player->position_x += (int)world->player->speed;
            break;
    }

    //Check for collision
    switch(PlayerCollisionCheck(world))
    {
        case wall:
            //Return player to the previous position
            world->player->position_x = prev_x;
            world->player->position_y = prev_y;

            //Reverse direction
            switch(world->player->movement_direction_y)
            {
                case negative:
                    world->player->movement_direction_y = positive;
                    break;
                case positive:
                    world->player->movement_direction_y = negative;
                    break;
            }

            switch(world->player->movement_direction_x)
            {
                case negative:
                    world->player->movement_direction_x = positive;
                    break;
                case positive:
                    world->player->movement_direction_x = negative;
                    break;
            }

            break;
        case enemy:
            //Increase player health
            world->player->health++;
    }

    //Decrease speed
    if(world->player->speed > 0)
    {
        world->player->speed -= DRAG;
    }
}

enum Collision PlayerCollisionCheck(struct World* world)
{   
    if((world->player->position_x < 0) || (world->player->position_x > SIZE_X - 1) || (world->player->position_y < 0) || (world->player->position_y > SIZE_Y - 1))
    {
        return wall;
    }

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

    return none;
}

void DecreaseHealth(struct World *world)
{
    int time = (int)GetTime(world);
    if((time % HEALTH_DECREASE_RATE == 0) && (time != world->player->time_health_cheked))
    {
        world->player->health--;
        world->player->time_health_cheked = time;
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

enum bool EnemyCollisionCheck(struct World *world, int n)
{
    enum bool is_collided = false;

    //Cheks collision with wall
    if(world->level->level[world->enemies[n]->position_y][world->enemies[n]->position_x] == (char)WALL)
    {
        is_collided = true;
    }

    return is_collided;
}

void EnemiesMovement(struct World *world, enum Axis axis, int n)
{
    srand(time(NULL));

    //Save previous position of enemy
    int prev_x = world->enemies[n]->position_x;
    int prev_y = world->enemies[n]->position_y;

    switch(axis)
    {
        //Move enemy according on player position
        case x:
            if(rand() % 2 == 0)
            {
                world->enemies[n]->position_y--;
            } else
            {
                world->enemies[n]->position_y++;
            }
            break;
        case y:
            if(rand() % 2 == 0)
            {
                world->enemies[n]->position_x--;
            } else 
            {
                world->enemies[n]->position_x++;
            }
            break;
    }

    //Redo move based on collision check result
    if(EnemyCollisionCheck(world, n) == true)
    {
        world->enemies[n]->position_x += 2 * (prev_x - world->enemies[n]->position_x);
        world->enemies[n]->position_y += 2 * (prev_y - world->enemies[n]->position_y);
    }

}

void EnemiesAI(struct World *world)
{
    //Cheks for player approximation
    for(int i = 0; i < world->level->enemies; i++)
    {
        if(world->enemies[i]->moved == false)
        {
            if(abs(world->enemies[i]->position_x - world->player->position_x) == 1 && world->enemies[i]->position_y == world->player->position_y)
            {
                EnemiesMovement(world, x, i);
                //Sets cooldown on movement
                world->enemies[i]->moved = true;
                world->enemies[i]->move_cooldown = ENEMY_MOVEMENT_COOLDOWN; 
            }

            if(abs(world->enemies[i]->position_y - world->player->position_y) == 1 && world->enemies[i]->position_x == world->player->position_x)
            {
                EnemiesMovement(world, y, i);
                //Sets cooldown on movement
                world->enemies[i]->moved = true;
                world->enemies[i]->move_cooldown = ENEMY_MOVEMENT_COOLDOWN; 
            }
        } else
        {
            if(GetTime(world) != world->enemies[i]->time_cooldown_cheked)
            {
                world->enemies[i]->move_cooldown--;
                world->enemies[i]->time_cooldown_cheked = GetTime(world);
            }

            if(world->enemies[i]->move_cooldown == 0)
            {
                world->enemies[i]->moved = false;
            }
        }
    }
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