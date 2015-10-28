#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "functions.h"

#define STR_BUF_LEN 50
#define FILENAME_BUF_LEN 255
#define PW_BUF_LEN 65



int gather_int(){

  char buf[STR_BUF_LEN];
  int error = -1, result, ctr = 0;

  while (error){
    if (ctr > 99){
      exit(0);
    }

    gather_string(buf, STR_BUF_LEN, stdin, "Enter an integer: ");
    result = str_to_int(buf, &error);

    if (error){
      printf("%s not a valid integer.\n", buf);
      ctr++;
    }
  }

  return result;
}

void do_something(FILE * file){
  (void) file;
}


int main(){

  char fname[STR_BUF_LEN], lname[STR_BUF_LEN];
  //read first name
  gather_string(fname, STR_BUF_LEN, stdin, "Enter first name: ");
  //read last name
  gather_string(lname, STR_BUF_LEN, stdin, "Enter last name: ");

  printf("%s", fname);
  printf("%s", lname);

  //read two int values
  int int_val1, int_val2;
  int_val1 = gather_int();
  int_val2 = gather_int();

  //read input file name
  char input_filename[FILENAME_BUF_LEN];
  gather_string(input_filename, FILENAME_BUF_LEN, stdin, "Enter input file path: ");
  FILE * input_file = fopen(input_filename, "r");
  do_something(input_file);

  //read output file name
  char output_filename[FILENAME_BUF_LEN];
  gather_string(output_filename, FILENAME_BUF_LEN, stdin, "Enter output file path: ");
  FILE * output_file = fopen(output_filename, "w");
  do_something(output_file);

  char password[PW_BUF_LEN];
  //read password and verify
   gather_string(password, PW_BUF_LEN, stdin, "Enter password (8-64 chars): ");

   gather_string(password, PW_BUF_LEN, stdin,"Enter password again: ");

  //write output to output file


}
