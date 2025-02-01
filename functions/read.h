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
 * Ask and read the user's input based on the main menu options (modes + exit).
 * Returns the option selected by the user.
 * Option is an integer between 1 and the total number of difficulty levels + 1.
 * + 1 is for the exit option.
*/
int readMainMenuOption();

/*
 * Ask and read the user input for the game board dimensions.
 * The user is asked to enter the height and the width of the game board.
 * The height and width are between the minimum and maximum values defined in the config file.

 * @param *height Pointer of the height of the game board to save the value given by the user.
 * @param *width Pointer of the width of the game board to save the value given by the user
*/
void readGameBoardDimensions(int *height, int *width);

/*
 * Reads the user's input.

 * Returns 0 if the string is greater than maxLength.
 * Returns 1 if the string is less than or equal to maxLength.
  
 * @param saveToArray The array to save the string.
 * @param maxLength The maximum length of the string.
*/
int readText(char saveToArray[], unsigned int maxLength);


/*
 * Read the user's input, checks if it a valid game command and runs it.

 * Return gameCommandResult enum values.

 * @param **board Pointer of the game board.
 * @param height The height of the game board.
 * @param width The width of the game board.
 * @param **resultMessage Pointer of the extra results the command may return.
*/
gameCommandResult readAndRunGameCommand(BoardData **board, int height, int width, void **resultMessage);