#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define ROWS 0
#define COLUMNS 1
#define NUM_LIVES 2
#define NUM_GHOST 3
#define NUM_AWARDS 4
#define MAX_LIVES 5
#define REI 6

#define AMOUNT_PARAMETERS 7

#define FILE_CONFIG "config.txt"
#define SIZE_LINE_CONFIG 30

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/bool.h"

#define isNumber(a) ((a) >= '0' && (a) <= '9')

bool Config_getParametersFromFile(int* rows, int* columns, int* numLives, int* numGhost, int* numAwards, int* maxLives, bool* rei);


#endif // CONFIG_H_INCLUDED
