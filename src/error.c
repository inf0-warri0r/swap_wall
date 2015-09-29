#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void die(int error_message)
{
    fprintf(stderr, "Error %d\n", error_message);
    perror("");
    exit(EXIT_FAILURE);
}
