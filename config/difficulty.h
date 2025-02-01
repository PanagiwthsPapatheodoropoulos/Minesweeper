/*
PANAGIOTIS PAPATHEODOROPOULOS
AM:2022202200160
dit22160@go.uop.gr

NIKOLAS GOGALIS
AM: 2022202200031
dit22031@go.uop.gr
*/

#pragma once

typedef struct difficultyLevel {
    int mode;
    char name[20];
    int percentage;
} difficultyLevel;

extern difficultyLevel difficultyLevels[];

extern int totalDifficultyLevels;