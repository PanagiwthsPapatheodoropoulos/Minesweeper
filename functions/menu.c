/*
PANAGIOTIS PAPATHEODOROPOULOS
AM:2022202200160
dit22160@go.uop.gr

NIKOLAS GOGALIS
AM: 2022202200031
dit22031@go.uop.gr
*/

#include <stdio.h>
#include <stdlib.h>

#include "../config/difficulty.h"

#include "./menu.h"
#include "./read.h"


void printMainMenu() {
    
    /* IF THERE ARE NO DIFFICULTY LEVELS EXIT THE PROGRAM */
    if(totalDifficultyLevels < 1) {
        printf("ERROR: No difficulty levels found!\n");
        exit(1);
    }

    /* PRINTING THE MENU */
    printf("Welcome to Minesweeper game!\nChoose what difficulty you want to play:\n");

    /* PRINTING THE DIFFICULTY LEVELS */
    for (int i = 0; i < totalDifficultyLevels; i++) {
        printf("%d. %s mode (%d%%)", difficultyLevels[i].mode, difficultyLevels[i].name, difficultyLevels[i].percentage);
        if(i != totalDifficultyLevels - 1) printf(" | ");
    }

    /* PRINTING THE EXIT OPTION */
    printf(" | %d. Exit\n", totalDifficultyLevels + 1);

}