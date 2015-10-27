#include <stdlib.h>
#include <stdio.h>

#include "functions.h"

#define STR_BUF_LEN 50


int gather_int(){

  char buf[STR_BUF_LEN];
  int error = -1, result;

  while (error){

    gather_string(buf, STR_BUF_LEN, stdin, "Enter an integer: ");
    result = str_to_int(buf, &error);

    if (error){
      printf("%s", "Invalid integer. \n");
    }
  }

  return result;
}


int main(){

  char fname[STR_BUF_LEN], lname[STR_BUF_LEN];
  //read first name
  gather_string(fname, STR_BUF_LEN, stdin, "Enter first name: ");
  //read last name
  gather_string(lname, STR_BUF_LEN, stdin, "Enter last name: ");

  int int_val1, int_val2;
  //read two int values
  int_val1 = gather_int();
  int_val2 = gather_int();
  //read input file name
  char
  //read output file name

  //read output file name

  //read password and verify

  //write output to output file

}
