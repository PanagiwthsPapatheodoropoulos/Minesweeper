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
#include <time.h>
#include <string.h>

#include "./config/difficulty.h"
#include "./config/gameBoard.h"
#include "./config/gameCommands.h"

#include "./functions/menu.h"
#include "./functions/read.h"
#include "./functions/game.h"
#include "./functions/control.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    /* CHECK IF BOARD CONFIG DATA ARE CORRECT */
    validateGameBoardMinMaxCordinatesConfigData();

    /* DECLARING VARIABLES */
    int givenMainMenuOption, gameBoardHeight, gameBoardWidth, hasDebugMode = 0;
    int gameDifficultyLevel;

    /*
    USAGE:
    - Use "./executable" for regular gameplay.
    - Use "./executable -debug" to enable debug mode and display the player's table and non-hidden table.
    */
    if(argc == 2 && strcmp(argv[1], "-debug") == 0) hasDebugMode = 1;
    else if(argc >= 2) {
        printf("Invalid arguments! `./executable [-debug]`\n");
        return 1;
    }
    
    while(1) {
        /* CLEAR THE SCREEN */
        clearScreen();

        /* PRINT THE MAIN MENU WITH ALL THE OPTIONS TO USER */
        printMainMenu();

        /* READ THE OPTION SELECTED BY THE USER FROM THE CHOISES OF THE MENU */
        givenMainMenuOption = readMainMenuOption();

        /* IF USER SELECTS EXIT OPTION EXIT THE PROGRAM */
        /* +1 IS THE EXIT OPTION */
        if(givenMainMenuOption == totalDifficultyLevels + 1) break;

        /* IF OPTION IS NOT EXIT OPTION SET THE DIFFICULTY LEVEL */
        /* -1 BECAUSE THE DIFFICULTY ARRAY STARTS FROM 0 */
        gameDifficultyLevel = givenMainMenuOption - 1;

        /* READ THE DIMENSIONS OF THE GAME BOARD FROM USER */
        readGameBoardDimensions(&gameBoardHeight, &gameBoardWidth);

        /* START GAME */
        startGame(gameDifficultyLevel, gameBoardHeight, gameBoardWidth, hasDebugMode);
    }

    printf("Thank you for playing Minesweeper!\n");

    return 0;
}
