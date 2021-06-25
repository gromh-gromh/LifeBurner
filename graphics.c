#include <GUI_generation.h>
#include <world_generation.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

void ClearScreen()
{	
    COORD cursorPosition;	
    cursorPosition.X = 0;	
    cursorPosition.Y = 0;	
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void DrawMenu(struct Menu *menu)
{
    system("cls");

    struct Button *button = menu->tail;

    do
    {
        button = button->next;

        printf("%s ", button->name);
        if(button->isSelected == true)
        {
            printf("[]");
        }
        printf("\n");

    } while(button != menu->tail);
};

void DrawFrame(struct World *world)
{
    ClearScreen();
    //Allocationg array for combining all parts in one frame
    char **level_picture = calloc(world->level->size_y, sizeof(char *));
    for(int i = 0; i < world->level->size_y; i++)
    {
        level_picture[i] = calloc(world->level->size_x, sizeof(char));
    }

    //Combining parts
    for(int i = 0; i < world->level->size_y; i++)
    {
        for(int j = 0; j < world->level->size_x; j++)
        {
            level_picture[i][j] = world->level->level[i][j];
        }
    }

    for(int i = 0; i < world->level->enemies; i++)
    {
        if(world->enemies[i]->is_alive == true)
        {
            level_picture[world->enemies[i]->position_y][world->enemies[i]->position_x] = ENEMY;
        }
    }

    level_picture[world->player->position_y][world->player->position_x] = PLAYER;

    //Drawing world
    for(int i = 0; i < world->level->size_y; i++)
    {
        for(int j = 0; j < world->level->size_x; j++)
        {
            printf("%c", level_picture[i][j]);
        }
        printf("\n");
    }

    free(level_picture);
}

void DrawHUD(struct World *world)
{
    DrawHealthBar(world->player);
    DrawPassedLevels(world->player);
}

void DrawHealthBar(struct Player *player)
{
    for(int i = 0; i < player->health; i++)
    {
        printf("%c ", HEALTH);
    }
}

void DrawPassedLevels(struct Player *player)
{
    printf("\nPassed levels: %d", player->passed_levels);
}