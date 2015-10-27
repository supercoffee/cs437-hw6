
#include "functions.h"

void print_result(int value, int error){
  printf("Result: %d   Error: %d\n", value, error);
}

void test_str_to_int(){

  int result, error = -1;
  result = str_to_int("999", &error);
  print_result(result, error);

  result = str_to_int("-999", &error);
  print_result(result, error);


  //should overflow int
  result = str_to_int("9123456789", &error);
  print_result(result, error);


  //should also overflow
  result = str_to_int("-9123456789", &error);
  print_result(result, error);


  //Should have a conversion error
  result = str_to_int("123asdf", &error);
  print_result(result, error);

}

int main(){
  test_str_to_int();
}
