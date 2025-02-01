/*
PANAGIOTIS PAPATHEODOROPOULOS
AM:2022202200160
dit22160@go.uop.gr

NIKOLAS GOGALIS
AM: 2022202200031
dit22031@go.uop.gr
*/

#include "gameCommands.h"

#include "../functions/gameCommands.h"

/* CREATING THE ARRAY OF COMMANDS*/
gameCommand gameCommands[] = {
    {"open", 1, openCommand},
    {"mark", 1, markCommand},
    {"unmark", 1, unmarkCommand},
    {"cheat", 1, cheatCommand},
    {"exit", 0, exitCommand}
};

char* gameCommandResultMessage[] = {
    GAME_COMMAND_RESULT_ENUM(GENERATE_STRING)
};


/* GETTING THE TOTAL NUMBER OF DIFFICULTY LEVELS */
int totalCommands = sizeof(gameCommands) / sizeof(gameCommands[0]);