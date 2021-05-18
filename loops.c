#include <generation.h>
#include <loops.h>
#include <world.h>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void PlayLevel()
{
    struct World *world;
    world = CreateWorld();

    while(world->player->health > 0)
    {
        DecreaseHealth(world);
        DrawFrame(world);
        DrawGUI(world);
        WaitForInput(world);
    }

    system("cls");
}

void WaitForInput(struct World *world)
{
        if(kbhit)
        {
            PlayerMovement(world, getch());
        }
}