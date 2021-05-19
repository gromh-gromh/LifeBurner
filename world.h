#pragma once

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

enum Collision
{
    wall,
    enemy
};

void PlayerMovement(struct World *, char);

void DecreaseHealth(struct World *);

int CheckEnemies(struct World *);

void ChangePassedLevels(struct Player *, int);

enum Collision CollisionCheck(struct World *);

