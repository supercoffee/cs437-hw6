#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include "functions.h"

#define STR_BUF_LEN 50
#define FILENAME_BUF_LEN 255
#define PW_BUF_LEN 65

FILE * gather_filename_and_open(const char * prompt, const char * mode){

  if (NULL == prompt || NULL == mode){
    return NULL;
  }

  //read file name
  char filename[PATH_MAX];
  char cwd[PATH_MAX];
  char resolved_path[PATH_MAX];

  FILE * file = NULL;

  while (NULL == file){
    read_string_from_file(filename, FILENAME_BUF_LEN, stdin, prompt);

    realpath(filename, resolved_path);
    getcwd(cwd, PATH_MAX);

    // Input file should be a subpath of current directory
    int path_is_sub_dir = compare_file_paths(resolved_path, cwd);

    if (!path_is_sub_dir){
        printf("%s\n", "File path must be a subdirectory of current path.");
        continue;
    }
    file = fopen(filename, mode);

    if(NULL == file){
      printf("%s\n", "File does not exist or cannot read file.");
    }
  }
  return file;
}

void write_to_output_file(FILE * input_file, FILE * output_file, int32_t int_val2,
                    int32_t int_val1, char * fname, char * lname){

  // output user's name
  output_to_stream(fname, output_file);
  output_to_stream(" ", output_file);
  output_to_stream(lname, output_file);
  output_to_stream("\n", output_file);

 // Do addition and output results to file, warning if overflow occurred.
 int overflow = 0;
 int32_t addition_result = safe_add(int_val2, int_val1, &overflow);
 if (overflow){
   output_to_stream("WARNING: Addition resulted in overflow: \n", output_file);
 }
 fprintf(output_file, "%d\n", addition_result);

 // Do multiplication and output results to file, warning if overflow occurred.
 overflow = 0;
 int32_t multiplication_result = safe_multiply(int_val1, int_val2, &overflow);
 if (overflow){
   output_to_stream("WARNING: Multiplication resulted in overflow: \n", output_file);
 }
 fprintf(output_file, "%d\n", multiplication_result);


 // copy contents of input file to output file

 char buffer[128];
 while(! feof(input_file)){
    fgets(buffer, 128, input_file);
    output_to_stream(buffer, output_file);
 }

}


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


int main(){

  char fname[STR_BUF_LEN], lname[STR_BUF_LEN];
  //read first name
  read_string_from_file(fname, STR_BUF_LEN, stdin, "Enter first name: ");
  //read last name
  read_string_from_file(lname, STR_BUF_LEN, stdin, "Enter last name: ");

  //read two int values
  int int_val1, int_val2;
  int_val1 = read_int_from_file();
  int_val2 = read_int_from_file();

  FILE * input_file = gather_filename_and_open("Enter input file path: ", "r");
  FILE * output_file = gather_filename_and_open("Enter output file path: ", "w");

  gather_and_verify_password();

  //write output to output file
  write_to_output_file(input_file, output_file, int_val2, int_val1, fname, lname);

}
