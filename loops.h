#pragma once

//Main menu
void MainMenu();

//Help menu
void HelpMenu();

//Credits menu
void CreditsMenu();

//End screen menu
void EndScreenMenu();

//Death screen menu
void DeathScreenMenu();

//Gameplay loop
void PlayLevel(int);

//Gather input if keyboard was hit
void GatherInput(struct World *);

//Pause menu
void PauseMenu();

//Restarting game according on previous progress
void RestartSequence(struct World *);

//Exit game
void ExitGame();