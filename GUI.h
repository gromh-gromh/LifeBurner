#pragma once
#include <GUI_generation.h>

#define UPWARDS 'w'
#define DOWNWARDS 's'
#define PRESSED 13

enum direction
{
    up,
    down
};

//Handles interactions with menu
void MenuInteraction(char, struct Menu *);

//Additional function to change selected button
void ChangeSelected(struct Button *, enum direction);