#include <GUI_generation.h>
#include <world_generation.h>
#include <loops.h>
#include <GUI.h>
#include <world.h>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void MainMenu()
{
    struct Menu *main_menu = GenerateMainMenu();
    DrawMenu(main_menu);

    while(1)
    {
        MenuInteraction(getch(), main_menu);
        DrawMenu(main_menu);
    }
}

void PlayLevel(int passed_levels)
{
    struct World *world;
    world = CreateWorld(passed_levels);

    while(world->player->health > 0)
    {
        DecreaseHealth(world);
        DrawFrame(world);
        DrawHUD(world);
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