#include <stdlib.h>
#include <GUI_generation.h>
#include <loops.h>

struct Menu *GenerateMainMenu()
{
    //Menu memory allocation
    struct Menu *main_menu = malloc(sizeof(struct Menu));

    //Allocating memory for buttons
    struct Button *start_button = malloc(sizeof(struct Button));
    struct Button *settings_button = malloc(sizeof(struct Button));
    struct Button *exit_button = malloc(sizeof(struct Button));

    //Buttons initialization
    start_button->prev = exit_button;
    start_button->name = "Start game";
    start_button->action = (&PlayLevel);
    start_button->action_argument = (int)0;
    start_button->isSelected = true;
    start_button->next = settings_button;

    settings_button->prev = start_button;
    settings_button->name = "Settings";
    settings_button->action = NULL;
    settings_button->action_argument = NULL;
    settings_button->isSelected = false;
    settings_button->next = exit_button;

    exit_button->prev = settings_button;
    exit_button->name = "Exit game";
    exit_button->action = NULL;
    exit_button->action_argument = NULL;
    exit_button->isSelected = false;
    exit_button->next = start_button;

    //Menu inizialization
    main_menu->head = start_button;
    main_menu->tail = exit_button;
}