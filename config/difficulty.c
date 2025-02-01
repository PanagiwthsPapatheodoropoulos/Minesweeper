/*
PANAGIOTIS PAPATHEODOROPOULOS
AM:2022202200160
dit22160@go.uop.gr

NIKOLAS GOGALIS
AM: 2022202200031
dit22031@go.uop.gr
*/

#include "difficulty.h"

/* CREATING THE ARRAY OF THE DIFFICULTY LEVELS */
difficultyLevel difficultyLevels[] = {
    {1, "Easy", 10},
    {2, "Medium", 15},
    {3, "Hard", 20},
    {4, "Impossible", 25}
};

/* GETTING THE TOTAL NUMBER OF DIFFICULTY LEVELS */
int totalDifficultyLevels = sizeof(difficultyLevels) / sizeof(difficultyLevels[0]);