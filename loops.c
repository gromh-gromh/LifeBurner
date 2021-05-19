#include <generation.h>
#include <loops.h>
#include <world.h>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void PlayLevel(int passed_levels)
{
    struct World *world;
    world = CreateWorld(passed_levels);

    while(world->player->health > 0)
    {
        DecreaseHealth(world);
        DrawFrame(world);
        DrawGUI(world);
        WaitForInput(world);
        EnemiesAI(world);
        if(CheckEnemies(world) == 0)
        {
            break;
        }
    }
    RestartSequence(world);
}

void WaitForInput(struct World *world)
{
        if(kbhit)
        {
            PlayerMovement(world, getch());
        }
}

void RestartSequence(struct World *world)
{
    //Temprorary variable for passed levels
    int temp;
    system("cls");

    ChangePassedLevels(world->player, CheckEnemies(world));
    temp = world->player->passed_levels;
    
    FreeWorld(world);
    PlayLevel(temp);
}