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

#include "control.h"

void clearScreen() {
    system("clear");
}


void clearBuffer() {
    int ch;
    while( (ch = getchar()) != EOF && ch != '\n' ) continue;
}

