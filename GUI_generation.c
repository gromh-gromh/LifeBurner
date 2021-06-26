#include <stdlib.h>
#include <GUI_generation.h>
#include <loops.h>

struct Menu *GenerateMainMenu()
{
    //Menu memory allocation
    struct Menu *main_menu = malloc(sizeof(struct Menu));

    //Allocating memory for buttons
    struct Button *start_button = malloc(sizeof(struct Button));
    struct Button *help_button = malloc(sizeof(struct Button));
    struct Button *credits_button = malloc(sizeof(struct Button));
    struct Button *exit_button = malloc(sizeof(struct Button));

    //Buttons initialization
    start_button->prev = exit_button;
    start_button->name = "Start game";
    start_button->action = (&PlayLevel);
    start_button->action_argument = (int)0;
    start_button->isSelected = true;
    start_button->next = help_button;

    help_button->prev = start_button;
    help_button->name = "Help";
    help_button->action = (&HelpMenu);
    help_button->action_argument = NULL;
    help_button->isSelected = false;
    help_button->next = credits_button;

    credits_button->prev = help_button;
    credits_button->name = "Credits";
    credits_button->action = (&CreditsMenu);
    credits_button->action_argument = NULL;
    credits_button->isSelected = false;
    credits_button->next = exit_button;

    exit_button->prev = credits_button;
    exit_button->name = "Exit game";
    exit_button->action = (&ExitGame);
    exit_button->action_argument = NULL;
    exit_button->isSelected = false;
    exit_button->next = start_button;

    //Menu inizialization
    main_menu->head = start_button;
    main_menu->tail = exit_button;
    main_menu->name = "L I F E B U R N E R\nMain menu\n";
    main_menu->isOpened = true;

    return main_menu;
}

struct Menu *GeneratePauseMenu()
{
    //Menu memory allocation
    struct Menu *pause_menu = malloc(sizeof(struct Menu));

    //Buttons memory allocation
    struct Button *resume_button = malloc(sizeof(struct Button));
    struct Button *restart_button = malloc(sizeof(struct Button));
    struct Button *main_menu_button = malloc(sizeof(struct Button));
    struct Button *exit_button = malloc(sizeof(struct Button));

    //Buttons initizlization
    resume_button->prev = exit_button;
    resume_button->name = "Resume game";
    resume_button->action_argument = NULL;
    resume_button->action = NULL;
    resume_button->isSelected = true;
    resume_button->next = restart_button;

    restart_button->prev = resume_button;
    restart_button->name = "Restart game";
    restart_button->action_argument = (int)0;
    restart_button->action = (&PlayLevel);
    restart_button->isSelected = false;
    restart_button->next = main_menu_button;

    main_menu_button->prev = restart_button;
    main_menu_button->name = "Main menu";
    main_menu_button->action_argument = NULL;
    main_menu_button->action = (&MainMenu);
    main_menu_button->isSelected = false;
    main_menu_button->next = exit_button;

    exit_button->prev = main_menu_button;
    exit_button->name = "Exit game";
    exit_button->action_argument = NULL;
    exit_button->action = (&ExitGame);
    exit_button->isSelected = false;
    exit_button->next = resume_button;

    //Menu inizialization
    pause_menu->head = resume_button;
    pause_menu->tail = exit_button;
    pause_menu->name = "Game paused\n";
    pause_menu->isOpened = true;

    return pause_menu;

}

struct Menu *GenerateHelpMenu()
{
    //Menu memory allocation
    struct Menu *help_menu = malloc(sizeof(struct Menu));

    //Button memory allocation
    struct Button *return_button = malloc(sizeof(struct Button));

    //Button inititalization
    return_button->prev = return_button;
    return_button->name = "Return";
    return_button->action_argument = NULL;
    return_button->action = (&MainMenu);
    return_button->isSelected = true;
    return_button->next = return_button;

    //Menu initialization
    help_menu->head = return_button;
    help_menu->tail = return_button;
    help_menu->name = "Menu navigation:\nw - up\ns - down\nEnter - select\n\nGame controls:\nw - up\ns - down\na - left\nd - right\nEsc - pause menu\n";
    help_menu->isOpened = true;

    return help_menu;
}

struct Menu *GenerateCreditsMenu()
{
    //Menu memory allocation
    struct Menu *credits_menu = malloc(sizeof(struct Menu));

    //Button memory allocation
    struct Button *return_button = malloc(sizeof(struct Button));

    //Button inititalization
    return_button->prev = return_button;
    return_button->name = "Return";
    return_button->action_argument = NULL;
    return_button->action = (&MainMenu);
    return_button->isSelected = true;
    return_button->next = return_button;

    //Menu initialization
    credits_menu->head = return_button;
    credits_menu->tail = return_button;
    credits_menu->name = "Created as university project by gromh\nsoundcloud.com/gromh\n";
    credits_menu->isOpened = true;

    return credits_menu;
}

void FreeMenu(struct Menu *menu)
{
    struct Button *button = menu->tail;
    struct Button *next_button;
    do
    {
        next_button = button->next;
        free(button);
        button = next_button;
    } while(button != menu->tail);

    free(menu);
}