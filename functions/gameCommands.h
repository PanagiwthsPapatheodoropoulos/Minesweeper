/*
PANAGIOTIS PAPATHEODOROPOULOS
AM:2022202200160
dit22160@go.uop.gr

NIKOLAS GOGALIS
AM: 2022202200031
dit22031@go.uop.gr
*/

#pragma once

#include "../config/gameCommands.h"

/*
 * Returns EXIT and exits. 
 * After that the program will be back to the main menu.
*/
gameCommandResult exitCommand();

/*
 * Opens the cell in the game board.

 * @param **board The game board array as BoardData 2D array type.
 * @param height The height of the game board.
 * @param width The width of the game board.
 * @param x The x coordinate of the cell to be opened.
 * @param y The y coordinate of the cell to be opened.
 * @param **resultMessage to save the users cordinates.
*/
gameCommandResult openCommand(BoardData **board, int height, int width, int x, int y, void **resultMessage);

/*
 * Marks the cell in the game board.

 * @param **board The game board array as BoardData 2D array type.
 * @param height The height of the game board.
 * @param width The width of the game board.
 * @param x The x coordinate of the cell to be marked.
 * @param y The y coordinate of the cell to be marked.
 * @param **resultMessage.
*/
gameCommandResult markCommand(BoardData **board, int height, int width, int x, int y, void **resultMessage);

/*
 * Unmarks the cell in the game board.

 * @param **board The game board array as BoardData 2D array type.
 * @param height The height of the game board.
 * @param width The width of the game board.
 * @param x The x coordinate of the cell to be unmarked.
 * @param y The y coordinate of the cell to be unmarked.
 * @param **resultMessage.
*/
gameCommandResult unmarkCommand(BoardData **board, int height, int width, int x, int y, void **resultMessage);

/*
 * cheat gives the user the value of a cell.

 * @param **board The game board array as BoardData 2D array type.
 * @param height The height of the game board.
 * @param width The width of the game board.
 * @param x The x coordinate of the cell to be hinted to the user.
 * @param y The y coordinate of the cell to be hinted to the user.
 * @param **resultMessage to save the message of cheat command.
*/
gameCommandResult cheatCommand(BoardData **board, int height, int width, int x, int y, void **resultMessage);