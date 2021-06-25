#pragma once

//Main menu
void MainMenu();

//Main gameplay loop
void PlayLevel(int);

//Waiting for input
void WaitForInput(struct World *);

//Restarting game according on previous progress
void RestartSequence(struct World *);