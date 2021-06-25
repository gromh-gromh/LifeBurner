#pragma once
#define HEALTH 219

//Clear screen
void ClearScreen();

//Draw menu
void DrawMenu(struct Menu *);

//Draw worlds actual state
void DrawFrame(struct World *);

//Draw GUI
void DrawHUD(struct World *);

//Draw Health bar
void DrawHealthBar(struct Player *);

//Draw passed levels
void DrawPassedLevels(struct Player *);