#include "../headers/config.h"

int _Config_getParameter(const char* line);
bool _Config_getValue(const char* line, int* number);


bool Config_getParametersFromFile(int* rows, int* columns, int* numLives, int* numGhosts, int* numAwards, int* maxLives, bool* rei) {
    FILE* pf;
    char line[SIZE_LINE_CONFIG];
    int parameter;
    int number;

    *rows = -1;
    *columns = -1;
    *numLives = -1;
    *numGhosts = -1;
    *numAwards = -1;
    *maxLives = -1;
    *rei = false;

    pf = fopen(FILE_CONFIG, "rt");
    if(pf == NULL) {
        fprintf(stderr, "Error al abrir archivo config\n");
        return false;
    }

    while(fgets(line, SIZE_LINE_CONFIG, pf)) {
        parameter = _Config_getParameter(line);
        if((parameter != -1 && _Config_getValue(line, &number) == true) || parameter == 6) {
            switch (parameter) {
                case ROWS:
                    if(*rows == -1) 
                        *rows = number;
                break;
            case COLUMNS:
                    *columns = number;
                break;
            case NUM_LIVES:
                    *numLives = number;
                break;
            case NUM_GHOST:
                *numGhosts = number;
                break;
            case NUM_AWARDS:
                *numAwards = number;
                break;
            case MAX_LIVES:
                *maxLives = number;
                break;
            case REI:
                *rei = true;
                break;
            }
        }
    }

    fclose(pf);

    if(*rows == -1) {
        fprintf(stderr, "Error no se ingresaron filas validas\n");
        return false;
    }
    if(*columns == -1) {
        fprintf(stderr, "Error no se ingresaron columnas validas\n");
        return false;
    }
    if(*numLives == -1) {
        fprintf(stderr, "Error no se ingresaron un numero de vidas valido\n");
        return false;
    }
    if(*numGhosts == -1) {
        fprintf(stderr, "Error no se ingresaron un numero de fantasma valido\n");
        return false;
    }
    if(*numAwards == -1) {
        fprintf(stderr, "Error no se ingreso un numero de premios valido\n");
        return false;
    }
    if(*maxLives == -1) {
        fprintf(stderr, "Error no se ingreso un numero de vidas valido\n");
        return false;
    }

    return true;
}

int _Config_getParameter(const char* line) {
    char vec[][SIZE_LINE_CONFIG] = {
        "rows",
        "columns",
        "lives_initial",
        "number_of_ghost",
        "number_of_award",
        "lives_additional",
        "rei",
    };

    char copy[SIZE_LINE_CONFIG];
    char* colon;
    int i = 0;

    strcpy(copy, line);
    colon = strrchr(copy, ':');
    if(colon == NULL) {
        return -1;
    }
    *colon = '\0';

    while(i < AMOUNT_PARAMETERS) {
        if(strcmp(copy, vec[i]) == 0) {
            return i;
        }
        i++;
    }

    return -1;
}

bool _Config_getValue(const char* line, int* number) {
    char* colon;
    char* current;

    colon = strchr(line, ':');
    current = colon + 2;
    while(*current != '\0' && isNumber(*current)) {
        current ++;
    }

    if(*current == '\n') {
        *current = '\0';
    }

    if(*current == '\0') {
        *number = atoi(colon + 1);
        return true;
    } else
        return false;
}
