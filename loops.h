#pragma once

//Main menu
void MainMenu();

//Help menu
void HelpMenu();

//Credits menu
void CreditsMenu();

//End screen menu
void EndScreenMenu();

//Main gameplay loop
void PlayLevel(int);

//Pause menu
void PauseMenu();

//Restarting game according on previous progress
void RestartSequence(struct World *);

//Exit game
void ExitGame();