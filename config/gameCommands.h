/*
PANAGIOTIS PAPATHEODOROPOULOS
AM:2022202200160
dit22160@go.uop.gr

NIKOLAS GOGALIS
AM: 2022202200031
dit22031@go.uop.gr
*/

#pragma once

#include "gameBoard.h"

#define GAME_COMMAND_RESULT_ENUM(X) \
    X(NOTHING, "") \
    \
    X(USER_WON, "") \
    \
    X(INVALID_COMMAND, "Invalid command") \
    X(INVALID_CORDINATES, "Invalid coordinates") \
    \
    X(ALREADY_OPENED, "Cell is already opened") \
    X(FOUND_MINE_HAS_LOST, "Cell is a mine") \
    X(OPEN_CELL_SUCCESSFULLY, "Cell opened successfully") \
    X(OPEN_CELLS_SUCCESSFULLY, "Cells opened successfully") \
    \
    X(ALREADY_FLAGGED, "Cell is already marked") \
    X(MARK_CELL_SUCCESSFULLY, "Cell marked successfully") \
    \
    X(CELL_NOT_MARKED, "Cell is not marked") \
    X(UNMARK_CELL_SUCCESSFULLY, "Cell unmarked successfully") \
    \
    X(CHEAT_SUCCESS_MESSAGE, "") \
    \
    X(EXIT, "")

#define GENERATE_ENUM(ENUM, MESSAGE) ENUM,
#define GENERATE_STRING(ENUM, MESSAGE) MESSAGE,

extern int totalCommands;

typedef enum {
    GAME_COMMAND_RESULT_ENUM(GENERATE_ENUM)
} gameCommandResult;

extern char* gameCommandResultMessage[];

typedef struct gameCommand {
    char *name;
    int needsCordinates;
    gameCommandResult (*command)(BoardData **board, int height, int width, int x, int y, void **resultMessage);
} gameCommand;


extern gameCommand gameCommands[];