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

#include "gameBoard.h"

#define MINIMUM_BOARD_HEIGHT_AND_WIDTH 8


unsigned int gameBoardMaxHeight = 16;
unsigned int gameBoardMinHeight = 8;

unsigned int gameBoardMaxWidth = 32;
unsigned int gameBoardMinWidth = 8;


void validateGameBoardMinMaxCordinatesConfigData() {
    /* MIN HEIGHT CAN NOT BE GREATER THAN MAX HEIGHT */
    if(gameBoardMaxHeight < gameBoardMinHeight) {
        printf("ERROR: Invalid board height range!\n");
        exit(1);
    }

    /* MIN WIDTH CAN NOT BE GREATER THAN MAX WIDTH */
    if(gameBoardMaxWidth < gameBoardMinWidth) {
        printf("ERROR: Invalid board width range!\n");
        exit(1);
    }

    /* MAX/MIN HEIGHT/WIDTH CAN NOT BE LESS THAN 8 */
    if(gameBoardMaxHeight < MINIMUM_BOARD_HEIGHT_AND_WIDTH) {
        printf("ERROR: Invalid board max height range! gameBoardMaxHeight >= 8\n");
        exit(1);
    }
    if(gameBoardMaxWidth < MINIMUM_BOARD_HEIGHT_AND_WIDTH) {
        printf("ERROR: Invalid board max width range! gameBoardMaxWidth >= 8\n");
        exit(1);
    }
    if(gameBoardMinHeight < MINIMUM_BOARD_HEIGHT_AND_WIDTH) {
        printf("ERROR: Invalid board max height range! gameBoardMaxHeight >= 8\n");
        exit(1);
    }
    if(gameBoardMinWidth < MINIMUM_BOARD_HEIGHT_AND_WIDTH) {
        printf("ERROR: Invalid board max width range! gameBoardMaxWidth >= 8\n");
        exit(1);
    }
}