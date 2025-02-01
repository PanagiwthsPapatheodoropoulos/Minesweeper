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
#include <math.h>
#include <string.h>

#include "../config/gameBoard.h"
#include "../config/gameCommands.h"
#include "../config/difficulty.h"

#include "game.h"
#include "gameCommands.h"
#include "read.h"
#include "control.h"



void startGame(int gameDifficultyLevel, int gameBoardHeight, int gameBoardWidth, int hasDebugMode) {
    /* CLEAR THE SCREEN */
    clearScreen();


    /* DECLARING VARIABLES */
    int hasAlreadyMadeFirstPlay = 0, totalStages = 1;
    void *resultMessage = NULL;
    gameCommandResult commandResult;
    StageLevel currentStage;



    /* CALCULATE TOTAL STAGES */
    int tempHeight = gameBoardHeight, tempWidth = gameBoardWidth;
    while(tempHeight < gameBoardMaxHeight && tempWidth < gameBoardMaxWidth) {
        tempHeight = (gameBoardHeight + (totalStages * 5) > gameBoardMaxHeight) ? gameBoardMaxHeight : gameBoardHeight + (totalStages * 5);
        tempWidth = (gameBoardWidth + (totalStages * 5) > gameBoardMaxWidth) ? gameBoardMaxWidth : gameBoardWidth + (totalStages * 5);
        totalStages++;
    }



    /* LOOP THROUGH THE STAGES */
    for(int i = 0; i < totalStages; i++) {
        /* RESET */
        hasAlreadyMadeFirstPlay = 0;
        commandResult = NOTHING;


        /* CALCULATE STAGE'S BOARD DIMENSIONS */
        gameBoardHeight = (gameBoardHeight + (i * 5) > gameBoardMaxHeight) ? gameBoardMaxHeight : gameBoardHeight + (i * 5);
        gameBoardWidth = (gameBoardWidth + (i * 5) > gameBoardMaxWidth) ? gameBoardMaxWidth : gameBoardWidth + (i * 5);


        /* CREATE STAGE */
        currentStage.level = i + 1;
        currentStage.height = gameBoardHeight;
        currentStage.width = gameBoardWidth;
        currentStage.totalMines = round(gameBoardHeight * gameBoardWidth * difficultyLevels[gameDifficultyLevel].percentage / 100);
        currentStage.board = createBoard(gameBoardHeight, gameBoardWidth);


        /* PLAY THE GAME */
        while(1) {
            clearScreen();


            /*PRINT GAME DATA*/
            printf("Difficulty level: %s (%d%%)\n", difficultyLevels[gameDifficultyLevel].name, difficultyLevels[gameDifficultyLevel].percentage);
            printf("Game board dimensions (height x width): %d x %d\n", gameBoardHeight, gameBoardWidth);
            printf("Number of mines: %d\n", currentStage.totalMines);
            printf("Stage: %d/%d\n\n", currentStage.level, totalStages);


            /*GENERATE MINES ON FIRST OPEN*/
            if(commandResult ==  OPEN_CELL_SUCCESSFULLY && !hasAlreadyMadeFirstPlay) {
                generateBoard(currentStage.board, currentStage.height, currentStage.width, currentStage.totalMines, ((coordinates *)resultMessage)->x, ((coordinates *)resultMessage)->y);
                openCommand(currentStage.board, currentStage.height, currentStage.width, ((coordinates *)resultMessage)->x, ((coordinates *)resultMessage)->y, &resultMessage);
                hasAlreadyMadeFirstPlay = 1;
            }


            /*PRINT GAME BOARD*/
            printGameBoard(currentStage.board, gameBoardHeight, gameBoardWidth, commandResult == FOUND_MINE_HAS_LOST, hasDebugMode);


            /*EXIT COMMAND*/
            if(commandResult == EXIT) break;


            /* PRINT GAME COMMANDS */
            printGameCommands();


            /* PRINT COMMAND RESULT */
            if(strcmp(gameCommandResultMessage[commandResult], "") != 0) printf("%s\n", gameCommandResultMessage[commandResult]);


            /*CHEAT MESSAGE*/
            if(commandResult == CHEAT_SUCCESS_MESSAGE) printf("%s\n", (char *)resultMessage);

            /*USER WON AND MOVED TO NEW STAGE*/
            else if(commandResult == NOTHING && !hasAlreadyMadeFirstPlay && currentStage.level > 1) printf("You won the previous stage and you moved on to the next one!\n");
    

            /*CHECK IF USER HAS WON*/
            if(commandResult == USER_WON && i < totalStages - 1) break;
            if(commandResult == USER_WON && i == totalStages - 1) {
                askUserToExit("You have won all the stages! Press enter to go back to the main menu.");
                break;
            }


            /*CHECK IF USER HAS LOST*/
            else if(commandResult == FOUND_MINE_HAS_LOST) {
                askUserToExit("You have lost! Press enter to go back to the main menu.");
                break;
            }


            /*GET USER COMMAND*/
            else {
                printf("Enter command: ");
                commandResult = readAndRunGameCommand(currentStage.board, gameBoardHeight, gameBoardWidth, &resultMessage);
            }
        }

        /*FREE THE BOARD*/
        freeBoard(currentStage.board, currentStage.height);

        if(commandResult == EXIT) break;
        if(commandResult == USER_WON) continue;
        if(commandResult == FOUND_MINE_HAS_LOST) break;
    }


    /*FREE RESULT MESSAGE*/
    free(resultMessage);
}





BoardData **createBoard(int height, int width) {
    BoardData **board = (BoardData **)malloc(height * sizeof(BoardData *));

    for(int i = 0; i < height; i++) {
        board[i] = (BoardData *)malloc(width * sizeof(BoardData));
    }

    coordinates cords;

    /*RESET ALL VALUES*/
    for(int i = 0; i < height * width; i++) {
        cords.x = i % width;
        cords.y = i / width;

        board[cords.y][cords.x].isMine = 0;
        board[cords.y][cords.x].isFlagged = 0;
        board[cords.y][cords.x].isRevealed = 0;
        board[cords.y][cords.x].value = 0;
    }

    return board;
}


void freeBoard(BoardData **board, int height) {
    for(int i = 0; i < height; i++) {
        free(board[i]);
    }

    free(board);
}





void generateBoard(BoardData **board, int height, int width, int totalMines, int avoidRow, int avoidCol) {
    /* DECLARE VARIABLES */
    int totalMinesPlaced = 0;
    coordinates randomCord, cords;

    /* PLACE MINES RANDOMLY UNTIL TOTAL MINES ARE PLACED */
    while(totalMinesPlaced < totalMines) {
        randomCord.x = rand() % width;
        randomCord.y = rand() % height;

        /* IF RANDOM CORD HAS THE SAME CORD AS THE AVOID CORD CONTINUE*/
        /* THIS IS USED FOR THE FIRST OPEN CORDINATES TO AVOID MINE */
        if(randomCord.y == avoidRow && randomCord.x == avoidCol) continue;

        /* IF RANDOM CORD ALREADY HAS A MINE CONTINUE */
        if(board[randomCord.y][randomCord.x].isMine) continue;

        /* PLACE MINE */
        board[randomCord.y][randomCord.x].isMine = 1;
        board[randomCord.y][randomCord.x].value = '@';
        totalMinesPlaced++;
    }

    /* PLACE NUMBERS AROUND MINES */
    for(int i = 0; i < height * width; i++) {
        cords.x = i % width;
        cords.y = i / width;

        /* IF CURRENT CELL IS A MINE CONTINUE */
        if(board[cords.y][cords.x].isMine) continue;

        /* IF CURRENT CELL IS NOT A MINE, COUNT MINES AROUND IT */
        int minesAround = 0;

        /* LOOP THROUGH ALL CELLS AROUND THE CURRENT CELL */
        for(int currentRoundRowCell = cords.y - 1; currentRoundRowCell <= cords.y + 1; currentRoundRowCell++) {
            for(int currentRoundColCell = cords.x - 1; currentRoundColCell <= cords.x + 1; currentRoundColCell++) {

                /* IF THE CELL IS OUTSIDE THE BOARD, CONTINUE */
                if(currentRoundRowCell < 0 || currentRoundRowCell >= height || currentRoundColCell < 0 || currentRoundColCell >= width) continue;

                /*CONTINUE IF WE ARE LOOKING CURRENT CELL */
                if(currentRoundRowCell == cords.y && currentRoundColCell == cords.x) continue;

                /* IF THE CELL IS WITHIN THE BOARD AND IS A MINE, INCREMENT MINES AROUND COUNTER */
                if(board[currentRoundRowCell][currentRoundColCell].isMine) minesAround++;

            }
        }

        /*SET THE VALUE OF THE CURRENT CELL BASED ON THE MINES AROUND IT*/
        board[cords.y][cords.x].value = (minesAround > 0) ? ('0' + minesAround) : '.';
    }
}




void printGameBoard(BoardData **board, int height, int width, int hasLost, int hasDebugMode) {

    /* TOTAL DASHES '-' THAT WILL BE USED */
    int totalDashes = width * 3 + 3;


    for(int hasDebug = 0; hasDebug <= hasDebugMode; hasDebug++) {
        /*PRINT FIRST LINE OF NUMBERS WITH THE SEPERATING LINE*/
        printf("   ");
        for(int i = 0; i < width; i++) printf("%3d", i + 1);
        printf("\n");
        for(int i = 0; i < totalDashes; i++) printf("-");
        printf("\n");

        /*PRINT THE BOARD*/
        for(int i = 0; i < height; i++) {
            printf("%2d|", i + 1);

            for(int j = 0; j < width; j++) {
                if(!hasDebug && hasLost && board[i][j].isMine) printf("%3c", '@');
                else if(!hasDebug && board[i][j].isFlagged) printf("%3c", '@');
                else if(!hasDebug && board[i][j].isRevealed) printf("%3c", board[i][j].value ? board[i][j].value : '_');
                else if(!hasDebug) printf("%3c", '#');

                if(hasDebug && board[i][j].isMine) printf("%3c", '@');
                else if(hasDebug) printf("%3c", board[i][j].value ? board[i][j].value : '_');
            }
            
            printf("%2c\n", '|');
        }

        /*PRINT LAST SEPERATING LINE*/
        for(int i = 0; i < totalDashes; i++) printf("-");
        printf("\n\n");
    }
}


void printGameCommands() {
    printf("Commands:\n");
    for(int i = 0; i < totalCommands; i++) {
        if(gameCommands[i].needsCordinates) printf("- %s(Row,Col)\n", gameCommands[i].name);
        else printf("- %s\n", gameCommands[i].name);
    }
    printf("\n");
}


void askUserToExit(char *message) {
    printf("%s\n", message);
    clearBuffer();
}