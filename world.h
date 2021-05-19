#pragma once

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define HEALTH_DECREASE_RATE

enum Collision
{
    wall,
    enemy
};

//Change player position according on input
void PlayerMovement(struct World *, char);

//Decrease health over time
void DecreaseHealth(struct World *);

//Check alive enemies
int CheckEnemies(struct World *);

//Change passed levels values according on progress
void ChangePassedLevels(struct Player *, int);

//Enemies artificial intellegence
void EnemiesAI(struct World*);

//Checks for player collision
enum Collision CollisionCheck(struct World *);

