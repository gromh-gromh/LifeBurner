#pragma once
#include <world_generation.h>

//Representation of button as node of doubly linked list
struct Button
{
    struct Button *prev;
    char *name;
    void *action_argument;
    void (*action)();
    enum bool isSelected;
    struct Button *next;
};

//Representation of menu as doubly linked list
struct Menu
{
    struct Button *head;
    struct Button *tail;
};

//Generates hard coded main menu
struct Menu *GenerateMainMenu();

//Generates hard coded pause menu
struct Menu *GeneratePauseMenu();

//Frees allocated for menu memory
void FreeMenu();