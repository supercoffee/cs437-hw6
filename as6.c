#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "functions.h"

#define STR_BUF_LEN 50
#define FILENAME_BUF_LEN 255
#define PW_BUF_LEN 65

/*
  This function is pretty stupid. It just keeps looping until
  the password is entered and verified correctly. Each time the password
  is written out to file **Before** verifying it, per the assignments.
*/
void gather_and_verify_password(){

  char password[PW_BUF_LEN];
  // verify password returns non zero if verification fails
  int password_mismatch = 1;

  while (password_mismatch){
    //read password and verify
    read_string_from_file(password, PW_BUF_LEN, stdin, "Enter password (8-64 chars): ");
    write_password_to_file(password);

    read_string_from_file(password, PW_BUF_LEN, stdin, "Enter password again: ");
    password_mismatch = verify_password_from_file(password);

    if (password_mismatch){
      output_to_stream("Passwords do not match. \n", stdout);
    }
  }
}

int read_int_from_file(){

  char buf[STR_BUF_LEN];
  int error = -1, result, ctr = 0;

  while (error){
    if (ctr > 99){
      exit(0);
    }

    read_string_from_file(buf, STR_BUF_LEN, stdin, "Enter an integer: ");
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
  read_string_from_file(fname, STR_BUF_LEN, stdin, "Enter first name: ");
  //read last name
  read_string_from_file(lname, STR_BUF_LEN, stdin, "Enter last name: ");

  printf("%s", fname);
  printf("%s", lname);

  //read two int values
  int int_val1, int_val2;
  int_val1 = read_int_from_file();
  int_val2 = read_int_from_file();

  //read input file name
  char input_filename[FILENAME_BUF_LEN];
  read_string_from_file(input_filename, FILENAME_BUF_LEN, stdin, "Enter input file path: ");
  FILE * input_file = fopen(input_filename, "r");
  do_something(input_file);

  //read output file name
  char output_filename[FILENAME_BUF_LEN];
  read_string_from_file(output_filename, FILENAME_BUF_LEN, stdin, "Enter output file path: ");
  FILE * output_file = fopen(output_filename, "w");
  do_something(output_file);

  gather_and_verify_password();

  //write output to output file


}
