/*
PANAGIOTIS PAPATHEODOROPOULOS
AM:2022202200160
dit22160@go.uop.gr

NIKOLAS GOGALIS
AM: 2022202200031
dit22031@go.uop.gr
*/

#pragma once

/*
 * Starts the game.
 * Creates the total stages' game board and generates the mines.
 * Creates a playable invironment for the user.
 
 * @param difficultyLevel The difficulty level of the game.
 * @param gameBoardHeight The height of the game board.
 * @param gameBoardWidth The width of the game board.
 * @param hasDebugMode The debug mode, to show all the elements of the board.
*/
void startGame(int difficultyLevel, int gameBoardHeight, int gameBoardWidth, int hasDebugMode);

/*
 * Creates the game board array based on the height and width given.
 
 * Returns the game board array as BoardData 2D array type.

 * @param height The height of the game board.
 * @param width The width of the game board.
*/
BoardData **createBoard(int height, int width);

/*
 * Frees the game board array.
 
 * @param **board The game board array as BoardData 2D array type.
 * @param height The height of the game board.
*/
void freeBoard(BoardData **board, int height);

/*
 * Generates totalMines mines randomly in the game board.
 * Generates the numbers around the mines.
 * Generates the empty cells.
 
 * @param **board The game board array as BoardData 2D array type.
 * @param height The height of the game board.
 * @param width The width of the game board.
 * @param totalMines The total mines to be generated in the game board.
 * @param avoidRow The row to avoid generating mines in.
 * @param avoidCol The column to avoid generating mines in.
*/
void generateBoard(BoardData **board, int height, int width, int totalMines, int avoidRow, int avoidCol);


/*
 * Prints the game board.
 * Prints the opened cells.
 * Prints the closed cells.

 * @param **board The game board array as BoardData 2D array type.
 * @param height The height of the game board.
 * @param width The width of the game board.
 * @param hasLost if it is true print all the mines.
 * @param hasDebugMode if it is true print the board two times, one with all the elements revealed and one with the elements hidden like the normal game.
*/
void printGameBoard(BoardData **board, int height, int width, int hasLost, int hasDebugMode);


/*
 * Prints the game commands based on the game commands defined in the config file.
*/
void printGameCommands();


/*
 * Prints the message and waits for the user to press enter to continue.

 * @param message The message to be printed.
*/
void askUserToExit(char *message);

/*
 * Prints the command result message based on the gameCommandResult enum value.

 * @param commandResult The gameCommandResult enum value.
*/
void printCommandResult(gameCommandResult commandResult);