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

#include "gameCommands.h"
#include "../config/gameBoard.h"


gameCommandResult exitCommand() {
    return EXIT;
}


gameCommandResult openCommand(BoardData **board, int height, int width, int x, int y, void **resultMessage) {
    
    /* CHECK IF THE COORDINATES ARE VALID */
    if(x < 0 || x >= height || y < 0 || y >= width) return INVALID_CORDINATES;
    
    /* CHECK IF THE CELL IS ALREADY OPENED */
    if(board[x][y].isRevealed) return ALREADY_OPENED;

    /* CHECK IF THE CELL IS A MINE */
    if(board[x][y].isMine) return FOUND_MINE_HAS_LOST;

    /* OPEN THE CELL */
    /* IF VALUE IS 0 IT MEANS THAT THE BOARD IS NOT YET GENERATED */
    if(board[x][y].value) {
        board[x][y].isFlagged = 0; 
        board[x][y].isRevealed = 1;
    }

    /* IF THE CELL IS EMPTY OPEN ALL THE CELLS AROUND */
    if(board[x][y].value == '.') {
        for(int currentRowCell = x - 1; currentRowCell <= x + 1; currentRowCell++) {
            for(int currentColCell = y - 1; currentColCell <= y + 1; currentColCell++) {
                if(currentRowCell == x && currentColCell == y) continue;
                openCommand(board, height, width, currentRowCell, currentColCell, resultMessage);
            }
        }
    }

    /* SAVE THE CORDINATES OF THE CELL THE USER TRIES TO OPEN */
    if(*resultMessage != NULL) free(*resultMessage);
    *resultMessage = malloc(sizeof(coordinates)); 
    ((coordinates *)(*resultMessage))->x = x;
    ((coordinates *)(*resultMessage))->y = y;
    

    /* CHECK IF USER HAS WON */
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            /*IF IT IS A MINE IGNORE*/
            if(board[i][j].isMine) continue;

            /*IF WE FIND AT LEAST ONE THAT HAS NOT BEEN REVEALED IT MEANS THE GAME IS STILL IN PROGRESS*/
            if(!board[i][j].isRevealed) return board[x][y].value == '.' ? OPEN_CELLS_SUCCESSFULLY : OPEN_CELL_SUCCESSFULLY;
        }
    }

    /* IF THERE IS NOT AT LEAST ONE NOT REVEALED IT MEANS THE GAME IS OVER AND THE USER HAS WON */
    return USER_WON;
}


gameCommandResult markCommand(BoardData **board, int height, int width, int x, int y, void **resultMessage) {
    /* CHECK IF THE COORDINATES ARE VALID */
    if(x < 0 || x >= height || y < 0 || y >= width) return INVALID_CORDINATES;

    /* CHECK IF THE CELL IS ALREADY OPENED */
    if(board[x][y].isRevealed) return ALREADY_OPENED;

    /* CHECH IF THE CELL IS ALREADY FLAGGED */
    if(board[x][y].isFlagged) return ALREADY_FLAGGED;

    /* MARK THE CELL */
    board[x][y].isFlagged = 1;

    return MARK_CELL_SUCCESSFULLY;
}


gameCommandResult unmarkCommand(BoardData **board, int height, int width, int x, int y, void **resultMessage) {
    /* CHECK IF THE COORDINATES ARE VALID */
    if(x < 0 || x >= height || y < 0 || y >= width) return INVALID_CORDINATES;

    /* CHECK IF THE CELL IS ALREADY OPENED */
    if(board[x][y].isRevealed) return ALREADY_OPENED;

    /* CHECH IF THE CELL IS ALREADY FLAGGED */
    if(!board[x][y].isFlagged) return CELL_NOT_MARKED;

    /* UNMARK THE CELL */
    board[x][y].isFlagged = 0;

    return UNMARK_CELL_SUCCESSFULLY;
}


gameCommandResult cheatCommand(BoardData **board, int height, int width, int x, int y, void **resultMessage) {
    /* CHECK IF THE COORDINATES ARE VALID */
    if(x < 0 || x >= height || y < 0 || y >= width) return INVALID_CORDINATES;

    /* CHECK IF THE CELL IS ALREADY OPENED */
    if(board[x][y].isRevealed) return ALREADY_OPENED;

    /* PREPARE resultMessage TO SAVE THE HINT */
    free(*resultMessage);
    *resultMessage = malloc(sizeof(char) * 100);
    
    /* SHOW A HINT TO THE USER WHAT THE VALUE OF CELL IS */
    if(board[x][y].value) sprintf(*resultMessage, "The cell at (%d, %d) is a '%c'", x+1, y+1, board[x][y].value);
    /* IF VALUE IS 0 IT MEANS THAT THE BOARD IS NOT YET GENERATED */
    else sprintf(*resultMessage, "You can only cheat after first open!");

    return CHEAT_SUCCESS_MESSAGE;
}