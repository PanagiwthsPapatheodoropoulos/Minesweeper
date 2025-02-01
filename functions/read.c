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
#include <string.h>

#include "../config/difficulty.h"
#include "../config/gameBoard.h"

#include "read.h"
#include "control.h"
#include "gameCommands.h"


int readMainMenuOption() {
    int option = 0;

    do {
        printf("Select option [1-%d]: ", totalDifficultyLevels + 1);
        scanf("%d", &option);
        clearBuffer();

        if(option < 1 || option > totalDifficultyLevels + 1) printf("Invalid option! Try again.\n");
    } while(option < 1 || option > totalDifficultyLevels + 1);

    return option;
}


void readGameBoardDimensions(int *height, int *width) {
    /* GETTING THE HEIGHT OF THE GAME BOARD */
    do {
        printf("Enter the height of the game board [%d-%d]: ", gameBoardMinHeight, gameBoardMaxHeight);
        scanf("%d", height);
        clearBuffer();

        if(*height < gameBoardMinHeight || *height > gameBoardMaxHeight) printf("Invalid height! Try again.\n");
    } while(*height < gameBoardMinHeight || *height > gameBoardMaxHeight);


    /* GETTING THE WIDTH OF THE GAME BOARD */
    do {
        printf("Enter the width of the game board [%d-%d]: ", gameBoardMinWidth, gameBoardMaxWidth);
        scanf("%d", width);
        clearBuffer();

        if(*width < gameBoardMinWidth || *width > gameBoardMaxWidth) printf("Invalid width! Try again.\n");
    } while(*width < gameBoardMinWidth || *width > gameBoardMaxWidth);
}




int readText(char saveToArray[], unsigned int maxLength) {

    /*DECLARING VARIABLES*/
    char givenString[maxLength + 2];
    int givenStringLength = 0;

    /*GETTING THE STRING FROM THE USER*/
    fgets(givenString, sizeof(givenString), stdin);

    /*GETTING THE LENGTH OF THE STRING*/
    givenStringLength = strlen(givenString);

    /*IF THE LAST CHARACTER IS A NEWLINE CHARACTER*/
    if(givenString[givenStringLength - 1] == '\n') {
        givenString[givenStringLength - 1] = '\0';
        givenStringLength--;
    }

    /*IF THE LAST CHARACTER IS NOT A NEWLINE CHARACTER CLEAR INPUT AND RETURN 0*/
    else if(givenString[givenStringLength - 1] != '\0') {
        clearBuffer();
        return 0;
    }

    /*IF THE STRING LENGTH IS GREATER THAN MAXLENGTH RETURN 0*/
    if(givenStringLength > maxLength) return 0;

    /*SAVING THE STRING TO THE ARRAY*/
    strcpy(saveToArray, givenString);

    return 1;
}




gameCommandResult readAndRunGameCommand(BoardData **board, int height, int width, void **resultMessage) {
    /* DECLARE VARIABLES */
    char givenCommand[20];
    int selectedRow, selectedColumn;

    /* GETTING THE COMMAND FROM THE USER */
    int result = readText(givenCommand, sizeof(givenCommand) - 1);
    
    /* IF THE USER TYPES SOMETHING GREATER THAN 20 CHARACTERS IT MEANS INVALID COMMAND */
    if(result == 0) {
        printf("Invalid command! Try again.\n");
        return INVALID_COMMAND;
    }

    /* CHECK FIRST IF THE USER WANTS TO EXIT */
    if(strcmp(givenCommand, "exit") == 0) return EXIT;

    /* VALIDATE AND RUN COMMAND */
    for(int i = 0; i < totalCommands; i++) {

        /* CONTINUE IF THE COMMAND IS NOT THE ONE WE ARE LOOKING FOR */
        if(strncmp(givenCommand, gameCommands[i].name, strlen(gameCommands[i].name)) != 0) continue;

        /* CHECK IF USER HAS WRONG SYNTAX FOR CORDINATES */
        if(givenCommand[strlen(gameCommands[i].name)] != '(') return INVALID_COMMAND;
        if(givenCommand[strlen(givenCommand) - 1] != ')') return INVALID_COMMAND;

        /* AFTER CHECKING SYNTAX GET THE CORDINATES */
        char commandSyntax[20];
        strcpy(commandSyntax, gameCommands[i].name);
        strcat(commandSyntax, "(%d,%d)");
        if(sscanf(givenCommand, commandSyntax, &selectedRow, &selectedColumn) != 2) return INVALID_COMMAND;

        /* RUN THE COMMAND */
        return gameCommands[i].command(board, height, width, selectedRow - 1, selectedColumn - 1, resultMessage);
    }

    return INVALID_COMMAND;
}