#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "functions.h"
#define INT_BUFFER_LENGTH 16

#define ERROR_NON_NUMERIC_INPUT 1
#define ERROR_INT_OVERFLOW 2

int seek_to_newline(FILE * stream){

  int ch, ctr;
  for (ctr = 0; (ch = getc(stream)) != EOF && ch != '\n'; ctr++);

  return ctr;
}

void gather_string(char * buffer, size_t length, FILE * input,
                  const char * prompt){

  if (NULL != prompt){
      printf("%s", prompt);
  }

  if (NULL != buffer && NULL != input){
      fgets(buffer, length, input);
      // Replace newline character with null byte.
      // https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input

      size_t chars_read = strcspn(buffer, "\n");

      // If no newline occurs before the end of the string, then it must be
      // sitting on the buffer and needs to be removed.
      if (chars_read == length -1){
          seek_to_newline(stdin);
      } else {
        // Set newline character to null because fgets leaves it there
        buffer[chars_read] = '\0';
      }

  }
}


/**
    Convert a string into an integer.
    Caller must check error parameter to ensure
    that conversion result is accurate. The value zero is
    returned in error cases.
*/
int str_to_int(const char * in, int * error){

  char * garbage_bin = "";

  long long_val = strtol(in, &garbage_bin, 0);

  // Check if any chars were thrown away by strtol
  if (*garbage_bin != '\0'){
      //The input contained some non numeric garbage,  abort
      *error = ERROR_NON_NUMERIC_INPUT;
      return 0;
  }

  if (long_val > INT_MAX || long_val < INT_MIN){
      *error = ERROR_INT_OVERFLOW;
      return 0;
  }

  *error = 0;
  return (int) long_val;
}
