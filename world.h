#pragma once

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define ESC 27
#define HEALTH_DECREASE_RATE 15

enum Collision
{
    wall,
    enemy
};

enum Axis
{
    y,
    x
};

//Change player position or menu call according on input
void PlayerInput(struct World *, char);

//Decrease health over time
void DecreaseHealth(struct World *);

//Check alive enemies
int CheckEnemies(struct World *);

//Change passed levels values according on progress
void ChangePassedLevels(struct Player *, int);

//Enemies movemeent
void EnemiesMovement(struct World *, enum Axis, int);

//Enemies artificial intellegence
void EnemiesAI(struct World*);

//Checks for player collision
enum Collision PlayerCollisionCheck(struct World *);

//Checks for enemies collision
enum bool EnemyCollisionCheck(struct World *, int);

