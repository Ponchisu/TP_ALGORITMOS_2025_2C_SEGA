#include "../headers/config.h"

int Config_getParameter(const char* line);
bool Config_getValue(const char* line, int* number);


bool Config_getParametersFromFile(int* rows, int* columns, int* numLives, int* numGhost, int* numAwards, int* maxLives) {
    FILE* pf = fopen(FILE_CONFIG, "rt");
    char line[SIZE_LINE_CONFIG];
    int parameter;
    int number;

    *rows = -1;
    *columns = -1;
    *numLives = -1;
    *numGhost = -1;
    *numAwards = -1;
    *maxLives = -1;

    if(pf == NULL) {
        fprintf(stderr, "Error al abrir archivo config\n");
        return false;
    }

    while(fgets(line, SIZE_LINE_CONFIG, pf)) {
        parameter = Config_getParameter(line);
        if(parameter != -1 && Config_getValue(line, &number) == true) {
            switch (parameter) {
                case ROWS:
                    *rows = number;
                break;
            case COLUMNS:
                    *columns = number;
                break;
            case NUM_LIVES:
                    *numLives = number;
                break;
            case NUM_GHOST:
                *numGhost = number;
                break;
            case NUM_AWARDS:
                *numAwards = number;
                break;
            case MAX_LIVES:
                *maxLives = number;
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
        fprintf(stderr, "Error no se ingresaro un numero de vidas valido\n");
        return false;
    }
    if(*numGhost == -1) {
        fprintf(stderr, "Error no se ingresaro un numero de fantasma valido\n");
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

int Config_getParameter(const char* line) {
    char vec[][SIZE_LINE_CONFIG] = {
        "filas",
        "columnas",
        "vidas_inicio",
        "maximo_numero_fantasmas",
        "maximo_numero_premios",
        "maximo_vidas_extra",
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
        if(strcmpi(copy, vec[i]) == 0)
        {
            return i;
        }
        i++;
    }

    return -1;
}

bool Config_getValue(const char* line, int* number) {
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
        *number = atof(colon + 1);
        return true;
    } else
        return false;
}
