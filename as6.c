#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define INT_BUFFER_LENGTH 16

void gather_string(char * buffer, size_t length, const char * prompt){

  printf("%s", prompt);

  // apparently fgets reads length -1 chars into the buffer
  fgets(buffer, length, stdin);
}

/**
  Convert a long value to int value safely.
  If long value underflows or overflows, a non-zero
  error code is returned and out is left untouched.
*/
int convert_long_to_int(int * out, const long in){

    if (in > INT_MAX){
      return 1;
    } else if (in < INT_MIN){
      return -1;
    }
    *out = (int) in;
    return 0;
}

/**
    Gather an integer from the user and write it to out.
    Non-zero return value indicates bad input.
    @return 0 if no error
*/
int gather_int(int * out, const char * prompt){

  char buf[INT_BUFFER_LENGTH];
  gather_string(buf, INT_BUFFER_LENGTH, prompt);

  char * garbage_bin;
  long long_val = strtol(buf, garbage_bin, 0);

  // Check if any chars were thrown away by strtol
  if (*garbage_bin != '\0'){
      //The input contained some non numeric garbage,  abort
      return 1;
  }
  int error = convert_long_to_int(out, long_val);

  return error;
}

int main(){

}
