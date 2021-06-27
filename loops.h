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

//Pause menu
void PauseMenu();

//Main gameplay loop
void PlayLevel(int);

//Restarting game according on previous progress
void RestartSequence(struct World *);

//Exit game
void ExitGame();