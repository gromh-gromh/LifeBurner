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
    struct Menu *end_screen_menu = GenerateEndScreenMenu();

    while(end_screen_menu->isOpened == true)
    {
        DrawMenu(end_screen_menu);
        MenuInteraction(getch(), end_screen_menu);
    }
}

void DeathScreenMenu()
{
    struct Menu *death_screen_menu = GenerateDeathScreenMenu();

    while(death_screen_menu->isOpened == true)
    {
        DrawMenu(death_screen_menu);
        MenuInteraction(getch(), death_screen_menu);
    }
}

void PlayLevel(int passed_levels)
{
    struct World *world;
    world = CreateWorld(passed_levels);

    while(world->player->health > 0)
    {
        DrawFrame(world);
        DrawHUD(world);
        PlayerInput(world, getch());
        DecreaseHealth(world);
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
    //Temprorary variables
    int temp_levels;
    int temp_health;

    ChangePassedLevels(world->player, CheckEnemies(world));
    temp_levels = world->player->passed_levels;
    temp_health = world->player->health;
    
    FreeWorld(world);

    if(temp_levels < 10)
    {
        if(temp_health > 0)
        {
            PlayLevel(temp_levels);
        } else
        {
            DeathScreenMenu();
        }
    } else 
    { 
        EndScreenMenu();
    }
}

void ExitGame()
{
    exit(0);
}