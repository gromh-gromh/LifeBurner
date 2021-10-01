#pragma once

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define ESC 27
#define HEALTH_DECREASE_RATE 3
#define ENEMY_MOVEMENT_COOLDOWN 2
#define DRAG 0.2
#define MAX_SPEED 2

enum Collision
{
    wall,
    enemy,
    none
};

enum Axis
{
    y,
    x
};

//Change player position or menu call according on input
void PlayerInput(struct World *, char);

void PlayerMovement(struct World *);

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

