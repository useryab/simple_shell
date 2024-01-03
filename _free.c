#include "shell.h"

void _free(char ***arg) {
    int i = 0;

    while ((*arg)[i] != NULL) {
        free((*arg)[i]);
        i++;
    }

    free(*arg);
}
