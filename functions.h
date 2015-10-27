#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void gather_string(char * buffer, size_t length, FILE * input,
                  const char * prompt);

int str_to_int(const char * in, int * error);

#endif
