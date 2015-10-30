#include <limits.h>
#include "functions.h"


void print_result(int value, int error){
  printf("Result: %d   Error: %d\n", value, error);
}

void test_compare_file_paths(){

  // should succeed
  char a[] = "/a/b/c/d/e";
  char b[] = "/a/b/c/d";

  int matches = compare_file_paths(a, b);
  printf("%s subpath of %s ? %d\n", a, b, matches);

  // should fail, paths differnt after b
  char c[] = "/a/b/c/d";
  char d[] = "/a/b/d";
  matches = compare_file_paths(c,d);
  printf("%s subpath of %s ? %d\n", c, d, matches);

  // should fail, path e not a subpath of f
  char e[] = "/a/b/c/";
  char f[] = "/a/b/c/d";
  matches = compare_file_paths(e,f);
  printf("%s subpath of %s ? %d\n", e, f, matches);

}

void test_safe_add(){

  int32_t a = INT_MAX;
  int32_t b = 1;

  // Should produce error
  int error;
  int result = safe_add(a, b, &error);

  print_result(result, error);

  // Should not result in error
  a = INT_MIN;
  error = 0;
  result = safe_add(a, b, &error);
  print_result(result, error);
}


void test_safe_multiply(){

  int32_t a = INT_MAX;
  int32_t b = 1;

  // Should not result in error
  int error;
  int result = safe_multiply(a, b, &error);

  print_result(result, error);

  // Should result in error
  b = 2;
  error = 0;
  result = safe_add(a, b, &error);
  print_result(result, error);

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

  test_safe_add();
  test_safe_multiply();

  test_compare_file_paths();
}
