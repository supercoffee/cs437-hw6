#include <stdlib.h>
#include <stdio.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define PASSWORD_FILE "password.txt"

void read_string_from_file(char *buffer, size_t length, FILE *input,
                           const char *prompt);

int str_to_int(const char * in, int * error);

/**
  Returns 0 on success
  Returns 1 if opening password output file fails
  Attempts to write hashed password to PASSWORD_FILE.
  PASSWORD_FILE must be writable by the current user.
*/
int32_t store_password(char * password, FILE * output);

void output_to_stream(char * output, FILE * stream);

int write_password_to_file(char * password);

int verify_password_from_file(char * password);

int safe_add(int32_t a, int32_t b, int * error);

int safe_multiply(int32_t a, int32_t b, int * error);

int compare_file_paths(char * path1, char * path2);

#endif
