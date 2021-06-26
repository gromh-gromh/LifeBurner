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

    while(main_menu->isOpened == true)
    {
        DrawMenu(main_menu);
        MenuInteraction(getch(), main_menu);
    }
}

void HelpMenu()
{
    struct Menu *help_menu = GenerateHelpMenu();

    while(help_menu->isOpened == true)
    {
        DrawMenu(help_menu);
        MenuInteraction(getch(), help_menu);
    }
}

void CreditsMenu()
{
    struct Menu *credits_menu = GenerateCreditsMenu();

    while(credits_menu->isOpened == true)
    {
        DrawMenu(credits_menu);
        MenuInteraction(getch(), credits_menu);
    }
}

void PauseMenu()
{
    struct Menu *pause_menu = GeneratePauseMenu();

    while(pause_menu->isOpened == true)
    {
        DrawMenu(pause_menu);
        MenuInteraction(getch(), pause_menu);
    }
}

void EndScreenMenu()
{
    MainMenu();
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
        PlayerInput(world, getch());
        EnemiesAI(world);
        if(CheckEnemies(world) == 0)
        {
            break;
        } 
    }

    RestartSequence(world);
}

void RestartSequence(struct World *world)
{
    //Temprorary variable for passed levels
    int temp;
    system("cls");

    ChangePassedLevels(world->player, CheckEnemies(world));
    temp = world->player->passed_levels;
    
    FreeWorld(world);

    if(temp < 10)
    {
        PlayLevel(temp);
    } else 
    {
        EndScreenMenu();
    }
}

void ExitGame()
{
    exit(0);
}