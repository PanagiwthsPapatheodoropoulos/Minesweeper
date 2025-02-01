/*
PANAGIOTIS PAPATHEODOROPOULOS
AM:2022202200160
dit22160@go.uop.gr

NIKOLAS GOGALIS
AM: 2022202200031
dit22031@go.uop.gr
*/

#pragma once

extern unsigned int gameBoardMaxHeight; /* MAX HEIGHT CAN NOT BE LESS THAN 8*/
extern unsigned int gameBoardMinHeight; /* MIN HEIGHT CAN NOT BE LESS THAN 8*/

extern unsigned int gameBoardMaxWidth; /* MAX WIDTH CAN NOT BE LESS THAN 8*/
extern unsigned int gameBoardMinWidth; /* MIN WIDTH CAN NOT BE LESS THAN 8*/

typedef struct BoardData {
    int isMine; /* BOOLEAN, IF TRUE IT IS @ */
    int isFlagged; /* BOOLEAN, IF TRUE IT IS @ */
    int isRevealed; /* BOOLEAN, IF TRUE IT IS VALUE */
    char value; /* '1', '2', '3', '4', '5', '6', '7', '8', '.', '@' */
} BoardData;

typedef struct StageLevel {
    int level;
    int height;
    int width;
    int totalMines;
    BoardData **board;
} StageLevel;

typedef struct coordinates {
    int x;
    int y;
} coordinates;

void validateGameBoardMinMaxCordinatesConfigData();