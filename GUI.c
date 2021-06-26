#include <GUI.h>
#include <GUI_generation.h>

void MenuInteraction(char key, struct Menu *menu)
{
    struct Button *selected_button = menu->head;
    while(selected_button->isSelected != true)
    {
        selected_button = selected_button->next;
    }

    switch(key)
    {
        case UPWARDS:
            ChangeSelected(selected_button, up);
            break;
        case DOWNWARDS:
            ChangeSelected(selected_button, down);
            break;
        case PRESSED:
            menu->isOpened = false;
            FreeMenu(menu);
            if(selected_button->action)
            {
                selected_button->action(selected_button->action_argument);
                break;
            }
    }
};

void ChangeSelected(struct Button *button, enum direction direction)
{
    button->isSelected = false;

    switch(direction)
    {
        case up:
            button->prev->isSelected = true;
            break;
        case down:
            button->next->isSelected = true;
            break;
    }
}